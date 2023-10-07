#include <iostream>
using namespace std;
#include <functional>
using namespace std::placeholders; // 使用占位符 _1 _2 _3这些
#include <vector>
#include <algorithm>

double my_divide(double x, double y)
{
    return x / y;
}

struct MyPair
{
    double a, b;
    double multiply() { return a * b; }
};

void Bind_Functions()
{
    // binding functions
    auto fn_five = bind(my_divide, 10, 2); // return 10.0/2.0
    cout << fn_five() << endl;             // 5

    auto fn_half = bind(my_divide, _1, 2); // return x/2.0
    cout << fn_half(10) << endl;           // 5

    auto fn_rounding = bind(my_divide, _2, _1); // 第一参数为除数，第二参数为被除数 return y/x
    cout << fn_rounding(10, 2) << endl;         // 0.2

    auto fn_invert = bind<int>(my_divide, _1, _2); // int 代表希望返回的类型 return int(x/y)
    cout << fn_invert(10, 3) << endl;              // 3
}

void Bind_Members()
{
    MyPair ten_two{10, 2};

    auto bound_memfn = bind(&MyPair::multiply, _1); // return x.multiply()
    cout << bound_memfn(ten_two) << endl;           // 20

    auto bound_memdata = bind(&MyPair::a, ten_two); // return tentwo.a
    cout << bound_memdata() << endl;                // 10

    auto bound_memdata2 = bind(&MyPair::b, _1); // return x.b
    cout << bound_memdata2(ten_two) << endl;    // 2

    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto _fn = bind(less<int>(), _1, 5);
    cout << count_if(v.cbegin(), v.cend(), _fn) << endl;
    cout << count_if(v.begin(), v.end(), bind(less<int>(), _1, 5)) << endl;
}

int main()
{
    Bind_Functions();
    Bind_Members();

    return 0;
}
