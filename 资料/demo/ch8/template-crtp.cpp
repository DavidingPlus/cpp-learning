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
//template-crtp.cpp

#include <iostream>

template <typename T>
struct base {
    void interface() {
        std::cout << "Base: interface" << std::endl;
        auto p = static_cast<T *>(this);
        p->implement();
    }

    void implement() {
        std::cout << "Base: implement()" << std::endl;
    }
};

struct derived : public base<derived> { //!!!
    void implement() {
        std::cout << "Derived: implement()" << std::endl;
    }
};

int main() {
    derived d;
    base<derived> *p = &d;
    p->interface();
}