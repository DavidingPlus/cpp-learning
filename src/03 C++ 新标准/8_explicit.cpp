#include <iostream>
using namespace std;

struct Complex
{
    int real, imag;

    explicit Complex(int re, int im = 0) : real(re), imag(im) {}

    Complex operator+(const Complex &x)
    {
        return Complex(real + x.real, imag + x.imag);
    }
};

inline ostream &
operator<<(ostream &os, const Complex &x)
{
    os << '(' << x.real << ',' << x.imag << ')';
    return os;
}

int main()
{
    Complex c1(12, 5);
    // Complex c2 = c1 + 5; // 加了explicit关键字就不允许编译器直接把5转化为 Complex 类型了
    cout << c1 << endl;

    return 0;
}
