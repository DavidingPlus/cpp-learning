#include <iostream>
using namespace std;
#include <map>

/*
size();   //返回容器中元素的数目
empty();  //判断容器是否为空
swap(st); //交换两个集合容器
*/

using Key = int;
using Value = int;

//大小
void test01()
{
    map<Key, Value> m;
    m.insert(pair<Key, Value>(1, 10));
    m.insert(pair<Key, Value>(2, 20));
    m.insert(pair<Key, Value>(3, 30));

    if (m.empty())
        cout << "m为空" << endl;
    else
    {
        cout << "m不为空" << endl;
        cout << "m的大小为: " << m.size() << endl;
    }
}

//交换
void printMap(const map<Key, Value> &m)
{
    for (auto iter = m.begin(); iter != m.end(); ++iter)
        cout << "key = " << iter->first << " value = " << iter->second << endl;
    cout << endl;
}

void test02()
{
    map<int, int> m;
    m.insert(pair<Key, Value>(1, 10));
    m.insert(pair<Key, Value>(2, 20));
    m.insert(pair<Key, Value>(3, 30));

    map<int, int> m2;
    m2.insert(pair<Key, Value>(4, 100));
    m2.insert(pair<Key, Value>(5, 200));
    m2.insert(pair<Key, Value>(6, 300));

    cout << "交换前: " << endl;
    printMap(m);
    printMap(m2);

    cout << "交换后: " << endl;
    m2.swap(m);
    printMap(m);
    printMap(m2);
}

int main()
{
    // test01();
    test02();

    return 0;
}
