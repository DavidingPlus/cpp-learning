#include "btree.h"

// 类的静态数据成员的存储分配、初始化必须在类外完成
template <typename value_t>
size_t btree<value_t>::count = 0;