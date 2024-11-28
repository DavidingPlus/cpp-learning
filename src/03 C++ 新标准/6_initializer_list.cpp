#include <iostream>
using namespace std;

// 这是 initializer_list 的源码
/*
template <class _E>
class initializer_list
{
public:
    typedef _E value_type;
    typedef const _E &reference;
    typedef const _E &const_reference;
    typedef size_t size_type;
    typedef const _E *iterator;
    typedef const _E *const_iterator;

private:
    iterator _M_array;
    size_type _M_len;

    // The compiler can call a private constructor.
    constexpr initializer_list(const_iterator __a, size_type __l)
        : _M_array(__a), _M_len(__l) {}

public:
    constexpr initializer_list() noexcept
        : _M_array(0), _M_len(0) {}

    // Number of elements.
    constexpr size_type
    size() const noexcept { return _M_len; }

    // First element.
    constexpr const_iterator
    begin() const noexcept { return _M_array; }

    // One past the last element.
    constexpr const_iterator
    end() const noexcept { return begin() + size(); }
};
*/

// 所谓 initializer_list<>,是标准库提供的一个模板，它的形式就是initializer_list<>类或者{}，大括号里面可以接受同类型任意个数的参数
template <typename Type>
inline void print(const initializer_list<Type> &vals)
{
    for (auto val : vals)
        cout << val << ' ';
    cout << endl;
}

class P
{
public:
    P(const int &a, const int &b) { cout << "P(int,int), a = " << a << " , b = " << b << endl; }

    P(const initializer_list<int> &initlist)
    {
        cout << "P(initializer_list<int>), values = ";
        for (auto val : initlist)
            cout << val << ' ';
        cout << endl;
    }
};

class Complex
{
public:
    double re;
    double im;

public:
    Complex() : re(0), im(0) {}
    Complex(double _re, double _im) : re(_re), im(_im) {}
};

int main()
{
    initializer_list<int> a{1, 2, 3, 4, 5, 6};
    print(a);
    print({12, 3, 5, 7, 6, 3, 21});

    P p(77, 5);
    P q{77, 5};     // 如果没有 initializer_list<> 的构造函数，编译器会把这一包参数进行拆开，这里就是拆成两个参数，刚好就可以调用第一个构造函数
    P r{77, 5, 42}; // 没有的话，拆成三个参数就没有办法吻合，就会报错
    P s = {77, 5};

    return 0;
}
