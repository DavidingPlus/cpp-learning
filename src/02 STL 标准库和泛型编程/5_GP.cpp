#include <iostream>
using namespace std;

namespace fuck
{
    template <typename Type>
    inline const Type &max(const Type &a, const Type &b)
    {
        return a < b ? b : a;
    }

    template <typename Type, class functor>
    inline const Type &max(const Type &a, const Type &b, functor &cmp)
    {
        return cmp(a, b) ? b : a;
    }

    template <typename Type>
    inline const Type &min(const Type &a, const Type &b)
    {
        return a < b ? a : b;
    }

    template <typename Type, class functor>
    inline const Type &min(const Type &a, const Type &b, functor &cmp)
    {
        return cmp(a, b) ? a : b;
    }

}

bool strCmp(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

void test()
{
    cout << "max of zoo and hello: " << fuck::max(string("zoo"), string("hello")) << endl;         // zoo
    cout << "max of zoo and hello: " << fuck::max(string("zoo"), string("hello"), strCmp) << endl; // hello
}

int main()
{
    test();
    return 0;
}
