#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <algorithm>
#include"tools.hpp"
typedef struct Question
{
    std::string id_;
    std::string name_;
    std::string path_;
    std::string star_;
}QUES;
class OjModel
{
    public:
        OjModel()
        {
            LoadQuestions("./config_oj.cfg");
        }
        bool GetAllQuestions(std::vector<Question>* ques)
        {
            for(const auto& kv : model_map_)
            {
                ques->push_back(kv.second);
            }
            std::sort(ques->begin(), ques->end(), [](const Question& l, const Question& r){
                    return std::atoi(l.id_.c_str()) < std::atoi(r.id_.c_str());
                    });
           return true;
        }
        bool GetOneQuestion(const std::string& id, std::string* desc, std::string* header, Question* ques)
        {                      
          auto iter = model_map_.find(id);
          if(iter == model_map_.end())
          {return false;}
          *ques = iter->second;
          int ret = FileOper::ReadDataFromFile(DescPath(iter->second.path_), desc);
          if(ret == -1)
          {return false;}
          ret = FileOper::ReadDataFromFile(HeaderPath(iter->second.path_), header);
          if(ret == -1)  {return false;}
          return true;                                                                                                         
        }
        bool SplicingCode(std::string user_code, const std::string& ques_id, std::string* code)
        {
          auto iter = model_map_.find(ques_id);
          if(iter == model_map_.end())
          {   return false; }
          std::string tail_code;
          int ret = FileOper::ReadDataFromFile(TailPath(iter->second.path_), &tail_code);
          if(ret < 0)
          {   return false; }
          *code = user_code + tail_code;
          return true;                                                                                                    
        }
    private:
        bool LoadQuestions(const std::string& configfile_path)
        {
            std::ifstream file(configfile_path.c_str());
            if(!file.is_open())
            {
                return false;
            }

            std::string line;
            while(std::getline(file, line))
            {
                //1 单链表 ./xxx 难度
                //1.需要切割字符串
                std::vector<std::string> vec;
                StringTools::Split(line, " ", &vec);
                if(vec.size() != 4)
                {
                    continue;
                }
                //2.切割后的内容保存到unordered_map
                Question ques;
                ques.id_ = vec[0];
                ques.name_ = vec[1];
                ques.path_ = vec[2];
                ques.star_ = vec[3];
                model_map_[ques.id_] = ques;
            }
            file.close();
            return true;
        }
         private:
                std::string DescPath(const std::string& ques_path)
                {
                              return ques_path + "desc.txt";
                }        
                std::string HeaderPath(const std::string& ques_path)
               {
                 return ques_path + "header.cpp";                             
               }
               std::string TailPath(const std::string& ques_path)
               {
                 return ques_path + "tail.cpp";                                                      
               }
    private:
        std::unordered_map<std::string, Question> model_map_;
};
