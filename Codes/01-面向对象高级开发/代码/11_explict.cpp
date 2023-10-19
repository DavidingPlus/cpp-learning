#include <iostream>
using namespace std;

class Fraction
{
public:
    // explict-one-argument ctor
    explicit Fraction(int num, int den = 1) : _numerator(num), _denominator(den) {}
    // explict关键字的含义 防止类构造函数的隐式自动转换
    // 就是说这里由于只需要传入一个参数，所以编译器很可能会把数字隐式转化为Fraction对象
    // 但是加上了explict之后,明确指出不要让编译器这么干，要生成Fraction对象只能显式调用构造函数!!!!

    // conversion function
    operator double() const
    {
        return (double)this->_numerator / (double)this->_denominator;
    }

    // 重载加号运算符
    Fraction operator+(const Fraction &f) { ; }

private:
    int _numerator;
    int _denominator;
};

int main()
{
    Fraction f(3, 5);
    // Fraction d = f + 4; // 这里仍然会错，因为4不会被转化为Fraction了，也就没有办法直接相加
    double e = f + 4; // 这里显然就可以了，因为存在转换函数
    cout << e << endl;

    return 0;
}
