/* 
 * Copyright (c) 2023 白忠建 电子科技大学信息与软件工程学院
 * 现代C++程序设计课程源码及其构建系统 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2. 
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2 
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details. 
 */


//bzj^_^
//project: linked-list-case
//linked-list-module0.cxx。模块接口声明

export module linkedlist3case; //对外暴露模块

import <iostream>; 

export {

//链表相关类型声明并对外暴露
using value_t = int; //类型别名
struct _node { //节点类型定义
    value_t data;
    _node *next;
};
using node_ptr = _node *; //类型别名

struct linked_list {
    node_ptr head, tail; //头尾指针
    size_t size; //节点数目
};

//链表的操作：原型声明，并对外暴露
//初始化链表
void init(linked_list &l);
//在链表尾部添加数据
void push_back(linked_list &l, value_t d);
//清空链表
void clear(linked_list &l);
//获取链表的节点数
size_t size(linked_list &l);

};
