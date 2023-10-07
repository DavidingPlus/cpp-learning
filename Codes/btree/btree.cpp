#include "btree.h"

/**
 * @brief 类外初始化类内静态成员，
 * 并且需要放在.cpp文件当中(一个编译单元)，不能放在.h当中，防止头文件在重复包含的时候会重复定义这个静态变量
 */
size_t btree::count = 0;
