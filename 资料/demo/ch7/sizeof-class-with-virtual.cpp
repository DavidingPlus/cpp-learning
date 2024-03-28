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
//sizeof-class-with-virtual.cpp

#include <iostream>

class alignas(8) noVirtual {
    char a;
    void f() {}
};

class alignas(8) oneVirtual {
    char a;
    virtual void f() {}
};

class alignas(8) manyVirtual {
    char a;
    virtual void f() {}
    virtual int g() {
        return 0;
    }
    virtual double h(double) {
        return 1.0;
    }
};

int main() {
    std::cout << "size of noVirtual: " << sizeof(noVirtual) << std::endl;
    std::cout << "size of oneVirtual: " << sizeof(oneVirtual) << std::endl;
    std::cout << "size of manyVirtual: " << sizeof(manyVirtual) << std::endl;
    std::cout << "ref: size of pointer: " << sizeof(void *) << std::endl;
    return 0;
}
