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
//pi-case.cpp

#include <iostream>
#include <string>

const double pilf = 3.1415926536;
const int pii = 3;
const char * pis = "3.1415926536";

int main()
{
    std::cout << 1.2 * 1.2 * pilf << std::endl;
    std::cout << 2 * 2 * pii << std::endl;
    std::cout << std::string("3 * 3 * ") + pis << std::endl;

    return 0;
}
