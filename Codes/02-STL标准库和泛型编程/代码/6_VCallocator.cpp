#include <iostream>
using namespace std;
#include <vector>
#include <ext\pool_allocator.h>
#include <list>

int main()
{
    // 建立分配器
    int *p = allocator<int>().allocate(512, (int *)0);
    // 归还
    allocator<int>().deallocate(p, 512);

    list<string, __gnu_cxx::__pool_alloc<string>> l;

    return 0;
}
