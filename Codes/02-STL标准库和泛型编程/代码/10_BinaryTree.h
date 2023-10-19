#ifndef __BINARTTREE__
#define __BINARTTREE__
#include "10_TreeNode.h"

enum Order
{
    pre,
    in,
    post
};

// 写一个全局函数来删除二叉树
template <typename Type>
inline void deleteNodes(TreeNode<Type> *node)
{
    if (node->left)
        deleteNodes(node->left);
    if (node->right)
        deleteNodes(node->right);
    delete node;
}

// 定义整颗二叉树类
template <class Type>
class BinaryTree
{
    typedef Type __ValueType;
    typedef TreeNode<__ValueType> __NodeType;
    typedef __NodeType &__reference;
    typedef __NodeType *__pointer;

public:
    // BinaryTree();
    explicit BinaryTree(__ValueType val = NULL); // 不给默认值就是NULL
    ~BinaryTree() { deleteTree(); }
    void deleteTree();
    void printTree(Order ord);
    __reference getroot() const { return *root; }

private:
    __pointer root;
};

// 构造函数
template <class Type>
inline BinaryTree<Type>::BinaryTree(__ValueType val)
{
    root = new TreeNode<Type>;
    root->val = val;
    root->left = nullptr;
    root->right = nullptr;
}

// 整棵树的析构函数
template <class Type>
inline void BinaryTree<Type>::deleteTree()
{
    deleteNodes(root);
}

// 前序遍历
template <class Type>
inline void BinaryTree<Type>::printTree(Order ord)
{
    switch (ord)
    {
    case pre:
        root->PreOrder();
        break;
    case in:
        root->InOrder();
        break;
    case post:
        root->PostOrder();
        break;
    }
}

#endif
