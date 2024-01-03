#include <iostream>
using namespace std;
#include <algorithm>
#include <vector>
#include <string>

//  find(iterator beg, iterator end, value);
//  按值查找元素，找到返回指定位置迭代器，找不到返回结束迭代器位置
//  beg 开始迭代器
//  end 结束迭代器
//  value 查找的元素

//查找内置数据类型
void test01()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
        v.push_back(i);

    //查找容器中是否有5这个元素
    auto iter = find(v.begin(), v.end(), 5);
    if (iter == v.end())
        cout << "没有找到!" << endl;
    else
        cout << "找到: " << *iter << endl;
}

//查找自定义数据类型
class Person
{
public:
    Person(string name, int age) : Name(name), Age(age) {}

    bool operator==(const Person &p)
    {
        if (this->Age == p.Age && this->Name == p.Name)
            return true;
        else
            return false;
    }

    string Name;
    int Age;
};

//重载左移运算符
ostream &operator<<(ostream &cout, const Person &p)
{
    cout << "找到姓名:" << p.Name << " 年龄: " << p.Age << endl;
    return cout;
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

    Person p("bbb", 20);

    //查找
    vector<Person>::iterator iter = find(v.begin(), v.end(), p);
    if (iter == v.end())
        //当使用自定义类型的时候需要重载 == 号运算符!!! 因为解引用之后编译器不知道怎么判断是否相等
        cout << "没有找到!" << endl;
    else
        //复习 重载一下左移运算符!!!(注意是全局函数)
        cout << *iter;
}

int main()
{
    // test01();
    test02();

    return 0;
}
