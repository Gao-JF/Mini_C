/**************************************************************
 *                                                            *
 *   Copyright (c) 2021 Gaojunfeng All rights reserved.       *
 *   Version: 1.0                                             *
 *   Author: Gaojunfeng                                       *
 *                                                            *
 *   最后修改日期：2021.04.30                                 *
 *                                                            *
 *   语法分析的类定义                                         *
 *                                                            *
 **************************************************************/

#ifndef GRAMMER_ANALYSIS_H
#define GRAMMER_ANALYSIS_H
#include"word_analysis.h"
#include"grammer_tree.h"


class grammer_analysis:public word_analysis
{
public:
    grammer_analysis(word_analysis w);// 构造函数
    
    grammer_tree* match(string t);// 匹配词

    string get_Token();//获取词

    int get_flag();//获取语法是否有错误

    /* 下面是文法 */
    grammer_tree* program(grammer_tree *root);
    grammer_tree* declaration_list(grammer_tree *root);
    grammer_tree* declaration_list_1(grammer_tree *root);
    grammer_tree* declaration(grammer_tree *root);
    grammer_tree* simple_declaration(grammer_tree *root);
    grammer_tree* var_declaration(grammer_tree *root);
    grammer_tree* fun_declaration(grammer_tree *root);
    grammer_tree* type_specifier();
    grammer_tree* params(grammer_tree *root);
    grammer_tree* param_list(grammer_tree *root);
    grammer_tree* param_list_1(grammer_tree *root);
    grammer_tree* param(grammer_tree *root);
    grammer_tree* compound_stmt(grammer_tree *root);
    grammer_tree* local_declarations(grammer_tree *root);
    grammer_tree* statement_list(grammer_tree *root);
    grammer_tree* statement(grammer_tree *root);
    grammer_tree* expression_stmt(grammer_tree *root);
    grammer_tree* selection_stmt(grammer_tree *root);
    grammer_tree* iteration_stmt(grammer_tree *root);
    grammer_tree* return_stmt(grammer_tree *root);
    grammer_tree* expression(grammer_tree *root);
    grammer_tree* var(grammer_tree *root);
    grammer_tree* simple_expression(grammer_tree *root);
    grammer_tree* relop(grammer_tree *root);
    grammer_tree* additive_expression(grammer_tree *root);
    grammer_tree* additive_expression_1(grammer_tree *root);
    grammer_tree* addop(grammer_tree *root);
    grammer_tree* term(grammer_tree *root);
    grammer_tree* term_1(grammer_tree *root);
    grammer_tree* mulop(grammer_tree *root);
    grammer_tree* factor(grammer_tree *root);
    grammer_tree* call(grammer_tree *root);
    grammer_tree* args(grammer_tree *root);
    grammer_tree* arg_list(grammer_tree *root);
    grammer_tree* arg_list_1(grammer_tree *root);


private:
    word_analysis wa;
    grammer_tree *root;//语法树的根节点
    int pos;// 当前是第几个token
    string token;
    int flag;//标志是否有语法错误
};

#endif