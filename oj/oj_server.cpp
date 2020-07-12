#include <stdio.h>
#include <string>
#include <string.h>
#include "httplib.h"

#include"oj_view.hpp"
#include"oj_model.hpp"
#include"compile.hpp"
int main()
{
    using namespace httplib;
    Server Svr;
    OjModel ojmodel;
    Svr.Get("/all_questions", [&ojmodel](const Request& req, Response& resp){
        std::vector<Question> ques;
        ojmodel.GetAllQuestions(&ques);
        std::string html;
        OjView::ExpandAllQuestionshtml(&html,ques);
         resp.set_content(html,"text/html; charset=UTF-8");
          });
    Svr.Get(R"(/question/(\d+))", [&ojmodel](const Request& req, Response& resp){
      // 1.去试题模块去查找对应题号的具体的题目信
     //      map当中 （序号 名称 题目的地址 难度）
           std::string desc;
          std::string header;
          //从querystr当中获取id
          // 2.在题目地址的路径下去加载单个题目的描述信息
          struct Question ques;
          ojmodel.GetOneQuestion(req.matches[1].str(), &desc, &header, &ques);
          // 3.进行组织，返回给浏览器     
          std::string html;
          OjView::ExpandOneQuestion(ques, desc, header, &html);
          resp.set_content(html,"text/html; charset=UTF-8");
        });
    Svr.Post(R"(/question/(\d+))", [&ojmodel](const Request& req, Response& resp){
        std::unordered_map<std::string, std::string> pram;
        UrlUtil::PraseBody(req.body, &pram);
        std::string code;
        ojmodel.SplicingCode(pram["code"], req.matches[1].str(), &code); 
        Json::Value req_json;
        req_json["code"] = code;
        Json::Value Resp_json;
        Compiler::CompileAndRun(req_json, &Resp_json);
        const std::string errorno = Resp_json["errorno"].asString();
        const std::string reason = Resp_json["reason"].asString();
        const std::string stdout_reason = Resp_json["stdout"].asString();
        std::string html;
        OjView::ExpandReason(errorno, reason, stdout_reason, &html);
        resp.set_content(html,"text/html; charset=UTF-8");
        });
  Svr.listen("192.168.174.131", 19999);
  return 0;
}
