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
//redefine-member.cpp

#include <iostream>
#include <string>
using std::string;

class base {
protected:
    string name;

public:
    base() {
        name = "base";
    }

    void whoami() {
        std::cout << name << std::endl;
    }
};

class derived: public base {
protected:
    string name; //重定义成员。这个成员与基类的同名成员不同。因此，在derived内部，有两个name成员。

public:
    derived() : base() {
        name = "derived";    //初始化派生类自己的
    }

    string get_name() const {
        return name;    //获取派生类自己的
    }
};

class derived2: public base {
public:
    derived2() : base() {
        name = "derived";    //初始化基类的，也就是派生类继承的
    }

    string get_name() const {
        return name;    //获取基类的，也就是派生类继承的
    }
};

//也许是最佳方案
class base2 {
protected:
    string name;

public:
    base2(string n = "base") : name(n) {}

    void whoami() {
        std::cout << name << std::endl;
    }
};

class derived3: public base2 {
public:
    derived3(string n = "derived") : base2(n) {} //激活基类的构造函数来完成初始化

    string get_name() const {
        return name;
    }
};

int main() {
    derived d;
    d.whoami();
    std::cout << d.get_name() << std::endl;

    // derived2 d2;
    // d2.whoami();
    // std::cout << d2.get_name() << std::endl;

    // derived2 d3;
    // d3.whoami();
    // std::cout << d3.get_name() << std::endl;

    return 0;
}