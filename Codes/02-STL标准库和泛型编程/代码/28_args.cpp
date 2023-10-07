#include <iostream>
using namespace std;
#include <string>

class StringPrint
{
public:
    inline void myprint(const string &str)
    {
        _myprint(str);
        cout << endl;
    }

    template <typename... Types>
    inline void myprint(const string &str, const Types &...args)
    {
        _myprint(str, args...);
        cout << endl;
    }

    template <typename... Types>
    void foo(const Types &...args)
    {
        // 当我们想要知道包中有多少元素时，可以使用sizeof...运算符，该运算符返回一个常量表达式，并且不会对其实参求值
        cout << sizeof...(Types) << endl; // 类型参数数目
        cout << sizeof...(args) << endl;  // 函数参数数目
    }

private:
    inline void _myprint(const string &str)
    {
        cout << str;
    }

    // 接受参数包，参数包是占位符的替换
    template <typename Type, typename... Types>
    inline void _myprint(const string &str, const Type &val, const Types &...args)
    {
        // 一个字符一个字符的读，直到碰到占位符 %
        for (auto iter = str.begin(); iter != str.end(); ++iter)
        {
            if (*iter != '%')
                cout << *iter;
            else
            {
                // 是占位符
                cout << val;
                string newstr = string(++iter, str.end());
                _myprint(newstr, args...);
                return;
            }
        }
    }
} myPrint;

int main()
{
    myPrint.myprint("Hello , I'm % , % years old.", "David", 20);
    myPrint.foo("Hello , I'm % , % years old.", "David", 20);
    myPrint.myprint("fuck you!");
    myPrint.foo("fuck you!");

    return 0;
}
