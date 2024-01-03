
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <string>

// count_if(iterator beg, iterator end, _Pred);
//  按条件统计元素出现次数
//  beg 开始迭代器
//  end 结束迭代器
//  _Pred 谓词

//内置数据类型
class Greater4
{
public:
    bool operator()(const int val) const { return val > 4; }
};

void test01()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(4);
    v.push_back(5);
    v.push_back(3);
    v.push_back(4);
    v.push_back(4);

    int num = count_if(v.begin(), v.end(), Greater4());

    cout << "大于4的个数为: " << num << endl;
}

//自定义数据类型
class Person
{
public:
    Person(string name, int age) : Name(name), Age(age) {}

    //也可以将谓词(仿函数 函数对象)在Person类中重载
    bool operator()(const Person &p) const
    {
        return p.Age < 35;
    }

    //注意这里需要将默认构造函数进行空实现,因为不写的话编译器无法判断是构造函数还是重载运算符(匿名对象),需要空实现写出来!!!
    Person() {}

    string Name;
    int Age;
};

class AgeLess35
{
public:
    bool operator()(const Person &p) const { return p.Age < 35; }
};

void test02()
{
    vector<Person> v;

    Person p1("刘备", 35);
    Person p2("关羽", 35);
    Person p3("张飞", 35);
    Person p4("赵云", 30);
    Person p5("曹操", 25);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    v.push_back(p5);

    //统计年龄小于35的人的个数
    // int num = count_if(v.begin(), v.end(), AgeLess35());
    int num = count_if(v.begin(), v.end(), Person());
    cout << "年龄小于35的人个数为: " << num << endl;
}

int main()
{
    // test01();
    test02();

    return 0;
}
