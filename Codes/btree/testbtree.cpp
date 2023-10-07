// testbtree.cpp
#include <iostream>

#include "btree.h"

int main() {
    auto br = []() { std::cout << std::endl; };
    auto print_tag = [](btree::value_type& data) { std::cout << data.tag; };

    // 测试构造和析构
    btree tree("AB.C..DE..FG.H..I..");

    // 测试先序遍历
    tree.pre_order(print_tag);
    br();

    // 测试二叉树的高度
    std::cout << tree.height();
    br();

    // 测试静态变量count
    [[maybe_unused]] auto p = btree::get_count;

    std::cout << p();
    br();

    // 测试拷贝或者移动构造函数
    btree t2(tree);
    btree t3(std::move(tree));

    t2.pre_order(print_tag);
    br();

    std::cout << p();
    br();

    return 0;
}
