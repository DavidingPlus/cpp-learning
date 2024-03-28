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
//range-view.cpp

// #include <iostream>
// #include <ranges>

#include <iostream>
#include <ranges>

int main() {
    auto const a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto odd = [](int i) { return i % 2 == 1; };

    for (auto i : a | std::views::filter(odd) | std::views::transform([](int k) { return k * k; }))
        std::cout << i << std::endl;

    return 0;
}