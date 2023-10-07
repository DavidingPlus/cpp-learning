#include <iostream>
using namespace std;
#define SIZE 1e6
#include <list>
#include <string>

template <typename Type>
inline void output_static_data(const Type &obj)
{
    cout << "static_data: " << endl; // 输出静态成员
}

template <typename Container>
inline void test_moveable(Container c)
{
    typedef typename iterator_traits<typename Container::iterator>::value_type Value_Type;

    for (long i = 0; i < SIZE; ++i)
        c.insert(c.end(), Value_Type());

    output_static_data(*(c.begin()));
    Container c1(c);
    Container c2(std::move(c));
    c1.swap(c2);
}

int main()
{
    test_moveable(list<string>());

    return 0;
}