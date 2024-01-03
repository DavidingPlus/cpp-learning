#include <iostream>
using namespace std;
#include <vector>

// vector容器中的数据存取

/*
at(int idx); //返回索引idx所指的数据
operator[];  //返回索引idx所指的数据
front();     //返回容器中第一个数据元素
back();      //返回容器中最后一个数据元素
*/

void test01()
{
    vector<int> v1;
    for (auto i = 0; i < 10; ++i)
        v1.push_back(i);

    //利用[]方式访问数组元素
    for (auto i = 0; i < v1.size(); ++i)
        cout << v1[i] << ' ';
    cout << endl;

    //利用at方式访问元素
    for (auto i = 0; i < v1.size(); ++i)
        cout << v1.at(i) << ' ';
    cout << endl;

    //获取第一个元素
    cout << "第一个元素为: " << v1.front() << endl;
    //获取最后一个元素
    cout << "最后一个元素为: " << v1.back() << endl;
}

int main()
{
    test01();

    return 0;
}
