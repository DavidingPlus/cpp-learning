#include <iostream>
using namespace std;
#include <list>

// list容器构造函数
//  List有一个重要的性质，插入操作和删除操作都不会造成原有list迭代器的失效，这在vector是不成立的。
//  因为vector会开辟新的数据空间而导致原来的迭代器失效

/*
list<T> lst;           // list采用采用模板类实现,对象的默认构造形式：
list(beg, end);        //构造函数将[beg, end)区间中的元素拷贝给本身。
list(n, elem);         //构造函数将n个elem拷贝给本身。
list(const list &lst); //拷贝构造函数。
*/

void printList(const list<int> &l)
{
    for (list<int>::const_iterator iter = l.begin(); iter != l.end(); ++iter)
        //这里要用!= 因为 iter 是广义指针(迭代器) 这里本质上是链表 不能像线性一样写小于
        cout << *iter << ' ';
    cout << endl;
}

void test01()
{
    //创建list容器
    list<int> L1; //默认构造
    //添加数据
    L1.push_back(10);
    L1.push_back(20);
    L1.push_back(30);
    L1.push_back(40);

    //遍历容器
    printList(L1);

    //区间方式构造
    list<int> L2(L1.begin(), L1.end());
    printList(L2);

    //拷贝构造
    list<int> L3(L2);
    printList(L3);

    // n个elem构造
    list<int> L4(10, 1000);
    printList(L4);
}

int main()
{
    test01();

    return 0;
}
