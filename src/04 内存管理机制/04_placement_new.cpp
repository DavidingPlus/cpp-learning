#include <iostream>
using namespace std;

class Complex {
public:
    Complex() : _re(0), _im(0) {}
    Complex(double re, double im) : _re(re), _im(im) {}

public:
    double _re, _im;
};

int main() {
    char* buf = new char[sizeof(Complex) * 3];
    // 现在想把一个Complex对象动态开辟在buf的一个Complex单元，调用placement new
    Complex* pc = new (buf) Complex(1, 2);

    delete[] buf;

    return 0;
}
