#include <complex>
#include <iostream>
using namespace std;
#include "__allocator.h"

// macro 宏
#define DECLARE_POOL_ALLOC()                                           \
public:                                                                \
    void *operator new(size_t size) { return myAlloc.allocate(size); } \
    void operator delete(void *p) { myAlloc.deallocate(p, 0); }        \
                                                                       \
protected:                                                             \
    static __allocator myAlloc;

#define IMPLEMENT_POOL_ALLOC(class_name) \
    __allocator class_name::myAlloc;

class Foo {
    DECLARE_POOL_ALLOC()
public:
    long L;
    string str;

public:
    Foo(long l) : L(l) {}
};
// in class implementation file
IMPLEMENT_POOL_ALLOC(Foo)

//  in class definition file
class Goo {
    DECLARE_POOL_ALLOC()
public:
    complex<double> c;
    string str;

public:
    Goo(const complex<double> &x) : c(x) {}
};
// in class implementation file
IMPLEMENT_POOL_ALLOC(Goo)

//-------------
void test_static_allocator() {
    cout << "test_static_allocator().......... \n";

    {
        cout << endl;
        Foo *p[100];

        cout << "sizeof(Foo)= " << sizeof(Foo) << endl;
        for (int i = 0; i < 23; ++i) {  // 23,任意數, 隨意看看結果
            p[i] = new Foo(i);
            cout << p[i] << ' ' << p[i]->L << endl;
        }
        // Foo::myAlloc.check();

        for (int i = 0; i < 23; ++i) {
            delete p[i];
        }
        // Foo::myAlloc.check();

        cout << endl;
    }

    {
        cout << endl;
        Goo *p[100];

        cout << "sizeof(Goo)= " << sizeof(Goo) << endl;
        for (int i = 0; i < 17; ++i) {  // 17,任意數, 隨意看看結果
            p[i] = new Goo(complex<double>(i, i));
            cout << p[i] << ' ' << p[i]->c << endl;
        }
        // Goo::myAlloc.check();

        for (int i = 0; i < 17; ++i) {
            delete p[i];
        }
        // Goo::myAlloc.check();

        cout << endl;
    }
}

int main() {
    test_static_allocator();

    return 0;
}
