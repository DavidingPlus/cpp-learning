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
//linked-list-module1.cxx
//链表操作的实现

module linkedlist3case;

void init(linked_list &l) {
    l.head = l.tail = nullptr;
    l.size = 0;
}

void push_back(linked_list &l, value_t d) {
    node_ptr p = new _node{d, nullptr};

    if (l.head == nullptr) l.head = p;
    else l.tail->next = p;
    l.tail = p;

    ++l.size;
}

void clear(linked_list &l) {
    for (node_ptr p;  l.head != nullptr;) {
        p = l.head;
        l.head = l.head->next;
        delete p;
    }

    l.tail = l.head = nullptr;
    l.size = 0;
}

size_t size(linked_list &l) {
    return l.size;
}
