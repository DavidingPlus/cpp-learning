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
//literal.cpp

#include <iostream>
#include <cmath>
#include <format>

//用户自定义字面常量。这实际上是个运算符函数。
//功能：将度数转换为弧度数。
long double operator"" _d2r(long double degree) {
    return degree * 3.1415926 / 180.0;
}

int main() {
    //带千分位分隔符的二进制常量
    int a = 0b1'010'101;
    //普通字符串，其中\n是转义字符
    const char *s1 = "one\ntwo";
    //原始字符串。*是分隔符。符号串\n不再是转义字符，而是它们本身
    const char *s2 = R"*(one\ntwo)*";
    //utf-8编码的字符串
    const char8_t *s3 = u8"Unicode Characters: \u4e2d\u6587";

    std::cout << std::format("a={}\nsin(30deg)={:.5f}, sin(30rad)={:.5f}\ns1={}\ns2={}\ns3={}\n", 
    a,
    sin(30.0),
    sin(30.0_d2r),
    s1,
    s2,
    reinterpret_cast<const char*>(s3));

    return 0;
}
