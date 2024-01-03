#include <iostream>
using namespace std;
#include <list>
#include <algorithm>

// list容器的插入和删除

/*
push_back(elem);       //在容器尾部加入一个元素
pop_back();            //删除容器中最后一个元素
push_front(elem);      //在容器开头插入一个元素
pop_front();           //从容器开头移除第一个元素
insert(pos, elem);     //在pos位置插elem元素的拷贝，返回新数据的位置。
insert(pos, n, elem);  //在pos位置插入n个elem数据，无返回值。
insert(pos, beg, end); //在pos位置插入[beg,end)区间的数据，无返回值。
clear();               //移除容器的所有数据
erase(beg, end);       //删除[beg,end)区间的数据，返回下一个数据的位置。
erase(pos);            //删除pos位置的数据，返回下一个数据的位置。
remove(elem);          //删除容器中所有与elem值匹配的元素。
*/

void myprint(int num)
{
    cout << num << ' ';
}

void test01()
{
    list<int> L;
    //尾插
    L.push_back(10);
    L.push_back(20);
    L.push_back(30);
    //头插
    L.push_front(100);
    L.push_front(200);
    L.push_front(300);
    // 300 200 100 10 20 30
    for_each(L.begin(), L.end(), myprint);
    cout << endl;

    //尾删
    L.pop_back();
    // 300 200 100 10 20
    for_each(L.begin(), L.end(), myprint);
    cout << endl;
    //头删
    L.pop_front();
    // 200 100 10 20
    for_each(L.begin(), L.end(), myprint);
    cout << endl;

    // insert插入
    list<int>::iterator iter = L.begin();
    L.insert(++iter, 1000);
    // 200 1000 100 10 20
    for_each(L.begin(), L.end(), myprint);
    cout << endl;

    //删除
    iter = L.begin();
    L.erase(++iter);
    // 200 100 10 20
    for_each(L.begin(), L.end(), myprint);
    cout << endl;

    //移除
    L.push_back(10000);
    L.push_back(10000);
    L.push_back(10000);
    L.push_back(10000);
    // 200 100 10 20 10000
    for_each(L.begin(), L.end(), myprint);
    cout << endl;
    L.remove(10000); //直接把容器当中10000的元素全删掉
    // 200 100 10 20
    for_each(L.begin(), L.end(), myprint);
    cout << endl;

    //清空
    L.clear();
    for_each(L.begin(), L.end(), myprint);
    cout << endl;
}

int main()
{
    test01();

    return 0;
}
