#include "26_Stone.h"
using namespace std;
#include <bitset>
#include <iostream>
#include <string>
#include <tuple>

// Stone
inline ostream&
operator<<(ostream& os, const Stone& sto) {
    return os << "( " << sto.getLen() << " , " << sto.getWid() << " , " << sto.getHei() << " , " << sto.getWei() << " )";
}

template <size_t index, size_t max, typename... Args>
struct tuple_print {
    static inline void print(const tuple<Args...>& t, ostream& os) {
        os << get<index>(t) << " ; ";
        tuple_print<index + 1, max, Args...>::print(t, os);
    }
};

template <size_t max, typename... Args>
struct tuple_print<max, max, Args...> {
    static inline void print(const tuple<Args...>& t, ostream& os) {
        os << get<max>(t);
    }
};

template <typename... Args>
inline ostream&
operator<<(ostream& os, const tuple<Args...>& t) {
    os << "[ ";
    tuple_print<0, sizeof...(Args) - 1, Args...>::print(t, os);
    return os << " ]";
}

int main() {
    Stone s(1.2, 2.3, 3.4, 4.5);
    tuple<int, double, string, Stone> t{1, 3.14, "hello", s};
    cout << t << endl;

    cout << make_tuple(7.5, string("hello"), bitset<16>(377), 42) << endl;

    return 0;
}
