#include <iostream>
using namespace std;

void *myAlloc(size_t size)
{
    return malloc(size);
}

void myFree(void *ptr)
{
    return free(ptr);
}

inline void *operator new(size_t size)
{
    cout << "global new" << endl;
    return myAlloc(size);
}

inline void *operator new[](size_t size)
{
    cout << "global new[]" << endl;
    return myAlloc(size);
}

inline void operator delete(void *ptr)
{
    cout << "global delete" << endl;
    myFree(ptr);
}

inline void operator delete[](void *ptr)
{
    cout << "global delete[]" << endl;
    myFree(ptr);
}

int main()
{
    return 0;
}
