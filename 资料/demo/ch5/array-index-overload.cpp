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
//array-index-overload.cpp

#include <iostream>
#include <initializer_list>

using value_type = int;

//一维数组
class arr {
public:
    using value_type = ::value_type;
    using pointer = value_type*;
    using reference = value_type&;

private:
    size_t len;
    pointer a;

public:
    arr(size_t l = 1) : len(l), a(new value_type[l]) {}
    arr(std::initializer_list<value_type> l) : arr(l.size()) {
        auto p = a;
        for (auto&& e : l) *p++ = e;
    }
    ~arr() { delete[] a; }

    //访问方式：a[i]
    reference operator[](size_t i) try {
        if (i >= len) throw "arr: index out of range";

        return a[i];
    } catch (const char *errmsg) {
        std::cout << errmsg << std::endl;
        exit(1);
    }
};

//二维数组
class arr2D {
public:
    using value_type = ::value_type;
    using pointer = value_type*;
    using reference = value_type&;

private:
    size_t row, col;
    pointer a; //二维数组压缩存储到一个一维数组中

public:
    arr2D(size_t r, size_t c, std::initializer_list<value_type> l) : row(r), col(c), a(new value_type[r * c]) {
        auto p = a;
        for (auto&& e : l) *p++ = e;
    }
    ~arr2D() { delete[] a; }

    //访问方式：a[r, c]
    reference operator[](size_t r, size_t c) try {
        if (r >= row || c >= col) throw "arr2D: index out of range";

        return a[r * col + c];
    } catch (const char *errmsg) {
        std::cout << errmsg << std::endl;
        exit(1);
    }
};

int main() {
    arr a{1, 2, 3, 4, 5};
    std::cout << a[2] << std::endl;

    arr2D b{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    std::cout << b[1, 2] << std::endl;

    std::cout << b[3, 5] << std::endl; //will throw exception

    return 0;
}
