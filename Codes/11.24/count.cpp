#include <iostream>
using namespace std;
#include <algorithm>
#include <vector>
#include <string>

// count(iterator beg, iterator end, value);
//  统计元素出现次数
//  beg 开始迭代器
//  end 结束迭代器
//  value 统计的元素

//常用查找算法 count

//统计内置数据类型
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

    int num = count(v.begin(), v.end(), 4);
    cout << "4的个数为: " << num << endl;
}

//统计自定义数据类型
class Person
{
public:
    Person(string name, int age) : Name(name), Age(age) {}
    bool operator==(const Person &p)
    //重载 == 号运算符 判断年龄是否相同
    {
        return this->Age == p.Age;
    }

    int Age;
    string Name;
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

    Person p("诸葛亮", 35);

    //统计与测试人年龄相同的人 需要根据实际情况重载 == 运算符
    int num = count(v.begin(), v.end(), p);
    cout << "和诸葛亮同岁数的人员个数为: " << num << endl;
}

int main()
{
    // test01();
    test02();

    return 0;
}
