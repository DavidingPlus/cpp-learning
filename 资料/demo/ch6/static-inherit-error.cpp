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
//static-inherit-error.cpp

#include <iostream>

class A {
public: static int i;
};
int A::i = 0;

class B : private A {
public:
    int f() {
        return A::i;    //OK, but i is private for B
    }
};

class C : public B {
public:
    int g() {
        return A::i; //error, B的继承将i私有化
        return B::i; //error, 被替换成A::i, 但在B中是private
    }
};

int main() {
    std::cout << A::i; //OK, i is public in A
    std::cout << B::i; //error, 被替换成A::i, 但在B中是private
    return 0;
}

