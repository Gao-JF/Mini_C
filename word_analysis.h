
/**************************************************************
 *                                                            *
 *   Copyright (c) 2021 Gaojunfeng All rights reserved.       *
 *   Version: 1.0                                             *
 *   Author: Gaojunfeng                                       *
 *                                                            *
 *   最后修改日期：2021.04.30                                 *
 *                                                            *
 *   此类是实现词法分析的类，能够提取关键字、标识符、         *
 *   数字、运算符、特殊符号                                   *
 *                                                            *
 **************************************************************/


#ifndef WORD_ANALYSIS_H
#define WORD_ANALYSIS_H

#include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<vector>

using namespace std;

class word_analysis
{
public:
    
    word_analysis();//构造函数
    
    int get_code(string code);//读取txt文件
    
    int scan();//扫描程序

    string output();//输出扫描结果
    
    static word_analysis copy(word_analysis a,word_analysis b);//复制Token和label

    vector<string> ret_Token();//返回token向量

    vector<string> ret_Label();//返回标签向量
    
private:
    
    set<char>symbol;//存放符号

    set<string>keyword;//存放关键字

    string file;//代码文本

protected:
    vector<string>Token;//存放扫描到的词

    vector<string>label;//存放扫描到的词对应的标签

};
#endif