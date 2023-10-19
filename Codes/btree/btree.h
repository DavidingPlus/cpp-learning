// btree.h
#ifndef _BTREE_H_
#define _BTREE_H_

#include <iostream>

/**
 * @brief 定义数据类型
 */
// struct value_type {
//     char tag;
// };

/**
 * @brief 二叉树的类
 */
template <typename value_t>
class btree {
public:
    /**
     * @brief 定义一些类型
     */
    using value_type = value_t;
    using pointer = value_type *;
    using reference = value_type &;
    using constref = const value_type &;

    /**
     * @brief 定义回调函数类型
     */
    using callback_t = void(value_type &);

public:
    /**
     * @brief 默认构造函数，但是我需要强制禁止，意思是必须带有二叉树先序字符串
     */
    btree() = delete;

    /**
     * @brief 构造函数
     * @param  str，二叉树先序字符串
     */
    btree(const char *str) {
        auto p = str;  // 在创建的函数中，传入的是指针的引用，p会被修改，所以不能直接传入str
        root = _create_by_str(p);
        ++count;
    }

    /**
     * @brief 拷贝构造函数
     * @param  other
     */
    btree(const btree &other) {
        root = _copy(other.root);
        ++count;
    }

    /**
     * @brief 移动构造函数
     * @param  other
     */
    btree(btree &&other) {
        std::swap(root, other.root);
    }

    /**
     * @brief 拷贝赋值函数，但是被我禁止了
     * @return btree&
     */
    btree &operator=(const btree &) = delete;

    /**
     * @brief 移动赋值函数，但是也被我禁止了
     * @return btree&
     */
    btree &operator=(btree &&) = delete;

    /**
     * @brief 析构函数
     */
    ~btree() {
        _destroy(root);
        --count;
    }

public:
    /**
     * @brief 先序遍历这棵树
     * @param  visit，回调函数
     */
    void pre_order(callback_t visit) {
        _preorder(root, visit);
    }

    /**
     * @brief 求这个二叉树的高度
     * @return int
     */
    size_t height() {
        return _height(root);
    }

    /**
     * @brief 得到静态数据成员，静态函数只能访问静态成员
     * @brief 静态成员函数不能访问类内的成员，因为没有this指针，他是被所有实例化对象共享的，所以只能访问静态成员
     * @return size_t
     */
    static size_t get_count() {
        return count;
    }

private:
    /**
     * @brief 定义结点类型
     */
    struct node {
        value_type data;
        struct node *left = nullptr;
        struct node *right = nullptr;
    };

    /**
     * @brief 定义结点指针类型别名
     */
    using nodeptr_t = node *;

    /**
     * @brief 定义根节点
     */
    nodeptr_t root = nullptr;

    /**
     * @brief 统计实例化了多少个对象
     */
    static size_t count;

private:
    /**
     * @brief 递归生成一个子树
     * @param  str，具有一定规则的二叉树字符串，传入的是指针引用，const是代表指针指向的值不能修改，但是这个指针可以移动
     * @return nodeptr_t
     */
    nodeptr_t _create_by_str(const char *&str) {
        // 定位串处理完了
        if ('\0' == *str)
            return nullptr;

        // 遇到了定位串中的'.'，这表明这颗子树是空树
        if ('.' == *str) {
            ++str;
            return nullptr;
        }

        // 生成新节点，填充数据
        auto t = new node{*str};  // 生成一个新结点
        // t->data.tag = *str;

        // 每消费了一个字符，指针pstr后移一位
        ++str;
        // 递归生成子树
        t->left = _create_by_str(str);   // 生成左子树
        t->right = _create_by_str(str);  // 生成右子树

        return t;
    }

    /**
     * @brief 从根节点开始复制一棵树
     * @param  root，根节点指针
     */
    nodeptr_t _copy(nodeptr_t root) {
        if (nullptr == root)
            return nullptr;

        auto t = new node{root->data.tag};

        t->left = _copy(root->left);
        t->right = _copy(root->right);

        return t;
    }

    /**
     * @brief 从根节点开始销毁这颗树
     * @param  root，根节点指针
     */
    void _destroy(nodeptr_t root) {
        if (nullptr == root)
            return;

        _destroy(root->left);
        _destroy(root->right);
        delete root;
    }

    /**
     * @brief 实际做事情的先序遍历
     * @param  root，一个树的根节点
     * @param  visit，回调函数，访问时候对节点做的事情
     */
    void _preorder(nodeptr_t root, callback_t visit) {
        if (nullptr == root)
            return;

        visit(root->data);
        _preorder(root->left, visit);
        _preorder(root->right, visit);
    }

    /**
     * @brief 实际做事情的求二叉树的高度
     * @param  root，一个树的根节点
     */
    size_t _height(nodeptr_t root) {
        if (nullptr == root)
            return 0;

        // 这里由于类的原因不好定义遍历参数depth，我就用第二种方法了
        return 1 + std::max(_height(root->left), _height(root->right));
    }
};

#endif
