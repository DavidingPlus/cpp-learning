//btree.h

#pragma once

#include <iostream>


// 二叉树类
template <typename value_t>
class btree {
public:
    using value_type = value_t;
    using pointer = value_type*;
    using reference = value_type&;
    using constref = value_type const&;

    using callback_t = void (value_type &);

private:
    // 二叉树结点类型定义
    struct node {
        value_type data;
        node *left = nullptr, 
            *right = nullptr;
    };

    using nodeptr_t = node*;

    nodeptr_t root = nullptr; // 根结点指针

    static size_t count;

    /*
        @brief  根据先序定位串重构二叉树
        @param  str：先序定位串
        @return 二叉树根结点指针
    */
    nodeptr_t _create_by_str(const char* &str) {
        //定位串处理完了
        if (*str == '\0') return nullptr;

        //遇到了定位串中的'.'，这表明这颗子树是空树
        if (*str == '.') {
            ++str;
            return nullptr;
        }

        //生成新节点，填充数据
        auto t = new node{*str}; //生成一个新结点
        // t->data.tag = *str;

        //每消费了一个字符，指针pstr后移一位
        ++str;
        //递归生成子树
        t->left = _create_by_str(str); //生成左子树
        t->right = _create_by_str(str); //生成右子树

        return t;
    }

    /*
        @brief  根据二叉树root复制一棵新的二叉树。是一种先序遍历
        @param  root：源二叉树根结点指针
        @return 新二叉树根结点指针
    */
    [[nodiscard]] nodeptr_t _copy(nodeptr_t root) {
        if (root == nullptr) 
            return nullptr;

        auto t = new node{root->data.tag};
        t->left = _copy(root->left);
        t->right = _copy(root->right);
        return t;
    }

    // 后续遍历销毁二叉树
    void _destroy(nodeptr_t root) {
        if (root == nullptr) return;

        _destroy(root->left);
        _destroy(root->right);
        delete root;
    }

    /*
        @brief  先序遍历二叉树。
        @param  root：根结点指针
        @param  visit：访问结点的回调函数
        @return void
    */
    void _preorder(nodeptr_t root, callback_t visit) {
        if (root == nullptr) return;

        visit(root->data);
        _preorder(root->left, visit);
        _preorder(root->right, visit);
    }

    // 求二叉树的高度
    size_t _height(nodeptr_t root) {
        if (root == nullptr) return 0;

        auto hl = _height(root->left);
        auto hr = _height(root->right);
        return (hl > hr ? hl : hr) + 1;
    }

public:
    // 禁止默认构造函数
    btree() = delete;

    btree(const char *str) {
        auto p = str;
        root = _create_by_str(p);
        ++count;
    }

    // 复制控制1：复制构造函数
    btree(btree const& tree) {
        root = _copy(tree.root);
        ++count;
    }

    // 复制控制2：转移复制构造函数
    btree(btree && tree) {
        std::swap(root, tree.root);
        ++count;
    }

    ~btree() {
        _destroy(root);
    }

    // 复制控制3：禁止赋值和转移赋值
    btree& operator=(btree const&) = delete;
    btree& operator=(btree &&) = delete;

    // 先序遍历的包装函数
    void preorder(callback_t visit) {
        _preorder(root, visit);
    }

    // 求树高度的包装函数
    auto height() {
        return _height(root);
    }

    // 类的静态成员函数没有this指针
    static auto get_count() {
        return count;
    }
};