//fun-tpl-abbr.cpp

#include <iostream>

template <typename T>
auto add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add(1, 2) << std::endl;
    std::cout << add(3.3, 4.4) << std::endl;

    return 0;
}