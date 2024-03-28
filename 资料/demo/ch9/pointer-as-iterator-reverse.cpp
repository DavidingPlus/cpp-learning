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
//pointer-as-iterator-reverse.cpp

#include <iostream>
#include <initializer_list>

template <typename T>
class vector {
public:
    using value_type = T;
    using reference = T&;
    using pointer = T*;

private:
    size_t len;
    pointer storage;

public:
    vector(std::initializer_list<value_type> list) : len(0), storage(new value_type[list.size()])
    {
        for (auto e : list) storage[len++] = e;
    }
    ~vector() { delete[] storage; }

    using iterator = pointer;
    constexpr iterator begin() { return storage; }
    constexpr iterator end() { return storage + len; }

    constexpr iterator rbegin() { return storage + len - 1; }
    constexpr iterator rend() { return storage - 1; }
};

int main() {
    vector<int> a{1, 2, 3, 4, 5};
    for (auto itr = a.rbegin(); itr != a.rend(); --itr) 
        std::cout << *itr << ' ';

    return 0;
}
