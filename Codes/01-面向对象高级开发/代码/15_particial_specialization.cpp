#include <iostream>

using namespace std;

template <typename T>
struct TC // 泛化的TC类模板
{
    void functest()
    {
        cout << "泛化版本" << endl;
    }
};
// 偏特化：模板参数范围上的特化版本
template <typename T>
struct TC<const T> // const的特化版本
{
    // 对特化版本做单独处理
    void functest()
    {
        cout << "偏特化const版本" << endl;
    }
};
template <typename T>
struct TC<T *> // T* 的特化版本
{
    void functest()
    {
        cout << "const T*特化版本" << endl;
    }
};
template <typename T>
struct TC<T &> // T& 的特化版本
{
    void functest()
    {
        cout << "T &左值引用特化版本" << endl;
    }
};

template <typename T>
struct TC<T &&> // T&& 的特化版本
{
    void functest()
    {
        cout << "T &&右值引用特化版本" << endl;
    }
};

int main()
{
    TC<double> td;
    td.functest();

    TC<const double> td2;
    td2.functest();

    TC<double *> tpd;
    tpd.functest();

    TC<const double *> tpd2;
    tpd2.functest();

    TC<int &> tcyi;
    tcyi.functest();

    TC<int &&> tcyi2;
    tcyi2.functest();

    return 0;
}
