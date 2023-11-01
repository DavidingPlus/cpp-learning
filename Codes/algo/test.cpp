/**
 * @file test.cpp
 * @author 白忠建 (baizj@uestc.edu.cn)
 * @brief 泛型算法的测试
 * @version 0.1
 * @date 2023-11-01
 * 
 * @copyright Copyright (C) 2023 白忠建. All rights reserved.
 * 
 */

#include <iostream>
#include <format>

#include "algo.h"
#include "../dlist/dlist.h"
#include "../array/array.h"

#include "foo.h"

/**
 * @brief 测试泛型算法 
 * 
 * @tparam iterator 迭代器类型
 * @tparam gt_fn 谓词类型
 * @tparam T 值类型
 * @param range_name 范围标题
 * @param first 范围起点迭代器
 * @param last 范围终点迭代器
 * @param gtf 谓词对象。用于count_if算法
 * @param val 值对象。用于count算法
 */
template <typename iterator, typename gt_fn, typename T>
void test(const char *range_name, iterator first, iterator last, gt_fn&& gtf, T const& val) {
    print_any(range_name, '\n');

    print_range(first, last);

    print_any(
        // "count=", count(first, last, val), 
        // ", count_if=", count_if(first, last - 2, std::forward<gt_fn>(gtf)),
        // ", sum=", accumulate(first + 3, last - 3), 
        "\n\n"
    );
}

int main() {
    // 用dlist测试
    dlist<int> l{1, 8, 5, 3, 6, 5, 4, 7, 2, 9, 5};
    test("dlist<int>", l.begin(), l.end(), [](auto v) { return v > 3; }, 5);

    dlist<std::string> ls;
    for (auto v : l) ls.push_back(std::format("{}s", v));
    test("dlist<std::string>", ls.begin(), ls.end(), [](auto const& v) { return v > "3s"; }, "5s");

    dlist<foo> lf;
    for (auto v : l) lf.emplace_back(v, v * 0.1);
    test("dlist<foo>", lf.begin(), lf.end(), gt<foo>(foo{3, 0.3}), foo{5, 0.5});

    // // 用原生数组测试
    // constexpr size_t n = 11;
    // float a[n];
    // for (int i = 0; auto v : l) a[i++] = v / 10.0f;
    // test("float a[n]", a, a + n, gt<float>(0.3f), 0.5f);

    // // 用array测试
    // array<long, n> b;
    // for (int i = 0; auto v : l) b[i++] = long(v) * 10l;
    // test("array<long, n>", b.begin(), b.end(), gt<long>(30l), 50l);

    return 0;
}