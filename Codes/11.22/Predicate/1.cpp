#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

/*
返回bool类型的仿函数称为谓词 !!!!!
如果operator()接受一个参数，那么叫做一元谓词
如果operator()接受两个参数，那么叫做二元谓词
*/

//一元谓词
//仿函数返回值类型为bool为谓词
class GreaterFive
{
public:
    bool operator()(int val) const
    {
        return val > 5;
    }
};

void test01()
{
    vector<int> v;
    for (auto i = 0; i < 10; ++i)
        v.push_back(i);

    //查找容器中有没有大于5的数字
    // GreaterFive() 匿名函数对象 这里为一元谓词
    auto iter = find_if(v.begin(), v.end(), GreaterFive());
    if (iter == v.end())
        cout << "未找到" << endl;
    else
        cout << "找到了大于5的数字是: " << *iter << endl;
}

int main()
{
    test01();

    return 0;
}
