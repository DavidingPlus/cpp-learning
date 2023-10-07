#include <iostream>
using namespace std;
#include <bitset>
#include <string>
#include <tuple>

namespace PRINT {

template <int index, int max, typename... Args>
struct Tuple_Print {
    inline static void print(ostream& os, const tuple<Args...>& t) {
        os << get<index>(t) << (index + 1 != max ? "," : "");  // 如果不是最后一个就是 , 号
        Tuple_Print<index + 1, max, Args...>::print(os, t);
    }
};

// 递归终点
template <int max, typename... Args>
struct Tuple_Print<max, max, Args...> {
    inline static void print(ostream& os, const tuple<Args...>& t) {}
};

}  // namespace PRINT

template <typename... Args>
inline ostream&
operator<<(ostream& os, const tuple<Args...>& t) {
    os << "[";
    PRINT::Tuple_Print<0, sizeof...(Args), Args...>::print(os, t);
    return os << "]";
}

int main() {
    cout << make_tuple(7.5, string("hello"), bitset<16>(377), 42) << endl;

    return 0;
}
