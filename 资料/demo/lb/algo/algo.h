/**
 * @file algo.h
 * @author 白忠建 (baizj@uestc.edu.cn)
 * @brief 泛型算法
 * @version 0.1
 * @date 2023-11-01
 * 
 * @copyright Copyright (C) 2023 白忠建. All rights reserved.
 * 
 */


#pragma once

#include "../iterator/iterator.h"

// 可调用对象

/**
 * @brief 大于functor
 * 
 * @tparam value_type 值的类型
 */
template <typename value_type>
struct gt {
    gt(value_type const& v) : t(v) {}

    constexpr bool operator()(value_type const& w) {
        return w > t;
    }
    
private:
    value_type t;
};


/**
 * @brief 乘法二元操作对象
 * 
 * @tparam value_type 基础类型
 */
template <typename value_type>
struct multiply {
    constexpr value_type operator()(value_type const& a, value_type const& b) {
        return a * b;
    }
};

// 泛型算法
// 0. 不用迭代器的算法

/**
 * @brief 打印任意类型值列表
 * 
 * @tparam types 变长类型参数包
 * @param args 变长参数包
 * @return auto 参数包中参数的个数 
 */
template <typename ...types>
auto print_any(types&& ...args) {
    (std::cout << ... << args);
    return sizeof...(args);
}

// 1. 只带一对迭代器的算法

/**
 * @brief 打印范围里的所有元素
 * 
 * @tparam iterator 前向迭代器类型
 * @param first 范围起点迭代器
 * @param last 范围终点迭代器
 * @param end 行尾结束符。默认为换行
 */
template <Forward_iterator iterator>
void print_range(iterator first, iterator last, char end = '\n') {
    for (auto itr = first; itr != last; ++itr) {
        std::cout << *itr << ' ';
    }
    std::cout << end;
}

/**
 * @brief 打印范围里的所有元素
 * 
 * @tparam range 范围类型。容器就是一种范围
 * @param r 范围
 * @param end 行尾结束符。默认为换行
 */
template <Iterable range>
void print_range(range r, char end = '\n') {
    print_range(r.begin(), r.end(), end);
}


// 2. 带一对迭代器和附加类型的算法

/**
 * @brief 统计范围内的等于指定值的元素的个数 
 * 
 * @tparam iterator 前向迭代器类型
 * @param first 范围起点迭代器
 * @param last 范围终点迭代器
 * @param value 指定值
 * @return auto difference_type 满足条件的元素个数
 */
template <Forward_iterator iterator>
auto count(iterator first, iterator last, typename iterator_traits<iterator>::value_type const& value) {
    typename iterator_traits<iterator>::difference_type c = {};
    for (auto itr = first; itr != last; ++itr) {
        if (*itr == value) { ++c; }
    }
    return c;
}

/**
 * @brief 计算范围内所有元素的累计值
 * 
 * @tparam iterator 前向迭代器类型
 * @param first 范围起点迭代器
 * @param last 范围终点迭代器
 * @param init 累计初始值
 * @return auto 累计值
 */
template <Forward_iterator iterator>
auto accumulate(iterator first, iterator last, typename iterator_traits<iterator>::value_type const& init = {}) {
    auto sum = init;
    for (auto itr = first; itr != last; ++itr) {
        sum = std::move(sum) + *itr;
    }
    return sum;
}

/**
 * @brief 计算范围内所有元素的累计值
 * 
 * @tparam iterator 前向迭代器类型
 * @param first 范围起点迭代器
 * @param last 范围终点迭代器
 * @param init 累计初始值
 * @param op 二元运算符对象
 * @return auto 累计值
 */
template <Forward_iterator iterator, typename operate>
auto accumulate(iterator first, iterator last, 
    typename iterator_traits<iterator>::value_type const& init, operate&& op) {
    auto sum = init;
    for (auto itr = first; itr != last; ++itr) {
        sum = op(sum, *itr);
    }
    return sum;
}


// 3. 带一对迭代器和谓词的算法

/**
 * @brief 统计范围内的满足条件的元素的个数 
 * 
 * @tparam iterator 前向迭代器类型
 * @tparam predicate 谓词类型
 * @param first 范围起点迭代器
 * @param last 范围终点迭代器
 * @param pred 谓词
 * @return auto difference_type 满足条件的元素个数
 */
template <Forward_iterator iterator, Callable<typename iterator_traits<iterator>::value_type> predicate>
auto count_if(iterator first, iterator last, predicate&& pred) {
    typename iterator_traits<iterator>::difference_type c = {};
    for (auto itr = first; itr != last; ++itr) {
        if (pred(std::forward<typename iterator_traits<iterator>::value_type>(*itr))) { ++c; }
    }
    return c;
}