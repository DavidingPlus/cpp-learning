#include <iostream>
using namespace std;
#include <vector>

// type alias 和 typedef 没有任何的不同
namespace Test
{
    void test01(int, int)
    {
        cout << "test01" << endl;
    }

    template <typename T>
    struct Container
    {
        using Value_Type = T;
    };

    template <class CharT>
    using mystring = std::basic_string<CharT, std::char_traits<CharT>>;

    template <class Container>
    void fn2(const Container &con)
    {
        using Value_Type = typename iterator_traits<typename Container::iterator>::value_type;
        cout << "fn2" << endl;
    }
}

using namespace Test;
int main()
{
    // func现在指向参数如下的函数
    using func = void (*)(int, int);
    func f1 = test01;
    f1(1, 1);

    mystring<char> str;

    fn2(vector<int>());

    return 0;
}
