#include <iostream>
using namespace std;
#include <string>
#include <tuple>
#include <complex>
#include <typeinfo>
#include "29_tuple_print.h"

// 重载tuple << 运算符
// inline ostream &
// operator<<(ostream &out, const tuple<int, float, string> &t)
// {
//     out << get<0>(t) << ' ' << get<1>(t) << ' ' << get<2>(t);
//     return out;
// }

void test()
{
    cout << "string,sizeof = " << sizeof(string) << endl;                   // 32
    cout << "double,sizeof = " << sizeof(double) << endl;                   // 8
    cout << "float,sizeof = " << sizeof(float) << endl;                     // 4
    cout << "int,sizeof = " << sizeof(int) << endl;                         // 4
    cout << "complex<double>,sizeof = " << sizeof(complex<double>) << endl; // 16

    tuple<string, int, int, complex<double>> t;
    cout << "tuple<string,int,int,complex<double>,sizeof = " << sizeof(t) << endl; // 56

    tuple<int, float, string> t1(41, 6.3, "nico");
    cout << "tuple<int,float,string>,sizeof = " << sizeof(t1) << endl;              // 40
    cout << "t1: " << get<0>(t1) << ' ' << get<1>(t1) << ' ' << get<2>(t1) << endl; // 取出其中的元素用法

    auto t2 = make_tuple(22, 44.0, "stacy");
    get<1>(t1) = get<1>(t2);
    cout << "t1: " << get<0>(t1) << ' ' << get<1>(t1) << ' ' << get<2>(t1) << endl;
    cout << "t2: " << get<0>(t2) << ' ' << get<1>(t2) << ' ' << get<2>(t2) << endl;

    // 比较大小
    if (t1 < t2)
        cout << "t1 < t2" << endl;
    else if (t1 > t2)
        cout << "t1 > t2" << endl;
    else
        cout << "t1 == t2" << endl;
    t1 = t2; // 赋值操作
    cout << t2 << endl;

    typedef tuple<int, float, string> TupleType;
    cout << tuple_size<TupleType>::value << endl; // 3

    typedef tuple_element<2, TupleType>::type Type1; // string
    cout << typeid(Type1).name() << endl;

    tuple<int, float, string> t3(77, 1.1, "more light");
    int i1;
    float f1;
    string s1;
    tie(i1, f1, s1) = t3; // 将这t3的三个属性绑定到这三个变量上面
    cout << "i1 = " << i1 << " f1 = " << f1 << " s1= " << s1 << endl;
}

int main()
{
    test();

    return 0;
}
