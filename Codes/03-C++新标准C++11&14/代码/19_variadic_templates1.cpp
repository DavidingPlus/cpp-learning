#include <iostream>
using namespace std;

static int value = 0;

namespace Test {
inline void _func() {}

template <typename Value_Type, typename... Types>
inline void _func(const Value_Type& firstArg, const Types&... args) {
    ++value;
    _func(args...);
}

// 包装
template <typename... Types>
inline void func(const Types&... args) {
    _func(args...);
    cout << "value: " << value << endl;
}

}  // namespace Test

using namespace Test;
int main() {
    func(1, 2, 3, 4, 5);             // 5
    func("string", "fuck", 2, 1.2);  // 9

    return 0;
}
