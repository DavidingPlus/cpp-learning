#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

//常用拷贝和替换算法 copy
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
    vector<int> v1;
    for (int i = 0; i < 10; ++i)
        v1.push_back(i);

    vector<int> v2;
    //在拷贝之前v2需要提前开辟空间!!!
    v2.resize(v1.size());
    copy(v1.begin(), v1.end(), v2.begin());
    for_each(v2.begin(), v2.end(), myPrint_Pred());
    cout << endl;
}

int main()
{
    test01();

    return 0;
}
