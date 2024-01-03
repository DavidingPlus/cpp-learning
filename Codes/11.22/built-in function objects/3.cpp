#include <iostream>
using namespace std;
#include <functional>
#include <vector>
#include <algorithm>

/*
template<class T> bool logical_and<T>  //逻辑与
template<class T> bool logical_or<T>   //逻辑或
template<class T> bool logical_not<T>  //逻辑非
*/

//内建函数对象仿函数
class myLogical_not
{
public:
    bool operator()(bool val)
    {
        //异或运算符0^1=1;1^1=0;2^1=3;3^1=2;
        return val ^ 1;
    }
};

void test01()
{
    vector<bool> v;
    v.push_back(true);
    v.push_back(false);
    v.push_back(true);
    v.push_back(false);

    for (vector<bool>::iterator iter = v.begin(); iter != v.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;

    //利用逻辑非 将容器v 搬运到容器v2中 并执行取反操作
    vector<bool> v2;
    v2.resize(v.size());

    // transform(v.begin(), v.end(), v2.begin(), myLogical_not());
    transform(v.begin(), v.end(), v2.begin(), logical_not<bool>());

    for (vector<bool>::iterator iter = v2.begin(); iter != v2.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;
}

int main()
{
    test01();

    return 0;
}
