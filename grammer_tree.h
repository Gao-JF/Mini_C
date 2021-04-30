/**************************************************************
 *                                                            *
 *   Copyright (c) 2021 Gaojunfeng All rights reserved.       *
 *   Version: 1.0                                             *
 *   Author: Gaojunfeng                                       *
 *                                                            *
 *   最后修改日期：2021.04.30                                 *
 *                                                            *
 *   声明了语法树的数据结构，属性包括当前结点、当前结点值、   *
 *   孩子                                                     *
 *                                                            *
 **************************************************************/


#ifndef GRAMMER_TREE_H
#define GRAMMER_TREE_H

#include<vector>
using namespace std;

class grammer_tree
{
public:
    grammer_tree(string d)//构造函数
    {
        data=d;
    }
    grammer_tree() { node = NULL; };//构造函数

    void insert_tree(grammer_tree *c)//给当前结点添加孩子
    {
        child.push_back(c);
    }
    void delete_child()//删除当前结点的最后一个孩子
    {
        child.pop_back();
    }
    int child_size()//返回当前结点孩子的个数
    {
        return child.size();
    }
    string get_data()//返回当前结点值
    {
        return data;
    }
    vector<grammer_tree*> get_child()//返回当前结点的孩子
    {
        return child;
    }
private:
    grammer_tree *node;//结点
    string data;//当前结点值
    vector<grammer_tree*>child;//当前结点的孩子
};

#endif