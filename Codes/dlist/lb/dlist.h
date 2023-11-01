/**
 * @file dlist.h
 * @author 白忠建 (baizj@uestc.edu.cn)
 * @brief 双向链表类模板
 * @version 0.1
 * @date 2023-11-01
 * 
 * @copyright Copyright (C) 2023 白忠建. All rights reserved.
 * 
 */

#pragma once

#include <iostream>
#include <initializer_list>
#include <format>
#include <exception>

#include "../iterator/iterator.h"

/**
 * @brief 双向链表类模板
 * 
 * @tparam value_t 链表元素类型
 */
template <typename value_t>
class dlist {
public:
    /**
     * @brief 定义内部类型，以便与外部类型隔离。
     * 
     */
    using value_type = value_t; 
    using pointer = value_type*;
    using reference = value_type&;
    using constref = value_type const &; // 值的常量左值引用类型

private:
    /**
     * @brief 链表的结点类型
     * 
     */
    struct node {
        value_type data;    // 数据域
        node *next = nullptr;  // 后向指针域
        node *prior = nullptr; // 前向指针域

        // 默认构造函数
        node() = default;

        /**
         * @brief 带变长参数的构造函数。这样可将构造参数包直接传递给内部对象data的构造函数，从而避免复制。
         * 
         * @tparam types 变长类型参数包
         * @param args 变长参数包
         */
        template <typename ...types>
        node(types&& ...args) : data(args...) {}
    };

    // 定义指向结点的指针类型。
    using nodeptr_t = node*;

    nodeptr_t head = nullptr, tail = nullptr; //指向头尾结点的指针
    size_t length = 0; //链表长度

    /**
     * @brief 初始化。1.生成头尾结点，分别用head和tail指针指向；2.将头尾结点链在一起。
     * 
     */
    void _init() {
        head = new node;
        tail = new node;
        head->next = tail;
        tail->prior = head;
    }

    /**
     * @brief 清空链表。将链表中包括头尾结点在内的所有结点删除。
     * 
     */
    void _clear() {
        auto p = head, q = p;
        while (p != nullptr) {
            q = p;
            p = p->next;
            delete q;
        }
        length = 0;
    }

    /**
     * @brief 在结点前插入新结点
     * 
     * @param post 结点指针。新节点插入到此结点之前
     * @param p 新结点指针
     */
    void _linkbefore(nodeptr_t post, nodeptr_t p) {
        p->next = post;
        p->prior = post->prior;
        post->prior->next = p;
        post->prior = p;

        ++length;
    }

protected:

public:
    // 默认构造函数
    dlist() noexcept {
        _init();
    }

    // 花括号初始化列表构造函数。使用了构造函数委托。
    dlist(std::initializer_list<value_type> const& l) noexcept : dlist() {
        for (auto& v : l) push_back(v);
    }

    // 复制构造函数
    dlist(dlist const& l) : dlist() {
        for (auto p = l.head->next; p != l.tail; p = p->next)
            push_back(p->data);
    }

    // 转移复制构造函数
    dlist(dlist&& l) : dlist() {
        std::swap(head, l.head);
        std::swap(tail, l.tail);
        std::swap(length, l.length);
    }

    // 析构函数
    ~dlist() noexcept {
        _clear();
    }

    // 重载的赋值运算符函数
    dlist& operator=(dlist const& l) {
        _clear();
        _init();

        for (auto p = l.head->next; p != l.tail; p = p->next)
            push_back(p->data);

        return *this;
    }

    // 重载的转移赋值运算符函数
    dlist& operator=(dlist&& l) {
        std::swap(head, l.head);
        std::swap(tail, l.tail);
        std::swap(length, l.length);

        return *this;
    }

    // 禁止复制
    // dlist(dlist const&) = delete;

    /**
     * @brief 在链表的尾部（即在尾结点之前）插入新节点
     * 
     * @param v 待插入的值（的常量引用）
     */
    void push_back(constref v) {
        auto p = new node{v}; // 生成结点并初始化
        _linkbefore(tail, p);
    }

    /**
     * @brief 在位尾插方法。模板中的成员模板
     * 
     * @tparam types 变长类型参数包
     * @param args 变长参数包，直接传递给node的构造函数，而此构造函数又直接将参数转发给内部对象的构造函数
     */
    template <typename ...types>
    void emplace_back(types&& ...args) {
        auto p = new node{args...}; // 生成结点并初始化
        _linkbefore(tail, p);
    }

    /**
     * @brief 在指定位置插入新结点。如插入位置有误，抛出异常
     * 
     * @param pos 插入位置。从0开始计数
     * @param v 待插入的值（的常量引用）
     */
    void insert(size_t pos, constref v) try {
        auto p = head->next;
        for (auto i = 0uz; i < pos and p != nullptr; ++i, p = p->next);
        if (p == nullptr) 
            throw std::out_of_range(std::format("inserting postion {} was out of range", pos));

        auto q = new node{v};
        _linkbefore(p, q);
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
        exit(1);
    }

    /**
     * @brief 在位插入法。模板中的成员模板
     * 
     * @tparam types 变长类型参数包
     * @param pos 插入位置。从0开始计数
     * @param args 变长参数包，直接传递给node的构造函数，而此构造函数又直接将参数转发给内部对象的构造函数
     */
    template <typename ...types>
    void emplace(size_t pos, types ...args) try {
        auto p = head->next;
        for (auto i = 0uz; i < pos and p != nullptr; ++i, p = p->next);
        if (p == nullptr) 
            throw std::out_of_range(std::format("inserting postion {} was out of range", pos));

        auto q = new node{args...};
        _linkbefore(p, q);
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
        exit(1);
    }

    /**
     * @brief 遍历链表，访问结点数据。模板中的成员模板
     * 
     * @tparam callback_t 回调函数类型。该类型的函数带有一个value_type|reference|constref类型的参数
     * @param visit 回调函数
     */
    template <typename callback_t>
    void traverse(callback_t visit) {
        for (auto p = head->next; p != tail; p = p->next)
            visit(p->data);
    }

    constexpr size_t size() const {
        return length;
    }

    constexpr bool empty() const {
        return length == 0;
    }
    
    // 为迭代器定义类型
    using container_type = dlist; // 容器类型
    using dataptr_type = nodeptr_t; // 数据指针类型
    using difference_type = ptrdiff_t; // 指针距离类型

    friend class iterator; // 为了效率，迭代器是容器类的友元
    /**
     * @brief 定义前向迭代器。迭代器是容器的内部类（模板）
     * 
     */
    class iterator : public random_access_iterator_tag {
    public:
        // 从容器引入必要的类型
        // 原则上，迭代器至少要包含以下四种类型
        using value_type = container_type::value_type;
        using pointer = container_type::pointer;
        using reference = container_type::reference;
        using difference_type = container_type::difference_type;

        using iterator_category = random_access_iterator_tag;

    private:
        using dataptr_type = container_type::dataptr_type;

        dataptr_type p; // 被包装的指针，指向容器的内部存储结构

        // 内部函数，用于指针的前移或后移
        void _next(dataptr_type& p) { p = p->next; }
        void _prev(dataptr_type& p) { p = p->prior; }
        
        // 判断指针是否移到链表外
        constexpr bool _is_exceed(dataptr_type p) const { return p == nullptr; }
        constexpr bool _is_next_exceed(dataptr_type p) const { return p->next == nullptr; }
        constexpr bool _is_prev_exceed(dataptr_type p) const { return p->prior == nullptr; }

    public:
        iterator(dataptr_type _p = nullptr) : p(_p) {}

        /**
         * @brief 向前移动内部指针方法
         * 
         * @param n 移动距离。如果是负数，则向后移动
         * @return constexpr iterator& 迭代器本身
         */
        constexpr iterator& advance(difference_type n = 1) try {
            if (n >= 0) {
                for (auto i = 0; i < n and not _is_exceed(p); ++i) _next(p);
            } else {
                for (auto i = 0; i < -n and not _is_exceed(p); ++i) _prev(p);
            }
            if (p == nullptr)
                throw std::out_of_range(std::format("advance distance {} causes out of range", n));
        
            return *this;
        } catch (std::out_of_range& e) {
            std::cout << e.what() << std::endl;
            exit(1);
        }

        /**
         * @brief 计算this迭代器和指定迭代器之间的距离
         * 
         * @param itr 指定的迭代器
         * @return constexpr difference_type 两个迭代器之间的距离。可能为负值
         */
        constexpr difference_type distance(iterator const &itr) const try {
            iterator tmp{p}; // 生成一个临时迭代器。因为distance方式是const方法，所以应该这么做。
            difference_type n = 0;

            // 先向后找，看看是否能遇到itr.p
            for (; tmp.p != itr.p and not tmp._is_next_exceed(tmp.p); tmp._next(tmp.p), ++n);
            if (tmp.p == itr.p) return n;

            // 再向后找
            for (n = 0, tmp.p = p; tmp.p != itr.p and not tmp._is_prev_exceed(tmp.p); tmp._prev(tmp.p), --n);
            if (tmp.p == itr.p) return n;

            // 未找到，抛出异常
            throw std::out_of_range("distance: cannot evaluate the distance");
        } catch (std::out_of_range &e) {
            std::cout << e.what() << std::endl;
            exit(1);
        }

        // 生成一个指向当前项后项的迭代器
        constexpr iterator next() const {
            auto itr{*this};
            _next(itr.p);
            return itr;
        }

        // 生成一个指向当前项前项的迭代器
        constexpr iterator prev() const {
            auto itr{*this};
            _prev(itr.p);
            return itr;
        }
    
        // 重载的!=运算符
        constexpr bool operator!=(iterator const& itr) const {
            return p != itr.p;
        }

        // 重载的++运算符：前缀
        constexpr iterator& operator++() {
            return advance();
        }

        // 重载的++运算符：后缀
        constexpr iterator operator++(int) {
            auto t = p;
            advance();
            return iterator(t);
        }

        // 重载的--运算符：前缀
        constexpr iterator& operator--() {
            return advance(-1);
        }

        // 重载的--运算符：后缀
        constexpr iterator operator--(int) {
            auto t = p;
            advance(-1);
            return iterator(t);
        }

        // 重载的*运算符。注意：返回数据的左值引用
        constexpr reference operator*() const {
            return p->data;
        }

        // 重载的+运算符，是迭代器具备随机访问能力
        constexpr iterator operator+(difference_type n) const {
            return iterator(p).advance(n);
        }

        // 重载的-运算符，是迭代器具备随机访问能力
        constexpr iterator operator-(difference_type n) const {
            return iterator(p).advance(-n);
        }
    };

    // 返回首迭代器
    constexpr iterator begin() const {
        return iterator(head->next);
    }

    // 返回哨兵迭代器
    constexpr iterator end() const {
        return iterator(tail);
    }

    /**
     * @brief 逆向迭代器
     * 
     */
    friend class reverse_iterator;
    class reverse_iterator : public random_access_iterator_tag {
    public:
        using value_type = container_type::value_type;
        using pointer = container_type::pointer;
        using reference = container_type::reference;
        using difference_type = container_type::difference_type;

        using iterator_category = random_access_iterator_tag;

    private:
        using dataptr_type = container_type::dataptr_type;

        dataptr_type p;

        // 内部函数，用于指针的前移或后移
        void _next(dataptr_type& p) { p = p->prior; }
        void _prev(dataptr_type& p) { p = p->next; }

        constexpr bool _is_exceed(dataptr_type p) const { return p == nullptr; }
        constexpr bool _is_next_exceed(dataptr_type p) const { return p->prior == nullptr; }
        constexpr bool _is_prev_exceed(dataptr_type p) const { return p->next == nullptr; }

    public:
        reverse_iterator(dataptr_type _p = nullptr) : p(_p) {}

        constexpr reverse_iterator& advance(difference_type n = 1) try {
            if (n >= 0) {
                for (auto i = 0; i < n and not _is_exceed(p); ++i) _next(p);
            } else {
                for (auto i = 0; i < -n and not _is_exceed(p); ++i) _prev(p);
            }
            if (_is_exceed(p))
                throw std::out_of_range(std::format("advance distance {} causes out of range", n));
        
            return *this;
        } catch (std::out_of_range& e) {
            std::cout << e.what() << std::endl;
            exit(1);
        }

        // 计算两个迭代器之间的距离
        constexpr difference_type distance(reverse_iterator const &itr) const try {
            reverse_iterator tmp{p};
            difference_type n = 0;

            // 先向后找，看看是否能遇到itr.p
            for (; tmp.p != itr.p and not tmp._is_next_exceed(tmp.p); tmp._next(tmp.p), ++n);
            if (tmp.p == itr.p) return n;

            // 再向后找
            for (n = 0, tmp.p = p; tmp.p != itr.p and not tmp._is_prev_exceed(tmp.p); tmp._prev(tmp.p), --n);
            if (tmp.p == itr.p) return n;

            // 未找到，抛出异常
            throw std::out_of_range("distance: cannot evaluate the distance");
        } catch (std::out_of_range &e) {
            std::cout << e.what() << std::endl;
            exit(1);
        }

        // 生成一个指向当前项后项的迭代器
        constexpr reverse_iterator next() const {
            auto itr{*this};
            _next(itr.p);
            return itr;
        }

        // 生成一个指向当前项前项的迭代器
        constexpr reverse_iterator prev() const {
            auto itr{*this};
            _prev(itr.p);
            return itr;
        }
    
        constexpr bool operator!=(reverse_iterator const& itr) const {
            return p != itr.p;
        }

        constexpr reverse_iterator& operator++() {
            return advance();
        }

        constexpr reverse_iterator operator++(int) {
            auto t = p;
            advance();
            return reverse_iterator(t);
        }

        constexpr reverse_iterator& operator--() {
            return advance(-1);
        }

        constexpr reverse_iterator operator--(int) {
            auto t = p;
            advance(-1);
            return reverse_iterator(t);
        }

        constexpr reference operator*() const {
            return p->data;
        }

        constexpr reverse_iterator operator+(difference_type n) const {
            return reverse_iterator(p).advance(n);
        }

        constexpr reverse_iterator operator-(difference_type n) const {
            return reverse_iterator(p).advance(-n);
        }
    };

    constexpr reverse_iterator rbegin() const {
        return reverse_iterator(tail->prior);
    }

    constexpr reverse_iterator rend() const {
        return reverse_iterator(head);
    }
};