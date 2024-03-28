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
//linked-list-main.cpp
//链表测试代码

import <iostream>;
import linkedlist3case;

int main() {
    value_t a[] = {1, 2, 3, 4, 5};
    linked_list l;

    init(l); //对象的初始化很重要！
    for (auto e : a) push_back(l, e);

    for (auto p = l.head; p != nullptr; p = p->next)
        std::cout << p->data << ' ';

    std::cout << std::endl << l.size;

    clear(l); //对象失效前的清理工作也很重要！

    return 0;
}
