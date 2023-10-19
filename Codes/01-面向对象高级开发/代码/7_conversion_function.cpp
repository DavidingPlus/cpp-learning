#include <iostream>
using namespace std;

class Fraction
{
public:
    Fraction(int num, int den = 1) : _numerator(num), _denominator(den) {}

    // 转换函数
    operator double() const
    {
        return (double)this->_numerator / (double)this->_denominator;
    }

private:
    int _numerator;
    int _denominator;
};

int main()
{
    Fraction f(3, 5);
    double d = 4 + f;
    cout << d << endl;

    return 0;
}
