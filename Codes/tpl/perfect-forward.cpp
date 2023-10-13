// perfect-forward.cpp
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
    forward_v(x);    // lvalue
    forward_v(1);    // lvalue，纯右值!但是这里会发生类型折叠，导致1进去之后转发之后变为左值
    forward_v(rrx);  // lvalue!!! rrx是一个右值引用，但是他是一个左值，会被转发给左值引用

    std::cout << "forward by ref:\n";
    forward_r(x);
    // forward_r(1);
    forward_r(rrx);  // 传递的是一个左值

    std::cout << "forward by perfectly:\n";
    forward_p(x);    // lvalue
    forward_p(1);    // prvalue，完美转发
    forward_p(rrx);  // lvalue!!! rrx是一个右值引用，但是他是一个左值，会被转发给左值引用

    return 0;
}
