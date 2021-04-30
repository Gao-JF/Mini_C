
/**************************************************************/
/*                                                            */
/*   Copyright (c) 2021 Gaojunfeng All rights reserved.       */
/*   Version: 1.0                                             */
/*   Author: Gaojunfeng                                       */
/*                                                            */
/*   最后修改日期：2021.04.30                                 */
/*                                                            */
/*   此类是词法分析的实现文件，能够将代码的各个token提取出来  */
/*   以及能够识别token属于的类型                              */
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
    int last=-1;//表示上一个word的标志，0表示标识符，1表示关键字，2表示运算符，3表示数字
    for(int i=0;i<file.length();)
    {
        string word;//存放单词
        //匹配标识符或关键字
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

        //匹配数字
        else if(((file[i]=='+'||file[i]=='-')&&last==2)||file[i]=='.'||file[i]>='0'&&file[i]<='9' && i < file.length())
        {
            bool dot=true;//判断是否还能匹配小数点
            bool e=true;//判断是否还能匹配E|e
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


