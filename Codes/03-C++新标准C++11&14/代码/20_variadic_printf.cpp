#include <iostream>
using namespace std;

namespace Print {
// 代码中抛出异常的部分先不管
// 用参数包重写printf函数 理解
inline void myprintf(const char* str) {
    while (*str) {
        if (*str == '%' && *(++str) != '%')  // 已经没有参数包了还有控制符号，不对劲，抛出异常
            throw runtime_error("invalid format string: missing arguments.");
        cout << *str++;
    }
}

template <typename Value_Type, typename... Types>
inline void myprintf(const char* str, const Value_Type& val, const Types&... args) {
    while (*str) {
        if (*str == '%' && *(++str) != '%') {  // 遇到控制符号了
            cout << val;
            myprintf(++str, args...);
            return;
        }
        cout << *str++;
    }
    throw logic_error("extra arguments provided to myprintf");
}
}  // namespace Print

using namespace Print;
int main() {
    myprintf("hello\n");

    int* pi = new int;
    // 但是这么模拟有一个很大的问题，就是控制符号我们没去管，但是介于只是一个简单的模拟，还是可以的
    myprintf("%d %s %p %f\n", 15, "This is Ace.", pi, 3.1415926535);
    delete pi;

    return 0;
}
