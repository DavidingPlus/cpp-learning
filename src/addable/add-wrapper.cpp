// add-wrapper.cpp

#include "add.h"

// 外部模板
extern template auto add<int>(int, int);

int add_wrapper(int a, int b) {
    return add(a, b);
}
