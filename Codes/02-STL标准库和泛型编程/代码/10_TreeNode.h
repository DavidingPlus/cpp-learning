#ifndef __TREENODE__
#define __TREENODE__

enum Left_Right
{
    Left,
    Right
};

// 定义结点类
#include <iostream>
template <class Type>
struct TreeNode
{
    typedef Type __ValueType;
    typedef TreeNode<__ValueType> __NodeType;
    typedef __NodeType *__pointer;

    __ValueType val;
    __pointer left;
    __pointer right;

    void __init__();
    void insert(__ValueType val, bool is_left = Left); // 1为左 0为右 默认为做左

    void PreOrder();
    void InOrder();
    void PostOrder();
    void visit();
};

// 虽然不给节点写构造函数但是写一个初始化没问题的
template <class Type>
inline void TreeNode<Type>::__init__()
{
    this->left = nullptr;
    this->right = nullptr;
}

// 插入子树
template <class Type>
inline void TreeNode<Type>::insert(__ValueType val, bool is_left)
{
    if (is_left == Left)
    {
        if (this->left)
        {
            cout << "leftnode has already be used." << endl;
            return;
        }
        __pointer newNode = new TreeNode<__ValueType>;
        newNode->__init__();
        newNode->val = val;
        this->left = newNode;
    }
    else
    {
        if (this->right)
        {
            cout << "rightnode has already be used." << endl;
            return;
        }
        __pointer newNode = new TreeNode<__ValueType>;
        newNode->__init__();
        newNode->val = val;
        this->right = newNode;
    }
}

// visit
template <class Type>
inline void TreeNode<Type>::visit()
{
    cout << this->val << endl;
}

// 遍历
template <class Type>
inline void TreeNode<Type>::PreOrder()
{
    if (!this)
        return;
    visit();
    left->PreOrder();
    right->PreOrder();
}

template <class Type>
inline void TreeNode<Type>::InOrder()
{
    if (!this)
        return;
    left->InOrder();
    visit();
    right->InOrder();
}

template <class Type>
inline void TreeNode<Type>::PostOrder()
{
    if (!this)
        return;
    left->PostOrder();
    right->PostOrder();
    visit();
}

#endif
