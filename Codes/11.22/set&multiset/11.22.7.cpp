#include <iostream>
using namespace std;
#include <set>

//利用仿函数，可以改变排序规则
// 利用仿函数 重载()号运算符 所有需要将排序的规则写成结构体或者类 并且在其中重载()运算符!!!

// set容器排序
// set容器存放内置数据类型
class myCompare
{
public:
    bool operator()(const int val1, const int val2) const
    //利用仿函数的时候不要忘了 只读 并且 后面加上const
    {
        return val1 > val2;
    }
};

void test01()
{
    set<int> s1;
    s1.insert(10);
    s1.insert(40);
    s1.insert(20);
    s1.insert(30);
    s1.insert(50);

    //默认从小到大
    for (auto iter = s1.begin(); iter != s1.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;

    //指定排序规则为从大到小 利用仿函数(重载()运算符)
    set<int, myCompare> s2;
    s2.insert(10);
    s2.insert(40);
    s2.insert(20);
    s2.insert(30);
    s2.insert(50);

    //注意这里的细节
    for (set<int, myCompare>::iterator iter = s2.begin(); iter != s2.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;
}

int main()
{
    test01();

    return 0;
}
