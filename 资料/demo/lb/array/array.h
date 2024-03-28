//array.h

#pragma once

#include <iostream>
#include <initializer_list>
#include <format>
#include <exception>
#include <memory>

/*
    @brief  数组类。
*/
template <typename value_t, size_t capacity>
class array {
public:
    /*
        @brief  定义内部类型，以便与外部类型隔离。
    */
    using value_type = value_t;
    using pointer = value_type*;
    using reference = value_type&;
    using constref = value_type const &; // 值的常量左值引用类型

private:
    // pointer a = nullptr; // 内部数组（指针）
    // size_t capacity = 0; // 数组容量
    value_type a[capacity];

protected:

public:
    // 默认构造函数
    array() noexcept = default;

    // 花括号初始化列表构造函数。使用了构造函数委托。
    array(std::initializer_list<value_type> const& l) noexcept {
        for (auto p = a; auto& v : l) *p++ = v;
    }

    // 复制构造函数
    array(array const& l) {
        auto p = a, q = l.a;
        for (auto i = 0uz; i < capacity; ++i) *p++ = *q++;
    }

    // 转移复制构造函数
    array(array&& l) = delete;
    // : array() {
    //     std::swap(a, l.a);
    //     std::swap(capacity, l.capacity);
    // }

    // 析构函数
    ~array() noexcept {
        // delete[] a;
    }

    // 重载的赋值运算符函数
    array& operator=(array const& l) {
        auto p = a, q = l.a;
        for (auto i = 0uz; i < capacity; ++i) *p++ = *q++;

        return *this;
    }

    // 重载的转移赋值运算符函数
    array& operator=(array&& l) = delete;
    // {
    //     std::swap(a, l.a);
    //     std::swap(capacity, l.capacity);

    //     return *this;
    // }

    // 获取数组容量的常成员函数
    size_t size() const {
        return capacity;
    }

    /*
        @brief  获取指定下标下的元素（引用）。下标超界抛出异常
        @param  i：下标
        @return reference（左值）
    */
    reference at(size_t i) try {
        if (i >= capacity) 
            throw std::out_of_range(std::format("index {} was out of bound", i));

        return a[i];
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
        exit(1);
    }

    reference operator[](size_t i) try {
        if (i >= capacity) 
            throw std::out_of_range(std::format("index {} was out of bound", i));

        return a[i];
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
        exit(1);
    }

    // 回调函数类型。这种类型的函数带有一个值引用作为参数，无返回值。
    using callback_t = void (reference);

    /*
        @brief  遍历链表，访问结点数据。
        @param  visit：回调函数
        @return void
    */
    void traverse(callback_t visit) {
        for (auto i = 0uz; i < capacity; ++i) visit(a[i]);
    }

    // 引用限定的成员。当this对象是持久对象时调用。
    // auto get_a() & {
    //     return a;
    // }

    // 引用限定的成员。当this对象是将亡对象时调用。
    // auto get_a() && {
    //     auto p = a;
    //     a = nullptr;
    //     // 返回一个智能指针。智能指针是对原生指针的包装；在析构时将释放原生指针
    //     return std::shared_ptr<value_type>(p, std::default_delete<value_type[]>());
    // }

    // // 友元函数。一个类的友元可以直接访问类的所有成员
    // // 仅处于效率上的考虑
    template <typename T, size_t s>
    friend pointer gget_a(array<T, s>& a);

    using iterator = pointer;

    iterator begin() {
        return a;
    }

    iterator end() {
        return a + capacity;
    }
};