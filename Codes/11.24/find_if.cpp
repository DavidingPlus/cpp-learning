#include <string>
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

// find_if(iterator beg, iterator end, _Pred);
//  按值查找元素，找到返回指定位置迭代器，找不到返回结束迭代器位置
//  beg 开始迭代器
//  end 结束迭代器
//  _Pred 函数或者谓词（返回bool类型的仿函数）

//常用查找算法 find_if

// 1.查找内置数据
class GreaterFive
{
public:
    bool operator()(const int val) const { return val > 5; }
};

void test01()
{
    vector<int> v;
    for (int i = 0; i < 10; ++i)
        v.push_back(i);
    //查找大于5的数
    auto iter = find_if(v.begin(), v.end(), GreaterFive());
    //这个小括号里面不需要给参数,因为这个谓词的参数是由遍历的迭代器给出的!!!
    if (iter == v.end())
        cout << "没有找到" << endl;
    else
        cout << "找到大于5的数字为: " << *iter << endl;
}
// 2.查找自定义数据类型
class Person
{
public:
    Person(string name, int age) : Name(name), Age(age) {}

    string Name;
    int Age;
};

class Greater20
{
public:
    bool operator()(const Person &p)
    {
        return p.Age > 20;
    }
};

//重载左移运算符
ostream &operator<<(ostream &out, const Person &p)
{
    cout << "找到姓名:" << p.Name << " 年龄: " << p.Age << endl;
    return out;
}

void test02()
{
    vector<Person> v;

    //创建数据
    Person p1("aaa", 10);
    Person p2("bbb", 20);
    Person p3("ccc", 30);
    Person p4("ddd", 40);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    //找到年龄大于20的人
    vector<Person>::iterator iter = find_if(v.begin(), v.end(), Greater20());
    if (iter == v.end())
        cout << "未找到" << endl;
    else
        cout << *iter;
}

int main()
{
    // test01();
    test02();

    return 0;
}
