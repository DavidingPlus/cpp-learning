#include <iostream>
using namespace std;
#include <array>
#include <vector>
#include <map>
#include <list>
#include <forward_list>
#include <deque>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <bits/stream_iterator.h>

// 可以只指定值不给参数
void __display_category(random_access_iterator_tag)
{
    cout << "random_access_iterator" << endl;
}
void __display_category(bidirectional_iterator_tag)
{
    cout << "bidirectional_iterator" << endl;
}
void __display_category(forward_iterator_tag)
{
    cout << "forward_iterator" << endl;
}
void __display_category(input_iterator_tag)
{
    cout << "input_iterator" << endl;
}
void __display_category(output_iterator_tag)
{
    cout << "output_iterator" << endl;
}

#include <typeinfo>
template <typename I>
void display_category(I iter)
{
    // 加上typename是为了是 I 就是迭代器类型(目前这么理解)
    typename iterator_traits<I>::iterator_category Iterator_Category; // 去问萃取剂这个迭代器是什么类型
    __display_category(Iterator_Category);

    cout << "typeid(itr).name()= " << typeid(iter).name() << endl
         << endl;
}

int main()
{
    display_category(array<int, 10>::iterator());
    display_category(vector<int>::iterator());
    display_category(list<int>::iterator());
    display_category(forward_list<int>::iterator());
    display_category(deque<int>::iterator());

    display_category(set<int>::iterator());
    display_category(map<int, int>::iterator());
    display_category(multiset<int>::iterator());
    display_category(multimap<int, int>::iterator());
    display_category(unordered_set<int>::iterator());
    display_category(unordered_map<int, int>::iterator());
    display_category(unordered_multiset<int>::iterator());
    display_category(unordered_multimap<int, int>::iterator());

    // 这两个不太一样，是从适配器adapter产生的
    display_category(istream_iterator<int>());
    display_category(ostream_iterator<int>(cout, ""));

    return 0;
}
