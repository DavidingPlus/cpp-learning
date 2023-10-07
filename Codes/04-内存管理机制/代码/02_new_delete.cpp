#include <iostream>
using namespace std;
#include <string>

class A {
public:
    A() = default;
    A(int id) : _id(id) { cout << "ctor. this = " << this << " id = " << id << endl; }
    ~A() { cout << "dtor. this = " << this << endl; }

    int _id;
};

int main() {
    string* pstr = new string;
    cout << "str= " << *pstr << endl;

    // pstr->string::string("hello");  // ‘class std::__cxx11::basic_string<char>’ has no member named ‘string’
    // pstr->~string();//crash

    cout << "str= " << *pstr << endl;

    A* pA = new A(1);
    cout << pA->_id << endl;  // 1

    // pA->A::A(3);//cannot call constructor ‘A::A’ directly
    // A::A(5);

    cout << pA->_id << endl;

    delete pA;

    return 0;
}
