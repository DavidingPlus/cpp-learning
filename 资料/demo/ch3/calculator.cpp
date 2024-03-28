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
//calculator.cpp

#include <iostream>
#include <string>
#include <format>

class calculator {
    using value_t = int;
    const char endc = '#';

private:
    struct expression {
        value_t lhs, rhs, result;
        char optr;
        std::string result_str;
    } expr;

    bool input() {
        std::cout << "Please input an expression like 2 + 3, or input operator as '#' to exit:" << std::endl;
        std::cin >> expr.lhs >> expr.optr >> expr.rhs;
        return expr.optr != endc;
    }

    void calculate() {
        switch (expr.optr) {
        case '+': expr.result = expr.lhs + expr.rhs; break;
        case '-': expr.result = expr.lhs - expr.rhs; break;
        case '*': expr.result = expr.lhs * expr.rhs; break;
        case '/': expr.result = expr.lhs / expr.rhs; break;
        case '%': expr.result = expr.lhs % expr.rhs; break;
        default:  expr.result_str = "Illegal operator!!!"; return;
        }

        expr.result_str = std::format("{} {} {} = {}", expr.lhs, expr.optr, expr.rhs, expr.result);
    }


    void display() {
        std::cout << expr.result_str << std::endl << std::endl;
    }


public:
    bool doCalc() {
        if (!input()) return false;
        calculate();
        display();
        return true;
    }
};

int main() {
    calculator c;
    while (c.doCalc());
    std::cout << "Good-bye!" << std::endl;

    return 0;
}
