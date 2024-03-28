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
//inherited-constructor.cpp

#include <iostream>
#include <string>

class B {
protected:
    char name;
    void info(std::string msg) {
        std::cout << name << ": " << msg << std::endl;
    }
public:
    B(char n = 'B') : name(n) {
        info("default constructor");
    }
    B(int, char n = 'B') : name(n) {
        info("int constructor");
    }
    B(const B &b) : name(b.name) {
        info("copy constructor");
    }
    B(B &&b) : name(b.name) {
        info("move copy constructor");
    }
    B &operator=(const B &) {
        info("operator=()");
        return *this;
    }
    B &operator=(B &&) {
        info("move operator=()");
        return *this;
    }
};

class D : public B {
public:
    using B::B; //constructors inherit
};

int main() {
    D d1{'D'}, d2{1, 'D'}, d3{d2}, d4{std::move(d1)};
    d1 = d2;
    d3 = std::move(d4);
    return 0;
}
