#include <iostream>
using namespace std;
#include <vector>

// vector容器的容量和大小操作

/*
empty();                   //判断容器是否为空
capacity();                //容器的容量
size();                    //返回容器中元素的个数
resize(int num);           //重新指定容器的长度为num，若容器变长，则以默认值填充新位置。
​                           //如果容器变短，则末尾超出容器长度的元素被删除。
resize(int num, elem);     //重新指定容器的长度为num，若容器变长，则以elem值填充新位置。
​                           //如果容器变短，则末尾超出容器长度的元素被删除
*/

void printVector(vector<int> &v)
{
    //这里的 auto 是指 vector<int>::iterator
    for (auto iter = v.begin(); iter < v.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;
}

void test01()
{
    vector<int> v1;
    for (auto i = 0; i < 10; ++i)
        v1.push_back(i);
    printVector(v1);

    //判断容器是否为空
    if (v1.empty()) //为真 代表容器为空
        cout << "v1为空" << endl;
    else
    {
        cout << "v1不为空" << endl;
        cout << "v1的容量为: " << v1.capacity() << endl;
        cout << "v1的大小为: " << v1.size() << endl;
        //容量大于等于大小
    }

    //重新指定大小
    v1.resize(15);
    printVector(v1);    //如果重新指定的过长比原来长,默认用 0 填充新的位置
    v1.resize(20, 100); //利用重载的版本可以指定默认的填充值
    printVector(v1);

    v1.resize(5); //如果重新指定的比原来短了,超出部分会被删掉
    printVector(v1);
}

int main()
{
    test01();

    return 0;
}
