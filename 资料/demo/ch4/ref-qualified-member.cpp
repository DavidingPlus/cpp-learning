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
//ref-qualified-member.cpp

#include <iostream>
#include <array>

class X {
    std::array<int, 3> data{2, 3, 4};

public:
    ~X() { std::cout << "~X()\n"; }

    //for lvalues
    auto& items() & { std::cout << "items() &\n"; return data; }

    //for rvalues, by value
    auto items() && { std::cout << "items() &&\n"; return data; }
};

int main() {
    X x;

    [[maybe_unused]] auto d1 = x.items();
    [[maybe_unused]] auto d2 = std::move(x).items();

    return 0;
}
