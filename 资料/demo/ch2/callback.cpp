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
//callback.cpp

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <format>

using value_type = unsigned;
using pointer = value_type*;
using reference = value_type&;

using callback_t = void (reference);
using predicate_t = bool (value_type);

//callback
void randv(reference v) { v = rand() % 100; }

// void array_traverse(pointer a, size_t len, void callback(reference)) {
void array_traverse(pointer a, size_t len, callback_t callback) {
    for (auto i = 0uz; i < len; ++i) callback(a[i]);
}

//predicate
[[nodiscard]] bool gt50(value_type v) { return v > 50; }

// size_t countif(pointer a, size_t len, bool pred(value_type)) {
[[nodiscard]] size_t countif(pointer a, size_t len, predicate_t pred) {
    auto count = 0uz;
    for (auto i = 0uz; i < len; ++i) if (pred(a[i])) ++count;
    return count;
}

int main () {
    srand(static_cast<value_type>(time(nullptr)));

    const auto len = 5uz;
    value_type a[len];

    //fill array
    array_traverse(a, len, randv);
    //print array, using lambda
    array_traverse(a, len, [](reference v) { std::cout << v << ' '; });

    std::cout << std::format("\nCount of greater than 60: {}\nCount of greater than 20: {}\n", 
    countif(a, len, gt50), 
    countif(a, len, [](value_type v) { return v > 20; }));

    return 0;
}
