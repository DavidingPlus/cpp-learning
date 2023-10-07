#include <iostream>
using namespace std;
#include "std_alloc_2nd.h"

void test_G29_alloc() {
    cout << "test_global_allocator_with_16_freelist().......... \n";

    void *p1 = alloc::allocate(120);
    void *p2 = alloc::allocate(72);
    void *p3 = alloc::allocate(60);  // 不是 8 倍數

    cout << p1 << endl
         << p2 << endl
         << p3 << endl;

    alloc::deallocate(p1, 120);
    alloc::deallocate(p2, 72);
    alloc::deallocate(p3, 60);

    // 以下, 不能搭配容器來測試, 因為新版 G++ 對於 allocator 有更多要求 (詢問更多 typedef 而 alloc 都無法回答)
    // 它其實就是 G4.9 __pool_alloc，所以讓 G4.9容器使用 __pool_alloc 也就等同於這裡所要的測試
    /*
        vector<int, simple_alloc<int,alloc>> v;
        for(int i=0; i< 1000; ++i)
            v.push_back(i);
        for(int i=700; i< 720; ++i)
            cout << v[i] << ' ';
    */
}

int main() {
    test_G29_alloc();

    return 0;
}
