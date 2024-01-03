#include <iostream>
using namespace std;
#include <functional>
#include <algorithm>
#include <vector>

/*
template<class T> bool equal_to<T>                    //等于
template<class T> bool not_equal_to<T>            //不等于
template<class T> bool greater<T>                      //大于
template<class T> bool greater_equal<T>          //大于等于
template<class T> bool less<T>                           //小于
template<class T> bool less_equal<T>              //小于等于
*/

// 内建函数对象 关系仿函数
// 大于 greater
class myCompare
{
public:
    bool operator()(const int val1, const int val2) const
    {
        return val1 > val2;
    }
};

void test01()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(50);
    v.push_back(40);
    v.push_back(20);

    for (auto iter = v.begin(); iter != v.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;

    //降序
    // sort(v.begin(), v.end(), myCompare());
    // greater<int>() 内建函数对象
    sort(v.begin(), v.end(), greater<int>());

    for (auto iter = v.begin(); iter != v.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;
}

int main()
{
    test01();

    return 0;
}
