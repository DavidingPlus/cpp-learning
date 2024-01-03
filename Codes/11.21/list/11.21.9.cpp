#include <iostream>
using namespace std;
#include <list>

// list容器 数据存取

/*
front(); //返回第一个元素。
back();  //返回最后一个元素。
*/

void test01()
{
    list<int> L1;
    L1.push_back(10);
    L1.push_back(20);
    L1.push_back(30);
    L1.push_back(40);

    // cout << L1.at(0) << endl; //错误 不支持at访问数据
    // cout << L1[0] << endl;    //错误  不支持[]方式访问数据
    //原因是list本质是链表,不使用连续线性空间存储数据,迭代器不支持随机访问
    cout << "第一个元素为： " << L1.front() << endl;
    cout << "最后一个元素为： " << L1.back() << endl;

    // list容器的迭代器是双向迭代器，不支持随机访问
    list<int>::iterator iter = L1.begin();
    // iter = iter + 1;//错误，不可以跳跃访问，即使是+1,因为重载+号有可能加2 加3 跳跃式访问
    // iter++; iter--; //正确 operator++()重载了
}

int main()
{
    test01();

    return 0;
}
