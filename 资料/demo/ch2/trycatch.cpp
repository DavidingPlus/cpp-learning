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
//trycatch.cpp

#include <iostream>

int mod(int e1, int e2) {
    if (e1 == 0) throw int(e1);
    if (e2 == 0) throw long(e2);

    return e1 % e2;
}

int main() {
    int e1, e2;

    while (true) {
        std::cout << "please input two numbers:" << std::endl;
        std::cin >> e1 >> e2;
        if (e1 + e2 == 0) break;

        try {
            std::cout << e1 << " mod " << e2 << " = " << mod(e1, e2) << std::endl;
        } catch (int) { //因为本异常处理器不需要异常对象的值，所以只需要类型
            std::cout << "It doesn’t make sense when numerator is 0." << std::endl;
        } catch (long) {
            std::cout << "Denominator cannot be zero." << std::endl;
        } catch (...) {
            std::cout << "unknown exception." << std::endl;
        }
    }

    std::cout << "It's done." << std::endl;

    return 0;
}
