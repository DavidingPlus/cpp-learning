#include <iostream>
using namespace std;
#include <algorithm>
#include <vector>

// reverse(iterator beg, iterator end);
//  反转指定范围的元素
//  beg 开始迭代器
//  end 结束迭代器

void myPrint(const int val)
{
    cout << val << ' ';
}

class myPrint_Pred
{
public:
    void operator()(const int val) const
    {
        cout << val << ' ';
    }
};

void test01()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(50);
    v.push_back(20);
    v.push_back(40);

    cout << "反转前： " << endl;
    for_each(v.begin(), v.end(), myPrint);
    cout << endl;

    reverse(v.begin(), v.end());

    cout << "反转后： " << endl;
    for_each(v.begin(), v.end(), myPrint_Pred());
    cout << endl;
}

int main()
{
    test01();

    return 0;
}
