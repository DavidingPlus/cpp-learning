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
//object-copy.cpp

#include <iostream>

int main() {
    struct X {int a; double b;};
    X o1{1, 2.3}; //定义对象并初始化
    X o2{o1};  //初始化，o2是o1的复制品。等价于X o2 = o1
    X o3;

    o3 = o1; //赋值，同样是复制
    std::cout << o1.a << ' ' << o1.b << std::endl;
    std::cout << o2.a << ' ' << o2.b << std::endl;
    std::cout << o3.a << ' ' << o3.b << std::endl;

    return 0;
}
