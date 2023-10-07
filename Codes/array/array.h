// array.h
#ifndef _array_H_
#define _array_H_

#include <exception>
#include <format>
#include <initializer_list>
#include <iostream>
#include <memory>

using value_type = int;

class array {
public:
    /**
     * @brief 定义一些类型
     */
    using value_type = ::value_type;
    using pointer = value_type*;
    using reference = value_type&;
    using constref = const value_type&;

public:
    /**
     * @brief 默认构造函数
     */
    array(size_t n = 0) noexcept {
        _init(n);
    }

    /**
     * @brief 构造函数，后面放了一个构造函数委托，在这个函数执行之前先执行被委托的函数
     */
    array(const std::initializer_list<value_type>& l) noexcept : array(l.size()) {
        auto p = data;
        for (auto& v : l)
            *p++ = v;
    }

    /**
     * @brief 析构函数
     */
    ~array() noexcept {
        _clear();
    }

    /**
     * @brief 拷贝构造函数，因为类成员里面含有指针
     * @param other，另一个对象
     */
    array(const array& other) noexcept {
        *this = other;
    }

    /**
     * @brief 拷贝赋值函数，理由同上
     * @param other，另一个对象
     * @return array类型的对象引用
     */
    array& operator=(const array& other) noexcept {
        // 检测自我赋值
        if (this == &other)
            return *this;

        // 杀死原来的
        _clear();
        // 重新初始化
        _init(other.size());

        // 深拷贝
        auto p = data, q = other.data;
        for (size_t i = 0; i < capacity; ++i)
            *p++ = *q++;

        return *this;
    }

    /**
     * @brief 移动构造函数，处理右值引用的将亡对象
     */
    array(array&& other) noexcept {
        *this = other;
    }

    /**
     * @brief 移动拷贝函数，同上
     * @param other，另一个对象
     * @return array类型的对象引用
     */
    array& operator=(array&& other) noexcept {
        // 移动构造不用下面的两个代码会报错：array l(l2);
        // 为了让移动构造不报错，我还是先清空，反正会被将亡对象清除
        _clear();
        _init(other.size());

        // 将对象交换，让将亡对象释放掉我之前的资源，然后我托管对方的资源
        std::swap(data, other.data);
        std::swap(capacity, other.capacity);

        return *this;
    }

public:
    /**
     * @brief 获取数组的长度
     */
    size_t size() const { return capacity; }

    /**
     * @brief 得到数组下标位置的元素
     */
    reference at(int i) try {
        if (i < 0 || (size_t)i >= capacity)
            throw std::out_of_range(std::format("index {} was out of bound.", i));

        return data[i];
    } catch (std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
        exit(-1);
    }

    /**
     * @brief 定义了回调函数的类型，返回值是void，参数是引用类型，可以打印也可以修改内容
     */
    using callback_t = void(reference);

    /**
     * @brief 链表的遍历方法
     * @param visit，回调函数callback_t
     */
    void traverse(callback_t visit) {
        for (size_t i = 0; i < capacity; ++i)
            visit(data[i]);
    }

    /**
     * @brief 得到数组指针
     * @brief 我们要想办法让这个函数识别调用的对象是持久对象还是将亡对象，因为将亡对象调用这个东西会导致内存越界!
     * @brief 在下面加上&表示调用这个函数的是持久对象，学到了!
     */
    pointer get_pointer() & { return data; }

    /**
     * @brief 对应的右值引用的版本
     * @brief 为了让我们返回的指针在使用之后被自动释放，不需要用户释放，所以使用智能指针
     * @brief 第二个参数是一个用来指明删除是delete[]的类的临时对象
     */
    auto get_pointer() && {
        auto p = data;
        data = nullptr;

        return std::shared_ptr<value_type>(p, std::default_delete<value_type[]>());
    }

    /**
     * @brief 这个函数是这个类的友元，可以直接访问这个类的所有成员和函数
     * @param arr，array的类对象，这个参数是必须有的，因为要给外面的函数提供类对象的接口，所以这个类对象是必须有的，这里传入引用
     */
    friend pointer get_pointer2(array& arr);

private:
    /**
     * @brief 初始化函数
     */
    void _init(int n) {
        data = new int[n];
        capacity = n;
    }

    /**
     * @brief 清空函数
     */
    void _clear() {
        delete[] data;

        capacity = 0;
    }

private:
    /**
     * @brief 定义存储数据的数组，用指针代表
     */
    pointer data;

    /**
     * @brief 定义数组的容量
     */
    size_t capacity;
};

#endif
