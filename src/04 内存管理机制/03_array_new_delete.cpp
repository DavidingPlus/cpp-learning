#include <iostream>
using namespace std;
#define size 3

class A {
public:
    A() : _id(0) { cout << "default ctor. this = " << this << " id = " << _id << endl; }
    A(int id) : _id(id) { cout << "ctor. this = " << this << " id = " << _id << endl; }
    ~A() { cout << "dtor. this = " << this << " id = " << _id << endl; }

public:
    int _id;
};

int main() {
    A* buf = new A[size];  // A必须有默认构造函数，否则会报错
    A* tmp = buf;

    cout << "buf= " << buf << " tmp= " << tmp << endl;

    for (int i = 0; i < size; ++i)
        new (tmp++) A(i);  // placement new , ctor 三次

    cout << "buf= " << buf << " tmp= " << tmp << endl;

    delete[] buf;  // dtor 3次，次序反过来 3 2 1

    return 0;
}
