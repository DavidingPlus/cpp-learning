#include <iostream>
using namespace std;
#include <string>

class Foo
{
public:
    int _id;

public:
    Foo() : _id(0) { cout << "default ctor.this = " << this << " id = " << _id << endl; }
    Foo(int id) : _id(id) { cout << "ctor.this = " << this << " id = " << _id << endl; }

    // virtual
    virtual ~Foo() { cout << "dtor.this = " << this << " id = " << _id << endl; }

    void *operator new(size_t size);
    void operator delete(void *ptr, size_t size);
    void *operator new[](size_t size);
    void operator delete[](void *ptr, size_t size);

    // many placement new
    void *operator new(size_t size, void *start);

    void *operator new(size_t size, long extra);
};

void *Foo::operator new(size_t size)
{
    Foo *p = static_cast<Foo *>(malloc(size));
    cout << "Foo::operator new(), size = " << size << "\treturn : " << p << endl;
    return p;
}

void Foo::operator delete(void *ptr, size_t size)
{
    cout << "Foo::operator delete(), ptr = " << ptr << "\tsize = " << size << endl;
    free(ptr);
}

void *Foo::operator new[](size_t size)
{
    Foo *p = static_cast<Foo *>(malloc(size));
    cout << "Foo::operator new[](), size = " << size << "\treturn : " << p << endl;
    return p;
}

void Foo::operator delete[](void *ptr, size_t size)
{
    cout << "Foo::operator delete[](), ptr = " << ptr << "\tsize = " << size << endl;
    free(ptr);
}

// many placement new
void *Foo::operator new(size_t size, void *start)
{
    return start;
}

// 这才是崭新的placement new
void *Foo::operator new(size_t size, long extra)
{
    return malloc(size + extra);
}

int main()
{
    cout << "sizeof(Foo) = " << sizeof(Foo) << endl
         << endl;

    cout << "Foo------------------------------------------------------------" << endl;

    Foo *p0 = ::new Foo;
    Foo *p = new (p0) Foo(7); // 这两个指针指向一块内存
    delete p;

    Foo *pp = new (2) Foo;

    cout << endl;

    Foo *pArray = new Foo[5]{1, 2, 3, 4, 5};
    delete[] pArray;

    cout << endl
         << "Global------------------------------------------------------------" << endl;

    Foo *p2 = ::new Foo;
    ::delete p2;

    cout << endl;

    Foo *pArray2 = ::new Foo[5]{1, 2, 3, 4, 5};
    ::delete[] pArray2;

    return 0;
}
