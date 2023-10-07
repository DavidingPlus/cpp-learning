#include <iostream>
using namespace std;
#include <complex>
#include <ext/pool_allocator.h>

int main() {
    // 三种使用方法
    void* p1 = malloc(512);  // 512 bytes
    cout << p1 << endl;
    free(p1);

    complex<int>* p2 = new complex<int>;
    cout << p2 << endl;
    delete p2;

    void* p3 = ::operator new(512);  // 512 bytes
    cout << p3 << endl;
    ::operator delete(p3);

// 以下使用 C++ 标准库提供的 allocators。
// 虽然接口都有标准规格，但是调用方式略有区别
#ifdef _MSC_VER
    // 以下兩函數都是 non-static，定要通過 object 調用。以下分配 3 個 ints.
    int* p4 = allocator<int>().allocate(3, (int*)0);
    allocator<int>().deallocate(p4, 3);
#endif

#ifdef __BORLANDC__
    // 以下兩函數都是 non-static，定要通過 object 調用。以下分配 5 個 ints.
    int* p4 = allocator<int>().allocate(5);
    allocator<int>().deallocate(p4, 5);
#endif

#ifdef __GNUC__
    // 以下兩函數都是 static，可通過全名調用之。以下分配 512 bytes.
    // void* p4 = alloc::allocate(512);
    // alloc::deallocate(p4, 512);

    // 以下兩函數都是 non-static，定要通過 object 調用。以下分配 7 個 ints.
    void* p4 = allocator<int>().allocate(7);
    cout << p4 << endl;
    allocator<int>().deallocate((int*)p4, 7);

    // 以下兩函數都是 non-static，定要通過 object 調用。以下分配 9 個 ints.
    void* p5 = __gnu_cxx::__pool_alloc<int>().allocate(9);
    cout << p5 << endl;
    __gnu_cxx::__pool_alloc<int>().deallocate((int*)p5, 9);
#endif

    return 0;
}
