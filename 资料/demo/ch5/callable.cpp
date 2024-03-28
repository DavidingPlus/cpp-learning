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
//callable.cpp

#include <iostream>
#include <functional>

int f() {
    return 0;    //函数
}

class foo { //重载了()的类
private:
    int x = 1;
public:
    int operator()() {
        return x;
    }
};

void g(std::function<int ()> fn) {
    std::cout << fn() << std::endl;
}

int main() {
    int a = 2;
    foo x;

    g(f); //函数作为参数
    g([=]->int { return a; }); //lambda作为参数
    g(x); //函数对象作为参数

    return 0;
}
