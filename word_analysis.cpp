
/**************************************************************/
/*                                                            */
/*   Copyright (c) 2021 Gaojunfeng All rights reserved.       */
/*   Version: 1.0                                             */
/*   Author: Gaojunfeng                                       */
/*                                                            */
/*   ����޸����ڣ�2021.04.30                                 */
/*                                                            */
/*   �����Ǵʷ�������ʵ���ļ����ܹ�������ĸ���token��ȡ����  */
/*   �Լ��ܹ�ʶ��token���ڵ�����                              */
/*                                                            */
/**************************************************************/

#include"pch.h"
#include"word_analysis.h"
#include<stdio.h>

word_analysis::word_analysis()
{
    keyword={"double","else","if","int","return","void","while"};
    symbol={'+','-','*','/','<','>','=',';',',','(',')','[',']','{','}'};
}

int word_analysis::get_code(string code)
{
    file = code;
    return 1;
}

int word_analysis::scan()
{
    int last=-1;//��ʾ��һ��word�ı�־��0��ʾ��ʶ����1��ʾ�ؼ��֣�2��ʾ�������3��ʾ����
    for(int i=0;i<file.length();)
    {
        string word;//��ŵ���
        //ƥ���ʶ����ؼ���
        if(file[i]=='\t'||file[i]==' '||file[i]=='\n'||file[i]=='\r' && i < file.length())
        {
            i++;
            continue;
        }
        else if(file[i]=='_'||file[i]>='a'&&file[i]<='z'||file[i]>='A'&&file[i]<='Z' && i < file.length())
        {
            while(file[i] != '\r' && file[i]!='\t'&&file[i]!=' '&&file[i]!='\n'&&symbol.find(file[i])==symbol.end()&&file[i]!='!'&&i<file.length())
            {
                word+=file[i++];
            }
            if(keyword.find(word)!=keyword.end())
            {
                Token.push_back(word);
                label.push_back("keyword");
                last=1;
            }
            else
            {
                Token.push_back(word);
                label.push_back("identifier");
                last=0;
            }
        }

        //ƥ������
        else if(((file[i]=='+'||file[i]=='-')&&last==2)||file[i]=='.'||file[i]>='0'&&file[i]<='9' && i < file.length())
        {
            bool dot=true;//�ж��Ƿ���ƥ��С����
            bool e=true;//�ж��Ƿ���ƥ��E|e
            if(file[i]=='.')
            dot=false;
            if(file[i]=='+'||file[i]=='-')
            {
                word+=file[i++];
            }
            while(file[i] != '\r'&&file[i]!='\t'&&file[i]!=' '&&file[i]!='\n'&&symbol.find(file[i])==symbol.end() && i < file.length())
            {
                if(file[i]>='0'&&file[i]<='9')
                {word+=file[i++];continue;}
                if(file[i]=='.'&&dot==true)
                {
                    dot=false;
                    word+=file[i++];
                    continue;
                }
                else if((file[i]=='E'||file[i]=='e')&&e==true&&file[i+1]>='0'&&file[i+1]<='9' && i < file.length())
                {
                    e=false;
                    dot=false;
                    word+=file[i++];
                    continue;
                }
                else
                {
                    cout<<"ERROR"<<endl;
                    return 0;
                }
            }
            Token.push_back(word);
            label.push_back("number");
            last=3;
        }
        else if(symbol.find(file[i])!=symbol.end()||file[i]=='!' && i < file.length())
        {
            if(file[i]=='<')
            {
                word="<";
                i++;
                if(file[i]=='=')
                {
                    word+='=';
                    i++;
                }
                Token.push_back(word);
                label.push_back("op");
            }
            else if(file[i]=='>' && i < file.length())
            {
                word=">";
                i++;
                if(file[i]=='=')
                {
                    word+='=';
                    i++;
                }
                Token.push_back(word);
                label.push_back("op");
            }
            else if(file[i]=='=' && i < file.length())
            {
                word="=";
                i++;
                if(file[i]=='=')
                {
                    word+='=';
                    i++;
                }
                Token.push_back(word);
                label.push_back("op");
            }
            else if(file[i]=='!' && i < file.length())
            {
                word="!=";
                i+=2;
                Token.push_back(word);
                label.push_back("op");
            }
            else if(file[i]=='/' && i < file.length())
            {
                word="/";
                i++;
                if(file[i]=='*' && i < file.length())
                {
                    word+='*';
                    i++;
                    while(1)
                    {
                        word+=file[i++];
                        if(file[i]=='*' && i < file.length())
                        {
                            word+=file[i++];
                            if(file[i]=='/' && i < file.length())
                            {
                                word+=file[i++];
                                break;
                            }
                        }
                        if(i==file.length()-1 )
                        {
                            cout<<"ERROR"<<endl;
                            return 0;
                        }
                    }
                    Token.push_back(word);
                label.push_back("annotation");
                }
                else
                {
                Token.push_back(word);
                label.push_back("op");
                }
            }
            else if(file[i]=='*'||file[i]=='+'||file[i]=='-' && i < file.length())
            {
                word=file[i];
                i++;
                Token.push_back(word);
                label.push_back("op");
            }
            else if(i < file.length())
            {
                word=file[i++];
                Token.push_back(word);
                label.push_back("symbol");
            }
            last=2;
        }

    }
}

string word_analysis::output()
{
    string ret;
    for(int i=0;i<Token.size();++i)
    {
        ret += Token[i];
        ret += "           ";
        ret+=label[i];
        ret += "\r\n";
    }
    return ret;
}

word_analysis word_analysis::copy(word_analysis a,word_analysis b)
{
    a.label=b.label;
    a.Token=b.Token;
    return a;
}

vector<string> word_analysis::ret_Token()
{
    return Token;
}

vector<string> word_analysis::ret_Label()
{
    return label;
}


