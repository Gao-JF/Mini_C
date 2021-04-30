
/**************************************************************/
/*                                                            */
/*   Copyright (c) 2021 Gaojunfeng All rights reserved.       */
/*   Version: 1.0                                             */
/*   Author: Gaojunfeng                                       */
/*                                                            */
/*   最后修改日期：2021.04.30                                 */
/*                                                            */
/*   此文件是语法分析的实现文件，包括各文法的实现以及         */
/*   token的匹配。                                            */
/*                                                            */
/**************************************************************/
#include"pch.h"
#include"grammer_analysis.h"



grammer_analysis::grammer_analysis(word_analysis w)
{
    pos=0;
    flag = 1;
    label=w.ret_Label();
    Token=w.ret_Token();
}

string grammer_analysis::get_Token()
{
    if(pos>=Token.size())
        return "";

    while(label[pos]=="annotation")
    pos++;
    token=Token[pos];
    return token;
}

grammer_tree* grammer_analysis::match(string t)
{
    if(token==t)
    {
        grammer_tree* c=new grammer_tree(get_Token());
        pos++;
        token=get_Token();
        return c;
    }
    else if(t=="ID")
    {
        if(label[pos]=="identifier")
        {
            grammer_tree* c=new grammer_tree(get_Token());
        pos++;
        token=get_Token();
        return c;
        }
    }
    else if(t=="NUM")
    {
        if(label[pos]=="number")
        {
            grammer_tree* c=new grammer_tree(get_Token());
        pos++;
        token=get_Token();
        return c;
        }
    }
    else
    {
        flag = 0;
        return NULL;
    }
}

int grammer_analysis::get_flag()
{
    return flag;
}

grammer_tree* grammer_analysis::program(grammer_tree *root)
{
/*
    program->declaration_list
*/
    token=get_Token();
    root=new grammer_tree("start");
    root=declaration_list(root);
    
    return root;
}

grammer_tree* grammer_analysis::declaration_list(grammer_tree *root)
{
/*
    declaration_list->declaration declaration_list_1
    declaration_list_1->declaration declaration_list_1 |empty
*/
    grammer_tree *c;
    c=new grammer_tree("declaration");
    c=declaration(c);
    if(c->child_size()>0)
    root->insert_tree(c);
    
    root=declaration_list_1(root);

    return root;
}

grammer_tree* grammer_analysis::declaration_list_1(grammer_tree *root)
{
    grammer_tree *c;
    token=get_Token();
    if( token=="int"|| token=="void")
    {
        c=new grammer_tree("declaration");
        c=declaration(c);
        if(c->child_size()>0)
        root->insert_tree(c);
        
        root=declaration_list_1(root);
    }
    return root;
}

grammer_tree* grammer_analysis::simple_declaration(grammer_tree *root)
{
/*
    simple_declaration->type_specifier ID
*/
    grammer_tree *c;
    token=get_Token();
    c=type_specifier();
    root->insert_tree(c);
    c=match("ID");
    token=get_Token();
    root->insert_tree(c);
    return root;
}

grammer_tree* grammer_analysis::declaration(grammer_tree *root)
{
/*
    declaration->var_declaration|fun_declaration
*/
    grammer_tree *c;
    token=get_Token();
    if(Token[pos+2]==";"||Token[pos+2]=="[")
    {
        c = new grammer_tree("var_declaration");
        c = var_declaration(c);
        if (c->child_size() > 0)
            root->insert_tree(c);
    }
    else if (Token[pos + 2] == "(")
    {
        c = new grammer_tree("fun_declaration");
        c = fun_declaration(c);
        if (c->child_size() > 0)
            root->insert_tree(c);
    }
    return root;
}

grammer_tree* grammer_analysis::var_declaration(grammer_tree* root)
{
/*
    var_declaration->type_specifier ID;|type_specifier ID[NUM];
*/
    grammer_tree* c;
    root = simple_declaration(root);
    if (token == ";")
    {
        c = match(";");
        token = get_Token();
        root->insert_tree(c);
    }
    else if (token == "[")
    {
        c = match("[");
        token = get_Token();
        root->insert_tree(c);

        c = match("NUM");
        token = get_Token();
        root->insert_tree(c);

        c = match("]");
        token = get_Token();
        root->insert_tree(c);

        c = match(";");
        token = get_Token();
        root->insert_tree(c);
    }
    return root;
}

grammer_tree* grammer_analysis::fun_declaration(grammer_tree* root)
{
/*
    fun_declaration->type-specifier ID(params) compound-stmt    
*/
    grammer_tree* c;
    root = simple_declaration(root);

        c = match("(");
        token = get_Token();
        root->insert_tree(c);

        c = new grammer_tree("params");
        c = params(c);
        if (c->child_size() > 0)
            root->insert_tree(c);

        c = match(")");
        token = get_Token();
        root->insert_tree(c);

        c = new grammer_tree("compound-stmt");
        c = compound_stmt(c);
        if (c->child_size() > 0)
        root->insert_tree(c);
        
    
    return root;
}

grammer_tree* grammer_analysis::type_specifier()
{
/*
    type_specifier->int|void
*/
    if(token=="int")
    {
        token=get_Token();
        return match("int");
    }
    if(token=="void")
    {
        token=get_Token();
        return match("void");
    }
}

grammer_tree* grammer_analysis::params(grammer_tree* root)
{
/*
    params->param_list|void
*/
    grammer_tree* c;

    if(token=="void")
    {
        if(label[pos]!="identifier")
        {
            c=match("void");
            token=get_Token();
            root->insert_tree(c);
        }
        else
        {
            c=new grammer_tree("params_list");
            c=param_list(c);
            if(c->child_size()>0)
            root->insert_tree(c);
        }
    }
    else
    {
        c=new grammer_tree("params_list");
        c=param_list(c);
        if(c->child_size()>0)
        root->insert_tree(c);
    }
    return root;
}

grammer_tree* grammer_analysis::param_list(grammer_tree* root)
{
/*
    param_list->param param_list_1
    param_list_1->,param param_list_1|empty
*/
     grammer_tree* c;

     c=new grammer_tree("param");
     c=param(c);
     if(c->child_size()>0)
     root->insert_tree(c);

    root=param_list_1(root);
     return root;
}

grammer_tree* grammer_analysis::param_list_1(grammer_tree* root)
{
     grammer_tree* c;
     if(token==",")
     {
         c=match(",");
         token=get_Token();
         root->insert_tree(c);

         c=new grammer_tree("param_list");
         c=param_list(c);
         if(c->child_size()>0)
         root->insert_tree(c);
     }
     return root;
}

grammer_tree* grammer_analysis::param(grammer_tree* root)
{
/*
    param->simple_declaration empty|[]
*/
     grammer_tree* c;

     root=simple_declaration(root);

     if(token=="[")
     {
         c=match("[");
         token=get_Token();
         root->insert_tree(c);

         c=match("]");
         token=get_Token();
         root->insert_tree(c);
     }
     return root;
}

grammer_tree* grammer_analysis::compound_stmt(grammer_tree *root)
{
/*
    compound_stmt->{local_declarations statement_list}
*/
        grammer_tree* c;
        c=match("{");
        token=get_Token();
        root->insert_tree(c);

        c=new grammer_tree("local_declarations");
        c=local_declarations(c);
        if(c->child_size()>0)
        root->insert_tree(c);

        c=new grammer_tree("statement_list");
        c=statement_list(c);
        if(c->child_size()>0)
        root->insert_tree(c);

        c=match("}");
        token=get_Token();
        root->insert_tree(c);

        return root;
}

grammer_tree* grammer_analysis::local_declarations(grammer_tree* root)
{
/*
    local_declarations->var_declaration local_declarations | empty
*/
    grammer_tree* c;
    if(token=="int"||token=="void")
    {
    root=simple_declaration(root);
    if(token==";")
    {
        c=match(";");
        token=get_Token();
        root->insert_tree(c);
    }
    else if(token=="[")
    {
        c=match("[");
        token=get_Token();
        root->insert_tree(c);

        c=match("NUM");
        token=get_Token();
        root->insert_tree(c);

        c=match("]");
        token=get_Token();
        root->insert_tree(c);
    }


    root=local_declarations(root);

    }
    return root;
}

grammer_tree* grammer_analysis::statement_list(grammer_tree* root)
{
/*
    statement_list->statement statement-list | empty
*/
     grammer_tree* c;
     if(label[pos]=="identifier"||token=="{"||token=="if"||token=="while"||token=="return")
     {
        c=new grammer_tree("statement");
        c=statement(c);
        if(c->child_size()>0)
        root->insert_tree(c);

        
        root=statement_list(root);
     }
     return root;
}


grammer_tree* grammer_analysis::statement(grammer_tree* root)
{
/*
    expression->expression_stmt
                |compound_stmt
                |selection_stmt
                |iteration_stmt
                |return_stmt    
*/
    grammer_tree* c;
    if(label[pos]=="identifier")
    {
        c=new grammer_tree("expression_stmt");
        c=expression_stmt(c);
        if(c->child_size()>0)
        root->insert_tree(c);
    }
    else if(token=="{")
    {
        c=new grammer_tree("compound_stmt");
        c=compound_stmt(c);
        if(c->child_size()>0)
        root->insert_tree(c);
    }
    else if(token=="if")
    {
        c=new grammer_tree("selection_stmt");
        c=selection_stmt(c);
        if(c->child_size()>0)
        root->insert_tree(c);
    }
    else if(token=="while")
    {
        c=new grammer_tree("iteration_stmt");
        c=iteration_stmt(c);
        if(c->child_size()>0)
        root->insert_tree(c);
    }
    else if(token=="return")
    {
        c=new grammer_tree("return_stmt");
        c=return_stmt(c);
        if(c->child_size()>0)
        root->insert_tree(c);
    }
    else
    {
        cout<<"ERROR"<<endl;
        exit(1);
    }
    return root;
}


grammer_tree* grammer_analysis::expression_stmt(grammer_tree* root)
{
/*
    expression_stmt->expression;|;
*/
    grammer_tree* c;
    if(label[pos]=="identifier")
    {
        c=new grammer_tree("expression");
        c=expression(c);
        if(c->child_size()>0)
        root->insert_tree(c);

        c=match(";");
        token=get_Token();
        root->insert_tree(c);
    }
    else if(token==";")
    {
        c=match(";");
        token=get_Token();
        root->insert_tree(c);
    }
    else
    {
        cout<<"ERROR"<<endl;
        exit(1);
    }
    return root;
}


grammer_tree* grammer_analysis::selection_stmt(grammer_tree* root)
{
/*
    selection_stmt->if(expression)statement empty|else statement
*/
    grammer_tree* c;

    c=match("if");
    token=get_Token();
    root->insert_tree(c);

    c=match("(");
    token=get_Token();
    root->insert_tree(c);

    c=new grammer_tree("expression");
    c=expression(c);
    if(c->child_size()>0)
    root->insert_tree(c);

    c=match(")");
    token=get_Token();
    root->insert_tree(c);

    c=new grammer_tree("statement");
        c=statement(c);
        if(c->child_size()>0)
        root->insert_tree(c);

    if(token=="else")
    {
        c=match("else");
        token=get_Token();
        root->insert_tree(c);

        c=new grammer_tree("statement");
        c=statement(c);
        if(c->child_size()>0)
        root->insert_tree(c);
    }
    return root;
}


grammer_tree* grammer_analysis::iteration_stmt(grammer_tree* root)
{
/*
    iteration_stmt->while(expression)statement
*/
    grammer_tree* c;

    c=match("while");
    token=get_Token();
    root->insert_tree(c);

    c=match("(");
    token=get_Token();
    root->insert_tree(c);

    c=new grammer_tree("expression");
    c=expression(c);
    if(c->child_size()>0)
    root->insert_tree(c);

    c=match(")");
    token=get_Token();
    root->insert_tree(c);

    c=new grammer_tree("statement");
    c=statement(c);
    if(c->child_size()>0)
    root->insert_tree(c);

    return root;
}

grammer_tree* grammer_analysis::return_stmt(grammer_tree* root)
{
/*
    return_stmt->return;|return expression;
*/
    grammer_tree* c;

    c=match("return");
    token=get_Token();
    root->insert_tree(c);

    if(token==";")
    {
        c=match(";");
        token=get_Token();
        root->insert_tree(c);
    }
    else if(label[pos]=="identifier")
    {
        c=new grammer_tree("expression");
        c=expression(c);
        if(c->child_size()>0)
        root->insert_tree(c);

        c=match(";");
        token=get_Token();
        root->insert_tree(c);
    }

    return root;
}

grammer_tree* grammer_analysis::expression(grammer_tree* root)
{
/*
    expression->var=expression|simple_expression
*/
    grammer_tree* c;
    if(label[pos]=="identifier")
    {
            int flag=pos;//表示是否回溯

            c=new grammer_tree("var");
            c=var(c);
            if(c->child_size()>0)
            root->insert_tree(c);

            if(token=="=")
            {
                c=match("=");
                token=get_Token();
                root->insert_tree(c);

                c=new grammer_tree("expression");
                c=expression(c);
                if(c->child_size()>0)
                root->insert_tree(c);
            }
            else if(token==";")
                return root;
            else if(token=="(")
            {
                pos=flag;
                root->delete_child();
                token=get_Token();

                c=new grammer_tree("simple_expression");
                c=simple_expression(c);
                if(c->child_size()>0)
                root->insert_tree(c);

                if(token==";")
                return root;
            }
            else if(token!=","&&token!=")"&&token!="]")
            {
                pos=flag;
                root->delete_child();
                token=get_Token();

                c=new grammer_tree("simple_expression");
                c=simple_expression(c);
                if(c->child_size()>0)
                root->insert_tree(c);
            }

    }
    if(token=="("||label[pos]=="number")
    {
        c=new grammer_tree("simple_expression");
            c=simple_expression(c);
            if(c->child_size()>0)
            root->insert_tree(c);
    }
    return root;
}

grammer_tree* grammer_analysis::var(grammer_tree* root)
{
/*
    var->ID|ID[expression]
*/
    grammer_tree* c;
    c=match("ID");
    token=get_Token();
    root->insert_tree(c);
    if(token=="[")
    {
        c=match("[");
        token=get_Token();
        root->insert_tree(c);

        c=new grammer_tree("expression");
        c=expression(c);
        if(c->child_size()>0)
        root->insert_tree(c);

        c=match("]");
        token=get_Token();
        root->insert_tree(c);
    }
    return root;
}


grammer_tree* grammer_analysis::simple_expression(grammer_tree* root)
{
/*
    simple_expression->additive_expression empty|relop additive_expression
*/
    grammer_tree* c;

    c=new grammer_tree("additive_expression");
    c=additive_expression(c);
    if(c->child_size()>0)
    root->insert_tree(c);

    if(token=="<="||token=="<"||token==">"||token==">="||token=="=="||token=="!=")
    {
        c=new grammer_tree("relop");
        c=relop(c);
        if(c->child_size()>0)
        root->insert_tree(c);

        c=new grammer_tree("additive_expression");
        c=additive_expression(c);
        if(c->child_size()>0)
        root->insert_tree(c);
    }
    
    return root;
}

grammer_tree* grammer_analysis::relop(grammer_tree* root)
{
/*
    relop-><=|<|>|>=|!=|==
*/
    grammer_tree* c;
    if(token=="<=")
    {
        c=match("<=");
        token=get_Token();
        root->insert_tree(c);
    }
    else if(token=="<")
    {
        c=match("<");
        token=get_Token();
        root->insert_tree(c);
    }
    else if(token=="==")
    {
        c=match("==");
        token=get_Token();
        root->insert_tree(c);
    }
    else if(token==">")
    {
        c=match(">");
        token=get_Token();
        root->insert_tree(c);
    }
    else if(token==">=")
    {
        c=match(">=");
        token=get_Token();
        root->insert_tree(c);
    }
    else if(token=="==")
    {
        c=match("==");
        token=get_Token();
        root->insert_tree(c);
    }
    return root;
}

grammer_tree* grammer_analysis::additive_expression(grammer_tree* root)
{
/*
    additive_expression->term additive_expression_1
    additive_expression_1->addop term additive_expression_1 | empty
*/
    grammer_tree* c;
    c=new grammer_tree("term");
    c=term(c);
    if(c->child_size()>0)
    root->insert_tree(c);

    root=additive_expression_1(root);
    return root;
}

grammer_tree* grammer_analysis::additive_expression_1(grammer_tree* root)
{
    grammer_tree* c;
    if(token=="+"||token=="-")
    {
    c=new grammer_tree("addop");
    c=addop(c);
    if(c->child_size()>0)
    root->insert_tree(c);

    c=new grammer_tree("term");
    c=term(c);
    if(c->child_size()>0)
    root->insert_tree(c);

    root=additive_expression_1(root);
    }
    return root;
}

grammer_tree* grammer_analysis::addop(grammer_tree* root)
{
/*
    addop->+|-
*/
    grammer_tree* c;
    if(token=="+")
    {
        c=match("+");
        root->insert_tree(c);
    }
    else if(token=="-")
    {
        c=match("-");
        root->insert_tree(c);
    }
    return root;
}

grammer_tree* grammer_analysis::term(grammer_tree* root)
{
/*
    term->factor term_1
    term_1->mulop factor term_1 |empty
*/
    grammer_tree* c;

    c=new grammer_tree("factor");
    c=factor(c);
    if(c->child_size()>0)
    root->insert_tree(c);

    root=term_1(root);
    return root;
}

grammer_tree* grammer_analysis::term_1(grammer_tree* root)
{
    grammer_tree* c;
    if(token=="*"||token=="/")
    {
        c=new grammer_tree("mulop");
        c=mulop(c);
        if(c->child_size()>0)
        root->insert_tree(c);

        c=new grammer_tree("factor");
        c=factor(c);
        if(c->child_size()>0)
        root->insert_tree(c);

        root=term_1(root);
    }
    return root;
}

grammer_tree* grammer_analysis::mulop(grammer_tree* root)
{
/*
    mulop->*|/
*/
    grammer_tree* c;
    if(token=="*")
    {
        c=match("*");
        root->insert_tree(c);
    }
    else if(token=="/")
    {
        c=match("/");
        root->insert_tree(c);
    }
    return root;
}

grammer_tree* grammer_analysis::factor(grammer_tree* root)
{
/*
    factor->(expression)|NUM|   ID empty|[expression]|(args)
*/
    grammer_tree* c;
    if(token=="(")
    {
        c=match("(");
        root->insert_tree(c);

        c=new grammer_tree("expression");
        c=expression(c);
        if(c->child_size()>0)
        root->insert_tree(c);

        c=match(")");
        root->insert_tree(c);
    }
    else if(label[pos]=="identifier")
    {
        c=match("ID");
        root->insert_tree(c);

        if(token=="[")
        {
            c=match("[");
            root->insert_tree(c);

            c=new grammer_tree("expression");
            c=expression(c);
            if(c->child_size()>0)
            root->insert_tree(c);

            c=match("]");
            root->insert_tree(c);
        }
        else if(token=="(")
        {
            c=match("(");
            root->insert_tree(c);

            c=new grammer_tree("args");
            c=args(c);
            if(c->child_size()>0)
            root->insert_tree(c);

            c=match(")");
            root->insert_tree(c);
        }
    }
    else if(label[pos]=="number")
    {
        c=match("NUM");
        root->insert_tree(c);
    }
    return root;
}


grammer_tree* grammer_analysis::args(grammer_tree* root)
{
/*
    args->arg_list|empty
*/
    grammer_tree* c;
    if(label[pos]=="identifier")
    {
        c=new grammer_tree("arg_list");
        c=arg_list(c);
        if(c->child_size()>0)
        root->insert_tree(c);
    }
    return root;
}

grammer_tree* grammer_analysis::arg_list(grammer_tree* root)
{
/*
    arg_list->expression arg_list_1
    arg_list_1->,expression arg_list_1 | empty
*/
    grammer_tree* c;
    c=new grammer_tree("expression");
    c=expression(c);
    if(c->child_size()>0)
    root->insert_tree(c);

    root=arg_list_1(root);

    return root;
}

grammer_tree* grammer_analysis::arg_list_1(grammer_tree* root)
{
    grammer_tree* c;
    if(token==",")
    {
        c=match(",");
        root->insert_tree(c);
        c=new grammer_tree("expression");
        c=expression(c);
        if(c->child_size()>0)
        root->insert_tree(c);

        root=arg_list_1(root);
    }
    return root;
}

