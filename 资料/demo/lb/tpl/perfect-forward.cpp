//perfect-forward.cpp

#include <iostream>

void f(int&) { std::cout << "f(int&)" << std::endl; }
void f(int&&) { std::cout << "f(int&&)" << std::endl; }

template <typename T>
void forward_v(T a) { f(a); }

template <typename T>
void forward_r(T& a) { f(a); }

template <typename T>
void forward_p(T&& a) { f(std::forward<T>(a)); }

int main() {
    int x = 0;
    int&& rrx = std::move(x);

    std::cout << "forward by value:\n";
    forward_v(x); // lvalue
    forward_v(1); // prvalue
    forward_v(rrx); // lvalue!!!

    std::cout << "forward by ref:\n";
    forward_r(x);
    // forward_r(1); 
    forward_r(rrx);

    std::cout << "forward perfectly:\n";
    forward_p(x); // lvalue
    forward_p(1); // prvalue
    forward_p(rrx); // lvalue!!!

    return 0;
}
