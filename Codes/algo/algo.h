/**
 * @file algo.h
 * @author 白忠建 (baizj@uestc.edu.cn)
 * @brief 泛型算法的实现
 * @version 0.1
 * @date 2023-11-01
 * 
 * @copyright Copyright (C) 2023 白忠建. All rights reserved.
 * 
 */

#pragma once

#include "../iterator/iterator.h"

// ==============================================================================
// 可调用对象
// ==============================================================================

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

// ==============================================================================
// 泛型算法
// ==============================================================================

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


// 2. 带一对迭代器和附加类型的算法


// 3. 带一对迭代器和谓词的算法