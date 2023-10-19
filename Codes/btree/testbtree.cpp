// testbtree.cpp
#include <iostream>

#include "btree.h"

// 定义二叉树的数据类型
struct value_t {
    char tag;
};

// 为value_t的静态成员做一个特化，分配存储，必须要这么做!!!
template <>
size_t btree<value_t>::count = 0;

int main() {
    auto br = []() { std::cout << std::endl; };
    auto print_tag = [](btree<value_t>::value_type& data) { std::cout << data.tag; };

    // 测试构造和析构
    btree<value_t> tree("AB.C..DE..FG.H..I..");

    // 测试先序遍历
    tree.pre_order(print_tag);
    br();

    // 测试二叉树的高度
    std::cout << tree.height();
    br();

    // 测试静态变量count
    [[maybe_unused]] auto p = btree<value_t>::get_count;

    std::cout << p();
    br();

    // 测试拷贝或者移动构造函数
    btree<value_t> t2(tree);
    btree<value_t> t3(std::move(tree));

    t2.pre_order(print_tag);
    br();

    std::cout << p();
    br();

    return 0;
}
