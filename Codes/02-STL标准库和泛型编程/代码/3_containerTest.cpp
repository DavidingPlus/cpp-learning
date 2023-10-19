#include <iostream>
using namespace std;
#include <vector>
#include <array>
#include <algorithm>
#include <ctime>
#include <list>
#include <forward_list>
#include <deque>
#define SIZE 1000000

// array
namespace fuck1
{
    void test()
    {
        srand(time(NULL));

        const size_t _size = 1000000;
        array<int, _size> arr;

        for (int i = 0; i < _size; ++i)
            // 随机数 0-100
            arr[i] = rand() % 101;
        // 打印一些信息
        cout << "arr.size()= " << arr.size() << endl;
        cout << "arr.front()= " << arr.front() << endl;
        cout << "arr.back()= " << arr.back() << endl;
        cout << "arr.data()= " << arr.data() << endl;
        cout << "&arr[0]= " << &arr[0] << endl;
    }
}

// vector
namespace fuck2
{
    void test(int length)
    {
        srand(time(NULL));

        vector<int> v;
        for (int i = 0; i < length; ++i)
            v.push_back(rand() % 101);
        // 打印
        cout << "v.size()= " << v.size() << endl;
        cout << "v.max_size()= " << v.max_size() << endl;
        cout << "v.front()= " << v.front() << endl;
        cout << "v.back()= " << v.back() << endl;
        cout << "v.data()= " << v.data() << endl;
        cout << "&v[0]=" << &v[0] << endl;
        cout << "v.capacity()= " << v.capacity() << endl;
    }
}

// list
namespace fuck3
{
    void test(int length)
    {
        srand(time(NULL));

        list<int> l;
        for (int i = 0; i < length; ++i)
            l.push_back(rand() % 101);
        cout << "l.size()= " << l.size() << endl;
        cout << "l.max_size()= " << l.max_size() << endl;
        cout << "l.front()= " << l.front() << endl;
        cout << "l.front()= " << *l.begin() << endl;
        cout << "l.front()= " << *(++l.end()) << endl;

        cout << "l.back()= " << l.back() << endl;
        cout << "l.back()= " << *(--l.end()) << endl;
        auto iter = --l.begin();
        cout << "l.back()= " << *(--iter) << endl;
    }
}

// forward_list(c++11)
// #include <ext\slist>
namespace fuck4
{
    void test(int length)
    {
        srand(time(NULL));

        forward_list<int> fl;
        for (int i = 0; i < length; ++i)
            fl.push_front(rand() % 101); // 只提供头插法,因为尾插法太慢了
        cout << "fl.max_size()= " << fl.max_size() << endl;
        cout << "fl.front()= " << fl.front() << endl;
        cout << "fl.front()= " << *(fl.begin()) << endl;
        // cout << "fl.back()= " << *(--fl.end()) << endl; // 没有重载 -- 运算符 只重载++运算符
    }
}

// deque
namespace fuck5
{
    void test(int length)
    {
        srand(time(NULL));
        deque<int> d;
        for (int i = 0; i < length; ++i)
            d.push_back(rand() % 101);
        cout << "d.size()= " << d.size() << endl;
        cout << "d.max_size()= " << d.max_size() << endl;
        cout << "d.front()= " << d.front() << endl;
        cout << "d.back()= " << d.back() << endl;
    }
}

// multiset
#include <set>
namespace fuck6
{
    void test(int length)
    {
        srand(time(NULL));
        set<int> s;
        for (int i = 0; i < length; ++i)
            s.insert(rand());
        cout << "s.size()= " << s.size() << endl;
        cout << "s.max_size()= " << s.max_size() << endl;
        // s.begin() s.end()存在
    }
}

// multimap
#include <map>
namespace fuck7
{
    void test(int length)
    {
        srand(time(NULL));
        map<int, int> m;
        for (int i = 0; i < length; ++i)
            m.insert(pair<int, int>(i, rand()));

        cout << "m.size()= " << m.size() << endl;
        cout << "m.max_size()= " << m.max_size() << endl;
        // m.begin() m.end() 存在
    }
}

// unordered_set
#include <unordered_set>
namespace fuck8
{
    void test(int length)
    {
        srand(time(NULL));
        unordered_set<int> us;
        for (int i = 0; i < length; ++i)
            us.insert(rand());

        cout << "us.size()= " << us.size() << endl;
        cout << "us.max_size()= " << us.max_size() << endl;
        cout << "us.bucket_count()= " << us.bucket_count() << endl;
        cout << "us.load_factor()= " << us.load_factor() << endl;
        cout << "us.max_load_factor()= " << us.max_load_factor() << endl;
        cout << "us.max_bucket_count()= " << us.max_bucket_count() << endl;
    }
}

int main()
{
    // fuck1::test();
    // fuck2::test(SIZE);
    // fuck3::test(SIZE);
    // fuck4::test(SIZE);
    // fuck5::test(SIZE);
    // fuck6::test(SIZE);
    // fuck7::test(SIZE);
    fuck8::test(SIZE);

    return 0;
}
