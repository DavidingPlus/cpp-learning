#include <iostream>
using namespace std;

template <class Type>
struct Fuck
{
};

// 模板特化
template <>
struct Fuck<int>
{
    int operator()(int val) const { return val; }
};

template <>
struct Fuck<string>
{
    string operator()(string ch) const { return ch; }
};

template <>
struct Fuck<double>
{
    double operator()(double val) const { return val; }
};

int main()
{
    // 匿名对象
    cout << Fuck<int>()(1) << endl;
    cout << Fuck<string>()("fuck") << endl;
    cout << Fuck<double>()(3.14) << endl;

    return 0;
}
