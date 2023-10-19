#ifndef _ADD_H_
#define _ADD_H_

// #include <iostream>

// bool类型加法没有意义
// 定义一个bool类型的常量表达式，判断T类型是否是bool类型，我们用变量模板来实现
template <typename T>
inline constexpr bool is_boolean = false;

// 将bool类型特化
template <>
inline constexpr bool is_boolean<bool> = true;

// 概念，一般都是模板
// 概念是一个编译器元素，约束一个类型，比如这里requires关键字就指定了这个类型定义了加法运算
// 定义了加法返回true，反之false
template <typename T>
concept Addable = requires(T x) { x + x; } and not is_boolean<T>;  // 用add连接约束

// 写法1:
// template <typename T>
//    requires Addable<T>  // 说明这个类型要经过Addable的语义约束
// 写法2:(建议用这个，语义非常清晰)
template <Addable T>
auto add(T a, T b) {
    // static int num = 0;
    // std::cout << num++ << std::endl;  // 我们看add()实例出来了几份，如果两份各是各的，如果是一份，那么是一个num

    return a + b;
}

#endif
