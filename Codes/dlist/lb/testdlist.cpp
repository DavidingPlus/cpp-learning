//testdlist.cpp

#include <iostream>
#include <format>

#include "dlist.h"

struct foo {
    int i;
    double d;

    foo(int _i = 0, double _d = 0) : i(_i), d(_d) {}
    foo(foo const& f) : i(f.i), d(f.d) {
        std::cout << "foo: copy ctor" << std::endl;
    }
};

std::ostream& operator<<(std::ostream& os, foo const& f) {
    return os << std::format("({},{})", f.i, f.d);
}

template <typename iterator>
void print_l(iterator first, iterator last) {
    if (first.distance(last) < 0) return;

    for (auto itr = first; itr != last; ++itr) { 
        std::cout << *itr << ' '; 
    };
    std::cout << std::endl;
}

int main() {
    dlist<foo> l2;
    for (int i = 1; i <= 10; ++i) {
        l2.emplace_back(i, i * 1.23);
    }

    // for (auto& e : l2)
    //     std::cout << e;
    // std::cout << std::endl;

    print_l(l2.begin(), l2.end());

    print_l(l2.begin() + 3, l2.end() - 2);

    print_l(l2.rbegin() + 6, l2.rend() - 2);

    return 0;
}