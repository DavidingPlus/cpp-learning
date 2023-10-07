#include <iostream>
using namespace std;

namespace MaxMin {
// Max
template <typename Value_Type>
Value_Type maximum(const Value_Type& val) {
    return val;
}

// 将array分为1 和 n-1 , n-1里面再递归选出最大的与第一个比较就好了
template <typename Value_Type, typename... Args>
Value_Type maximum(const Value_Type& val, const Args&... args) {
    return max(val, maximum(args...));
}

// Min
template <typename Value_Type>
Value_Type minimum(const Value_Type& val) {
    return val;
}

template <typename Value_Type, typename... Args>
Value_Type minimum(const Value_Type& val, const Args&... args) {
    return min(val, minimum(args...));
}
}  // namespace MaxMin

using namespace MaxMin;
int main() {
    cout << minimum(1) << endl;
    cout << maximum(6) << endl;
    cout << minimum(1, 2, 3, 4, 5, 6) << endl;
    cout << maximum(1, 2, 3, 4, 5, 6) << endl;

    return 0;
}
