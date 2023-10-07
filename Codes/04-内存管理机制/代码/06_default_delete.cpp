#include <iostream>
using namespace std;

class Foo {
public:
    long _x;

public:
    Foo(long x = 0) : _x(x) {}

    // 这两个东西不能default，因为编译器没有默认的版本，default只能用在big three当中，即default ctor,copy/move asgn,copy/move ctor,dtor当中
    // static void *operator new(size_t size) = default;                 //[Error] cannot be defaulted
    // static void operator delete(void *pdead, size_t size) = default;  //[Error] cannot be defaulted
    static void *operator new[](size_t size) = delete;
    static void operator delete[](void *pdead, size_t size) = delete;
};

class Goo {
public:
    long _x;

public:
    Goo(long x = 0) : _x(x) {}

    static void *operator new(size_t size) = delete;
    static void operator delete(void *pdead, size_t size) = delete;
};

void test_delete_and_default_for_new() {
    cout << "test_delete_and_default_for_new().......... \n";

    Foo *p1 = new Foo(5);
    delete p1;
    // Foo* pF = new Foo[10];	//[Error] use of deleted function 'static void* Foo::operator new [](size_t)'
    // delete [] pF;			//[Error] use of deleted function 'static void Foo::operator delete [](void*, size_t)'

    // Goo* p2 = new Goo(7);	//[Error] use of deleted function 'static void* Goo::operator new(size_t)'
    // delete p2;				//[Error] use of deleted function 'static void Goo::operator delete(void*, size_t)'
    Goo *pG = new Goo[10];
    delete[] pG;
}

int main() {
    test_delete_and_default_for_new();

    return 0;
}
