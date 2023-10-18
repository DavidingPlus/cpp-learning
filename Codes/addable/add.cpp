//add.cpp

#include <iostream>

#include "add.h"

extern int add_wrapper(int, int);

int main() {
    std::cout << add(1, 2) << std::endl;
    std::cout << add_wrapper(3, 4) << std::endl; 

    return 0;
}