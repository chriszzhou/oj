																																							   #pragma once
//ֱ�Ӱ�����ֱ��ʹ�ã�ʹ�㣺�ڱ�д���뵱�������Ҳ���ͷ�ļ������Իᱨ��, �����ʱ��ʹ��-Iѡ��ָ��ͷ�ļ���·���Ϳ�����
//���û������� CPLUS_INCLUDE_PATH
#include <ctemplate/template.h>
#include <string>
#include <vector>
#include "oj_model.hpp"


class OjView
{
    public:
        //��Ⱦhtmlҳ�棬���ҽ���ҳ�淵��������
        static void ExpandAllQuestionshtml(std::string* html, std::vector<Question>& ques)
        {
            //1.��ȡ�����ֵ�-->���õ����������ݰ���һ��˳�򱣴浽�ڴ浱��
            ctemplate::TemplateDictionary dict("all_questions");

            for(const auto& que:ques)
            {
                ctemplate::TemplateDictionary* section_dict = dict.AddSectionDictionary("question");
                section_dict->SetValue("id", que.id_);
                section_dict->SetValue("id", que.id_);
                section_dict->SetValue("name", que.name_);
                section_dict->SetValue("star", que.star_);
            }
            //2.��ȡģ����ָ�룬����Ԥ�����htmlҳ�浽�ڴ浱��
            ctemplate::Template* tl =  ctemplate::Template::GetTemplate("./html/all_questions.html", ctemplate::DO_NOT_STRIP);
            //3.��Ⱦ ����ģ�����ָ�룬�������ֵ䵱�е����ݸ��µ�htmlҳ����ڴ���
            tl->Expand(html, &dict);
        }

        //id name star desc header  ==> string html
        static void ExpandOneQuestion(const Question& ques, std::string& desc,std::string& header, std::string* html)
        {
            ctemplate::TemplateDictionary dict("question");
            dict.SetValue("id", ques.id_);
            dict.SetValue("name", ques.name_);
            dict.SetValue("star", ques.star_);
            dict.SetValue("desc", desc);
            dict.SetValue("header", header);
            ctemplate::Template* tpl = ctemplate::Template::GetTemplate("./html/question.html", ctemplate::DO_NOT_STRIP);
            tpl->Expand(html, &dict);
        }
        static void ExpandReason(const std::string& errorno, const std::string& reason, const std::string& stdout_reason, std::string* html){
          ctemplate::TemplateDictionary dict("reason");
          dict.SetValue("errorno", errorno);
          dict.SetValue("reason", reason);
          dict.SetValue("stdout", stdout_reason);
          ctemplate::Template* tpl = ctemplate::Template::GetTemplate("./html/reason.html", ctemplate::DO_NOT_STRIP);
          tpl->Expand(html, &dict);
        }
};
