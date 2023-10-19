// add.cpp

#include "add.h"

#include <iostream>

extern int add_wrapper(int, int);

int main() {
    std::cout << add(1, 2) << std::endl;
    std::cout << add_wrapper(3, 4) << std::endl;
    std::cout << add(1.1, 2.2) << std::endl;

    // 指针(error)
    // int *p = nullptr, *q = nullptr;
    // std::cout << add(p, q) << std::endl;

    // bool(error)
    // std::cout << add(true, false) << std::endl;

    return 0;
}
