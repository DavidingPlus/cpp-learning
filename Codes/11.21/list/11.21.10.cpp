#include <iostream>
using namespace std;
#include <list>
#include <algorithm>

// list容器的反转和排序

/*
reverse(); //反转链表 vector 容器中 reserve 预留
sort();    //链表排序
*/

void printList(const list<int> &L)
{
    for (list<int>::const_iterator iter = L.begin(); iter != L.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;
}

bool myCompare(int val1, int val2)
{
    //降序 就让第一个数 > 第二个数
    return val1 - val2;
}

void test01()
{
    //反转
    list<int> L;
    L.push_back(20);
    L.push_back(10);
    L.push_back(50);
    L.push_back(40);
    L.push_back(30);
    cout << "反转前: " << endl;
    printList(L);

    //反转
    L.reverse();
    cout << "反转后: " << endl;
    printList(L);

    //所有不支持随机访问迭代器的容器不可以用标准算法!!!!
    //不支持随机访问迭代器的容器,内部会提供一些算法!!!
    // sort(L.begin(), L.end());

    //排序
    L.sort(); //默认排序规则: 从小到大 升序
    cout << "升序: " << endl;
    printList(L);

    //降序的方法,提供一个回调函数
    L.sort(myCompare);
    cout << "降序: " << endl;
    printList(L);
}

int main()
{
    test01();

    return 0;
}
