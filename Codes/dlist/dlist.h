// dlist.h
#ifndef _DLIST_H_
#define _DLIST_H_

#include <exception>
#include <format>
#include <initializer_list>
#include <iostream>

// 类型隔离，很方便的转化为类模板
// using value_type = int;

template <typename value_t>
class dlist {
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
     * @brief 默认构造函数
     */
    dlist() noexcept {
        _init();
    }

    /**
     * @brief 构造函数，后面放了一个构造函数委托，在这个函数执行之前先执行被委托的函数
     */
    dlist(const std::initializer_list<value_type>& l) noexcept : dlist() {
        for (auto& v : l)
            push_back(v);
    }

    /**
     * @brief 析构函数
     */
    ~dlist() noexcept {
        _clear();
    }

    /**
     * @brief 拷贝构造函数，因为类成员里面含有指针
     * @param other，另一个对象
     */
    dlist(const dlist& other) noexcept {
        *this = other;
    }

    /**
     * @brief 拷贝赋值函数，理由同上
     * @param other，另一个对象
     * @return dlist类型的对象引用
     */
    dlist& operator=(const dlist& other) noexcept {
        // 检测自我赋值
        if (this == &other)
            return *this;

        // 杀死原来的
        _clear();
        // 重新初始化
        _init();

        // 深拷贝
        for (auto p = other.head->next; p != other.tail; p = p->next)
            push_back(p->data);

        return *this;
    }

    /**
     * @brief 移动构造函数，处理右值引用的将亡对象
     */
    dlist(dlist&& other) noexcept {
        *this = other;
    }

    /**
     * @brief 移动拷贝函数，同上
     * @param other，另一个对象
     * @return dlist类型的对象引用
     */
    dlist& operator=(dlist&& other) noexcept {
        // 移动构造不用下面的两个代码会报错：dlist l(l2);
        // 为了让移动构造不报错，我还是先清空，反正会被将亡对象清除
        _clear();
        _init();

        // 将对象交换，让将亡对象释放掉我之前的资源，然后我托管对方的资源
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(length, other.length);

        return *this;
    }

private:
    /**
     * @brief 定义结点类型
     */
    struct node {
        value_type data;
        struct node* next = nullptr;
        struct node* prior = nullptr;

        // TODO
        // 这里理解，如何去掉从push_back里面经过node的拷贝构造，省掉这一次不必要的赋值
        node() = default;

        // 在位构造
        template <typename... types>
        node(types&&... args) : data(args...) {}
    };

    /**
     * @brief 定义结点类型别名
     */
    using nodeptr_t = node*;

    /**
     * @brief 定义头结点，尾结点和链表长度
     */
    nodeptr_t head = nullptr, tail = nullptr;
    size_t length = 0;

    /**
     * @brief 初始化链表
     */
    void _init() {
        head = new node;
        tail = new node;
        head->next = tail;
        tail->prior = head;
    }

    /**
     * @brief 在某个结点前面插入一个节点
     * @param post，在这个结点的前面插入结点
     * @param p，需要新插入的结点
     */
    void _linkbefore(nodeptr_t post, nodeptr_t p) {
        p->next = post;
        p->prior = post->prior;
        post->prior->next = p;
        post->prior = p;

        ++length;
    }

    /**
     * @brief 清空链表，释放结点
     */
    void _clear() {
        auto p = head, q = p;
        while (p) {
            q = p;
            p = p->next;
            delete q;
        }
    }

public:
    /**
     * @brief 在链表头部插入节点
     */
    void push_front(constref v) {
        auto p = new node{v};
        _linkbefore(head->next, p);
    }

    /**
     * @brief 在链表尾部插入结点
     * @param v，需要插入的结点的data值
     */
    void push_back(constref v) {
        auto p = new node{v};
        _linkbefore(tail, p);
    }

    /**
     * @brief 在位插入
     * @tparam types
     * @param  args
     */
    template <typename... types>
    void emplace_back(types&&... args) {
        auto p = new node{args...};
        _linkbefore(tail, p);
    }

    /**
     * @brief 在指定位置插入一个结点，注意这里使用了异常捕获
     * @param pos，需要插入的位置，从第一个结点(head的后驱结点)为0开始计数
     * @param v，需要插入的结点的data值
     */
    void insert(size_t pos, constref v) try {
        auto p = head->next;
        // 这里有两种情况退出，一种是pos值没超停在正确的位置；一种是pos值超了，pos给的值不对
        for (size_t i = 0; i < pos && p != nullptr; ++i)
            p = p->next;

        // 处理异常
        if (!p)
            throw(std::out_of_range(std::format("insert postion {} was out of range", pos)));
        // 没有异常则正常插入
        auto q = new node{v};
        _linkbefore(p, q);
        ++length;
    } catch (std::out_of_range& e) {  // 捕获异常
        std::cout << e.what() << std::endl;
        exit(-1);
    }

    /**
     * @brief insert的优化版，去掉不必要的复制，叫emplace
     */
    template <typename... types>
    void emplace(size_t pos, types... args) try {
        auto p = head->next;
        // 这里有两种情况退出，一种是pos值没超停在正确的位置；一种是pos值超了，pos给的值不对
        for (size_t i = 0; i < pos && p != nullptr; ++i)
            p = p->next;

        // 处理异常
        if (!p)
            throw(std::out_of_range(std::format("emplace postion {} was out of range", pos)));
        // 没有异常则正常插入
        auto q = new node{args...};  // 改成在位构造
        _linkbefore(p, q);
        ++length;
    } catch (std::out_of_range& e) {  // 捕获异常
        std::cout << e.what() << std::endl;
        exit(-1);
    }

    /**
     * @brief 定义了回调函数的类型，返回值是void，参数是引用类型，可以打印也可以修改内容
     */
    // using callback_t = void(reference);

    /**
     * @brief 链表的遍历方法
     * @param visit，之前是回调函数callback_t，现在改造为模板
     */
    template <typename callback_t>
    void traverse(callback_t visit) {
        for (auto p = head->next; p != tail; p = p->next)
            visit(p->data);
    }

public:
    /**
     * @brief 定义容器类型，作类型屏蔽
     */
    using container_type = dlist;

    /**
     * @brief 定义指向数据的指针，作类型屏蔽
     */
    using dataptr_type = nodeptr_t;

    /**
     * @brief 定义相差的步数的类型，就是指针之间的距离
     */
    using difference_type = ptrdiff_t;

public:  // 迭代器----------------------------------------
    /**
     * @brief 作一个超前声明，说明是友元
     */
    friend class iterator;

    /**
     * @brief 定义迭代器类
     */
    class iterator {
    public:
        /**
         * @brief 定义一些类型
         */
        using value_type = container_type::value_type;
        using pointer = container_type::pointer;
        using reference = container_type::reference;
        using difference_type = container_type::difference_type;

    private:
        using dataptr_type = container_type::dataptr_type;

        /**
         * @brief 定义迭代器的成员，是一根指针，指向类的数据成员
         */
        dataptr_type p;

    public:
        /**
         * @brief 构造函数
         */
        iterator(dataptr_type _p = nullptr) : p(_p) {}

        /**
         * @brief 重载!=运算符
         * @param  other，另一个迭代器
         * @return true
         * @return false
         */
        // constexpr，如果编译器评估是常量表达式，则在编译期得出结果，可以提高效率
        constexpr bool operator!=(const iterator& other) const {
            return this->p != other.p;
        }

        /**
         * @brief 重载前缀++运算符
         * @return iterator&
         */
        iterator& operator++() {
            // p = p->next;
            // return *this;
            return advance();
        }

        /**
         * @brief 重载前缀--运算符
         * @return iterator&
         */
        iterator& operator--() {
            return advance(-1);
        }

        /**
         * @brief 重载后缀++运算符
         * @return iterator
         */
        iterator operator++(int) {
            auto t = p;  // 如果用拷贝构造的话，我们没写，可能造成浅拷贝
            // p = p->next;
            advance();
            return iterator(t);
        }

        /**
         * @brief 重载后缀--运算符
         * @return iterator
         */
        iterator operator--(int) {
            auto t = p;
            advance(-1);
            return iterator(t);
        }

        /**
         * @brief 重载*号运算符
         * @return reference
         */
        reference operator*() {
            return p->data;
        }

        /**
         * @brief 让当前的迭代器向前或者向后移动n位
         * @param  n，默认值为1
         */
        iterator& advance(difference_type n = 1) {
            // TODO
            // 我们暂时不管指针越界，这个后面自己完成
            if (n >= 0) {
                for (auto i = 0; i < n; ++i)
                    p = p->next;
            } else {
                for (auto i = 0; i < -n; ++i)
                    p = p->prior;
            }

            return *this;
        }

        /**
         * @brief 重载 + 运算符
         * @param  n
         * @return iterator
         */
        iterator operator+(difference_type n) {
            return iterator(p).advance(n);  // 为了保持左右操作数不变，给一个临时对象
        }

        /**
         * @brief 重载 - 运算符
         * @param  n
         * @return iterator
         */
        iterator operator-(difference_type n) {
            return iterator(p).advance(-n);
        }
    };

public:
    /**
     * @brief 容器的begin()方法
     * @return iterator
     */
    constexpr iterator begin() const {
        return iterator(head->next);
    }

    /**
     * @brief 容器的end()方法
     * @return iterator
     */
    constexpr iterator end() const {
        return iterator(tail);
    }

public:  // 逆向迭代器----------------------------------------
    /**
     * @brief 作一个超前声明，说明是友元
     */
    friend class reverse_iterator;

    /**
     * @brief 定义逆向迭代器类
     */
    class reverse_iterator {
    public:
        /**
         * @brief 定义一些类型
         */
        using value_type = container_type::value_type;
        using pointer = container_type::pointer;
        using reference = container_type::reference;
        using difference_type = container_type::difference_type;

    private:
        using dataptr_type = container_type::dataptr_type;

        /**
         * @brief 定义迭代器的成员，是一根指针，指向类的数据成员
         */
        dataptr_type p;

    public:
        /**
         * @brief 构造函数
         */
        reverse_iterator(dataptr_type _p = nullptr) : p(_p) {}

        /**
         * @brief 重载!=运算符
         * @param  other，另一个迭代器
         * @return true
         * @return false
         */
        // constexpr，如果编译器评估是常量表达式，则在编译期得出结果，可以提高效率
        constexpr bool operator!=(const reverse_iterator& other) const {
            return this->p != other.p;
        }

        /**
         * @brief 重载前缀++运算符
         * @return reverse_iterator&
         */
        reverse_iterator& operator++() {
            // p = p->next;
            // return *this;
            return advance();
        }

        /**
         * @brief 重载前缀--运算符
         * @return reverse_iterator&
         */
        reverse_iterator& operator--() {
            return advance(-1);
        }

        /**
         * @brief 重载后缀++运算符
         * @return reverse_iterator
         */
        reverse_iterator operator++(int) {
            auto t = p;  // 如果用拷贝构造的话，我们没写，可能造成浅拷贝
            // p = p->next;
            advance();
            return reverse_iterator(t);
        }

        /**
         * @brief 重载后缀--运算符
         * @return reverse_iterator
         */
        reverse_iterator operator--(int) {
            auto t = p;
            advance(-1);
            return reverse_iterator(t);
        }

        /**
         * @brief 重载*号运算符
         * @return reference
         */
        reference operator*() {
            return p->data;
        }

        /**
         * @brief 让当前的迭代器向前或者向后移动n位
         * @param  n，默认值为1
         */
        reverse_iterator& advance(difference_type n = 1) {
            // TODO
            // 我们暂时不管指针越界，这个后面自己完成
            if (n >= 0) {
                for (auto i = 0; i < n; ++i)
                    p = p->prior;
            } else {
                for (auto i = 0; i < -n; ++i)
                    p = p->next;
            }

            return *this;
        }

        /**
         * @brief 重载 + 运算符
         * @param  n
         * @return reverse_iterator
         */
        reverse_iterator operator+(difference_type n) {
            return reverse_iterator(p).advance(n);  // 为了保持左右操作数不变，给一个临时对象
        }

        /**
         * @brief 重载 - 运算符
         * @param  n
         * @return reverse_iterator
         */
        reverse_iterator operator-(difference_type n) {
            return reverse_iterator(p).advance(-n);
        }
    };

public:
    /**
     * @brief 容器的rbegin()方法
     * @return reverse_iterator
     */
    constexpr reverse_iterator rbegin() const {
        return reverse_iterator(tail->prior);
    }

    /**
     * @brief 容器的rend()方法
     * @return reverse_iterator
     */
    constexpr reverse_iterator rend() const {
        return reverse_iterator(head);
    }
};

#endif
