//main.cpp

#include <iostream>

#include "btree.h"

// 二叉树结点数据域的类型
struct value_type {
    char tag; // 目前只要一个字母标签
};

template <>
size_t btree<value_type>::count = 0;

int main() {
    auto print_tag = [](auto& v) {
        std::cout << v.tag;
    };
    auto br = [] { std::cout << std::endl; };

    btree<value_type> tree{"AB.C..DE..FG.H..I.."};

    tree.preorder(print_tag);
    br();

    std::cout << tree.height();
    br();

    btree t2{std::move(tree)};
    t2.preorder(print_tag);
    br();

    std::cout << btree<value_type>::get_count();
    br();

    // [[maybe_unused]] auto p = btree::get_count;

    // [[maybe_unused]] auto q = tree.preorder;

    return 0;
}