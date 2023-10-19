// array.h
#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <exception>
#include <format>
#include <initializer_list>
#include <iostream>
#include <memory>

// using value_type = int;

// 在模板参数当中直接指定数组的大小
template <typename value_t, size_t capacity>
class array {
public:
    /**
     * @brief 定义一些类型
     */
    using value_type = value_t;
    using pointer = value_type*;
    using reference = value_type&;
    using constref = const value_type&;

public:
    /**
     * @brief 默认构造函数，改造之后直接使用默认构造
     */
    // array() noexcept {
    //     _init(capacity);
    // }
    array() noexcept = default;

    /**
     * @brief 构造函数，后面放了一个构造函数委托，在这个函数执行之前先执行被委托的函数
     * @param l，初始化列表
     */
    array(const std::initializer_list<value_type>& l) noexcept {
        // TODO
        // 初始化列表的参数个数不和capacity相同时怎么办，需处理
        for (auto p = data; auto& v : l)
            *p++ = v;
    }

    /**
     * @brief 析构函数，改造之后直接使用默认析构
     */
    // ~array() noexcept {
    //     _clear();
    // }
    ~array() noexcept = default;

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
        // _clear();
        // 重新初始化
        // _init(other.size());

        // 深拷贝
        // TODO
        // 这里必须两个数组的capacity相同，需要做进一步的考虑
        auto p = data, q = other.data;
        for (size_t i = 0; i < capacity; ++i)
            *p++ = *q++;

        return *this;
    }

    // 原生数组不能转移，所以移动构造和拷贝需要删掉!!!

    /**
     * @brief 移动构造函数，处理右值引用的将亡对象，现在这么设计不能转移了
     */
    // array(array&& other) noexcept {
    //     *this = other;
    // }
    array(array&& other) noexcept = delete;

    /**
     * @brief 移动拷贝函数，同上
     * @param other，另一个对象
     * @return array类型的对象引用
     */
    // array& operator=(array&& other) noexcept {
    //     // 移动构造不用下面的两个代码会报错：array l(l2);
    //     // 为了让移动构造不报错，我还是先清空，反正会被将亡对象清除
    //     _clear();
    //     _init(other.size());

    //     // 将对象交换，让将亡对象释放掉我之前的资源，然后我托管对方的资源
    //     std::swap(data, other.data);
    //     std::swap(capacity, other.capacity);

    //     return *this;
    // }
    array& operator=(array&& other) noexcept = delete;

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
    // using callback_t = void(reference);

    /**
     * @brief 链表的遍历方法
     * @param visit，回调函数callback_t
     */
    template <typename callback_t>
    void traverse(callback_t visit) {
        for (size_t i = 0; i < capacity; ++i)
            visit(data[i]);
    }

    /**
     * @brief 得到数组指针
     * @brief 我们要想办法让这个函数识别调用的对象是持久对象还是将亡对象，因为将亡对象调用这个东西会导致内存越界!
     * @brief 在下面加上&表示调用这个函数的是持久对象，学到了!
     */
    // pointer get_pointer() & { return data; }

    /**
     * @brief 对应的右值引用的版本
     * @brief 为了让我们返回的指针在使用之后被自动释放，不需要用户释放，所以使用智能指针
     * @brief 第二个参数是一个用来指明删除是delete[]的类的临时对象
     */
    // auto get_pointer() && {
    //     auto p = data;
    //     data = nullptr;

    //     return std::shared_ptr<value_type>(p, std::default_delete<value_type[]>());
    // }

    /**
     * @brief 这个函数是这个类的友元，可以直接访问这个类的所有成员和函数
     * @param arr，array的类对象，这个参数是必须有的，因为要给外面的函数提供类对象的接口，所以这个类对象是必须有的，这里传入引用
     */
    // 这个Value_t不能和上面的value_t相同，否则会有歧义，会报错
    template <typename Value_t, size_t n>
    friend typename array<Value_t, n>::pointer get_pointer2(array<Value_t, n>& arr);

private:
    /**
     * @brief 初始化函数，改造之后不需要了
     */
    // void _init(int n) {
    //     data = new int[n];
    //     capacity = n;
    // }

    /**
     * @brief 清空函数，改造之后不需要了
     */
    // void _clear() {
    //     delete[] data;

    //     capacity = 0;
    // }

private:
    /**
     * @brief 定义存储数据的数组，用指针代表
     */
    // pointer data;

    /**
     * @brief 定义数组的容量
     */
    // size_t capacity;

    /**
     * @brief 模板参数给出大小之后，不需要用指针代表了，直接使用原生数组
     */
    value_type data[capacity];
};

#endif
