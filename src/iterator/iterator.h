/**
 * @file iterator.h
 * @author 白忠建 (baizj@uestc.edu.cn)
 * @brief 迭代器原语、tratis、concept的定义
 * @version 0.1
 * @date 2023-11-01
 *
 * @copyright Copyright (C) 2023 白忠建. All rights reserved.
 *
 */

#pragma once

// ==============================================================================
// 迭代器原语
// ==============================================================================

// 定义输入迭代器类型
struct input_iterator_tag {};
// 定义输出迭代器类型
struct output_iterator_tag {};
// 定义前向迭代器类型
struct forward_iterator_tag : public input_iterator_tag {};
// 定义双向迭代器类型
struct bidirectional_iterator_tag : public forward_iterator_tag {};
// 定义随机访问迭代器类型
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// ==============================================================================
// traits
// ==============================================================================

/**
 * @brief 类型提取trait。用于提取迭代器中类型
 *
 * @tparam iterator 迭代器类型
 */
template <typename iterator>
struct iterator_traits {
    using value_type = iterator::value_type;
    using pointer = iterator::pointer;
    using reference = iterator::reference;
    using difference_type = iterator::difference_type;
    using iterator_category = iterator::iterator_category;
};

/**
 * @brief 类型提取trait：用于原生指针的偏特化模板
 *
 * @tparam value_t 值类型
 */
template <typename value_t>
struct iterator_traits<value_t*> {
    using value_type = value_t;
    using pointer = value_type*;
    using reference = value_type&;
    using difference_type = ptrdiff_t;               // 指定为指针间距离类型
    using iterator_category = forward_iterator_tag;  // 指定为前向迭代器类型
};

// ==============================================================================
// concept
// ==============================================================================

/**
 * @brief 判断T是否为指针类型。对任意类型，先假定结果为false
 *
 * @tparam T 类型参数
 */
template <typename T>
inline constexpr bool is_pointer = false;

/**
 * @brief 上述concept的针对于原生指针的偏特化版本。结果为true
 *
 * @tparam T 类型参数
 */
template <typename T>
inline constexpr bool is_pointer<T*> = true;

/**
 * @brief 判断D类型是否是类型B的派生类。通过尝试能否将D类型指针静态转换为B类型指针完成任务
 *
 * @tparam D 派生类类型
 * @tparam B 基类类型
 */
template <typename D, typename B>
concept Derived_from = requires { static_cast<B*>((D*)nullptr); };

/**
 * @brief 判断给定类型T是否是迭代器类型。通过判断T的内部类型iterator_category是否为某种迭代器原语的子类完成任务
 *
 * @tparam T 类型参数
 * @tparam Iter_tag
 */
template <typename T, typename Iter_tag = input_iterator_tag>
concept Iterator = Derived_from<typename iterator_traits<T>::iterator_category, Iter_tag>;

/**
 * @brief 判断T类型是否是前向迭代器类型
 *
 * @tparam T 类型参数
 */
template <typename T>
concept Forward_iterator = Iterator<T, forward_iterator_tag>;

/**
 * @brief 判断容器|范围是否是可迭代的。原生指针、含有迭代器的类都是可迭代的，同时也是range
 *
 * @tparam T
 */
template <typename T>
concept Iterable = is_pointer<T> or Iterator<typename T::iterator>;

/**
 * @brief 判断类型F是否是可调用对象类型。目前这个版本的实现还非常不完善
 *
 * @tparam F 类型参数
 * @tparam Args 变长类型参数包
 */
template <typename F, typename... Args>
concept Callable = requires(F&& f, Args&&... args) { std::forward<F>(f)(std::forward<Args...>(args...)); };
