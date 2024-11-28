#include <iostream>
using namespace std;
#include <ext/pool_allocator.h>
#include <vector>

template <typename Alloc>
void cookie_test(Alloc alloc, size_t n) {
    typename Alloc::value_type *p1, *p2, *p3;  // 需有 typename
    p1 = alloc.allocate(n);                    // allocate() and deallocate() 是 non-static, 需以 object 呼叫之.
    p2 = alloc.allocate(n);
    p3 = alloc.allocate(n);

    cout << "p1= " << p1 << '\t' << "p2= " << p2 << '\t' << "p3= " << p3 << '\n';

    alloc.deallocate(p1, sizeof(typename Alloc::value_type));  // 需有 typename
    alloc.deallocate(p2, sizeof(typename Alloc::value_type));  // 有些 allocator 對於 2nd argument 的值無所謂
    alloc.deallocate(p3, sizeof(typename Alloc::value_type));
}

int main() {
    // pool_alloc
    cout << sizeof(__gnu_cxx::__pool_alloc<int>) << endl;
    vector<int, __gnu_cxx::__pool_alloc<int>> vecPool;
    cookie_test(__gnu_cxx::__pool_alloc<double>(), 1);  // 相邻相差08H说明每一块不带cookie

    cout << endl;

    // allocator
    cout << sizeof(std::allocator<int>) << endl;
    vector<int, std::allocator<int>> vec;
    cookie_test(std::allocator<double>(), 1);  // 相邻相差20H说明每一块带有cookie

    return 0;
}
