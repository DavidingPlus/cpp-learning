#include "btree.h"

/**
 * @brief 类外初始化类内静态成员，
 * 并且需要放在.cpp文件当中(一个编译单元)，不能放在.h当中，需要在cpp源文件当中进行单独存储!!!否则会出错
 */
// 在模板当中，由于模板不是程序实体，所以这个静态变量的分配是没有意义的，这仍然是一个声明，会报错
template <typename value_t>
size_t btree<value_t>::count = 0;
