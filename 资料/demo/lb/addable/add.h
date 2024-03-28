#pragma once

// #include <iostream>

template <typename T>
inline constexpr bool is_boolean = false;

template <>
inline constexpr bool is_boolean<bool> = true;

template <typename T>
concept Addable = requires (T x) { x + x; } and not is_boolean<T>;

// template <typename T>
// requires Addable<T>
template <Addable T>
auto add(T a, T b) {
    // static int c = 0;
    // std::cout << c++ << std::endl;

    return a + b;
}