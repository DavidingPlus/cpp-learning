#include <iostream>
using namespace std;

void* myAlloc(size_t size) {
    return malloc(size);
}

void myFree(void* ptr) {
    return free(ptr);
}

// 重载全局 operator new 和 operator delete
inline void* operator new(size_t size) {
    cout << "global new()" << endl;
    return myAlloc(size);
}

inline void* operator new[](size_t size) {
    cout << "global new[]()" << endl;
    return myAlloc(size);
}

inline void operator delete(void* ptr) noexcept {
    cout << "global delete()" << endl;
    myFree(ptr);
}

inline void operator delete[](void* ptr) noexcept {
    cout << "global delete[]()" << endl;
    myFree(ptr);
}

int main() {
    // new,delete
    int* pa = new int;
    delete pa;

    // array new,array delete0
    int* pb = new int[3];
    delete[] pb;

    return 0;
}
