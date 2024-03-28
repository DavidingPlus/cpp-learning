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
//fold-expression.cpp

#include <iostream>

template <typename ...Args>
auto sum_unaryleft(Args ...args) { return (... + args); }

template <typename ...Args>
auto sum_unaryright(Args ...args) { return (args + ...); }

template <typename ...Args>
auto sum_binaryleft(Args ...args) { return (0 + ... + args); }

template <typename ...Args>
auto sum_binaryright(Args ...args) { return (args + ... + 0); }

template <typename ...Args>
auto sub_unaryleft(Args ...args) { return (... - args); }

template <typename ...Args>
auto sub_unaryright(Args ...args) { return (args - ...); }

int main() {
    std::cout << sum_unaryleft(1, 2, 3) << std::endl;
    std::cout << sum_unaryright(4.5, 5.6, 6.7, 7.8, 8.9) << std::endl;
    std::cout << sum_binaryleft(1, 2.3, 3, 0.5) << std::endl;
    std::cout << sum_binaryright(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
    //std::cout << sum_unaryleft() << std::endl; //error，参数包为空
    std::cout << sum_binaryright() << std::endl; //OK

    std::cout << sub_unaryleft(3, 2, 1) << std::endl;
    std::cout << sub_unaryright(3, 2, 1) << std::endl;

    return 0;
}