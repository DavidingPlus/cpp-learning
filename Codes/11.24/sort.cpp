#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <functional>

// sort(iterator beg, iterator end, _Pred);
//  按值查找元素，找到返回指定位置迭代器，找不到返回结束迭代器位置
//   beg    开始迭代器
//   end    结束迭代器
//  _Pred  谓词

void myPrint(const int val) { cout << val << ' '; }

void test01()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(50);
    v.push_back(20);
    v.push_back(40);

    // sort默认从小到大排序
    sort(v.begin(), v.end());
    //注意谓词(函数对象)和函数的不同 一个是类 一个是函数
    //谓词的返回值是 bool 而函数可以是任何类型!!!!
    for_each(v.begin(), v.end(), myPrint);
    cout << endl;

    //从大到小排序
    sort(v.begin(), v.end(), greater_equal<int>());
    for_each(v.begin(), v.end(), myPrint);
    cout << endl;
}

int main()
{
    test01();

    return 0;
}
