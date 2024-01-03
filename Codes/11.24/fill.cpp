#include <iostream>
using namespace std;
#include <vector>
#include <numeric>
#include <algorithm>

//向容器中填充指定的元素
// fill(iterator beg, iterator end, value);
// 向容器中填充元素
// beg 开始迭代器
// end 结束迭代器
// value 填充的值

class myPrint_Pred
{
public:
    void operator()(const int val) const { cout << val << ' '; }
};

void test01()
{
    vector<int> v;
    v.resize(10);
    //填充
    fill(v.begin(), v.end(), 100);

    for_each(v.begin(), v.end(), myPrint_Pred());
    cout << endl;
}

int main()
{
    test01();

    return 0;
}
