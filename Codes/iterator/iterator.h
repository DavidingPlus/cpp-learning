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



// ==============================================================================
// concept
// ==============================================================================
