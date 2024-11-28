#include <iostream>
using namespace std;

namespace Test {
template <typename Value_Type1, typename Value_Type2>
auto add(const Value_Type1& x, const Value_Type2& y)
    -> decltype(x + y) {  // 不写在前面是因为编译器先后次序编译不认识x,y，所以放在后面用 -> 来指明auto的类型
    return x + y;
}
}  // namespace Test

using namespace Test;
int main() {
    cout << add(1, 2) << endl;
    cout << add(1.1, 2) << endl;

    return 0;
}
