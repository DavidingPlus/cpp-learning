#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

//二元谓词
class myCompare
{
public:
    bool operator()(int val1, int val2) const
    {
        return val1 > val2;
    }
};

void printVector(const vector<int> &v)
{
    for (vector<int>::const_iterator iter = v.begin(); iter != v.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;
}

void test01()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(40);
    v.push_back(20);
    v.push_back(30);
    v.push_back(50);

    sort(v.begin(), v.end());
    printVector(v);

    cout << "--------------------------" << endl;

    //使用函数对象 改变算法策略 变为排序规则为从大到小
    sort(v.begin(), v.end(), myCompare());
    printVector(v);
}

int main()
{
    test01();

    return 0;
}
