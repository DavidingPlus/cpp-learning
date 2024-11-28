#include <iostream>
using namespace std;

namespace Test
{
    // noexcept保证了在满足括号内的条件的时候不会抛出异常，这里就是 true 也就是永远不会抛出异常
    void foo() noexcept(true) { cout << "foo" << endl; }

    template <typename Value_Type>
    void swap(Value_Type &x, Value_Type &y) noexcept(noexcept(x.swap(y)))
    {
        x.swap(y);
    }

    class MyString
    {
    public:
        // move ctor
        MyString(MyString &&str) noexcept
            : _data(str._data), _len(str._len)
        {
            // TODO
            // Move操作
        }

        // move assignment
        MyString &operator=(MyString &&str) noexcept
        {
            // TODO
            // Move操作
            return *this;
        }

    private:
        char *_data;
        size_t _len;
    };
}

using namespace Test;
int main()
{
    foo();

    return 0;
}
