//abs.cpp

#include <iostream>

template <typename T, T zero = T(0)>
auto abs(T v) {
    return v < zero ? -v : v;
}

template <typename T>
auto abs<T*>(T* v) {
    return v;
}

// struct X {};

int main() {
    int a, *p = &a;
    abs(p);
    // std::cout << abs<int, 0uz>(-2) << std::endl;

    return 0;
}