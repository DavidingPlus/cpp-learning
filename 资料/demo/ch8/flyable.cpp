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
//flyable.cpp

#include <iostream>
#include <string>

template <typename ...types>
void print(types ...args) {
    (std::cout << ... << args);
    std::cout << std::endl;
}

//traits
struct flyable {
    virtual void fly() = 0;
};

struct named {
    std::string my_name;
    named(std::string n) : my_name(n) {}
};

//interfaces
struct animal {};
struct plant {};
struct manmade {};

//implements
struct sparrow : public animal, public flyable, public named {
    using named::named;
    void fly() {
        print(my_name, ":I wanna fly high but I cant...");
    }
};

struct plane : public manmade, public flyable, public named {
    using named::named;
    void fly() {
        print(my_name, ":crusing up above 30000 feet...");
    }
};

struct dandelion : public plant, public flyable, public named {
    using named::named;
    void fly() {
        print(my_name, ":floating, floating...");
    }
};

int main() {
    sparrow("sparrow").fly();
    dandelion("dandelion").fly();
    plane("Boeing 747").fly();
    return 0;
}
