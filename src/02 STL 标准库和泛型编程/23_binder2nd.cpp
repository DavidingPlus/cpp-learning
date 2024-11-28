#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <functional>

// 不太好理解!!!
namespace fuck
{
    // 自己写一个bind2nd和binder2nd
    // 仔细敲打一下这段代码
    // 这里暗示了需要传入的是一个二元运算符 然后下面的类型名称是继承里面写好的类型名称
    template <class Binary_Op>
    class _BinderSecond
    // 不继承这一行也可以运作，但是没办法进行后续的改造
    // 这里就不继承了!!!
    // : public unary_function<typename Binary_Op::first_argument_type, typename Binary_Op::result_type>
    {
    protected:
        Binary_Op op;
        typename Binary_Op::second_argument_type value; // 第二参数 需要设定的固定值
    public:
        // ctor
        _BinderSecond(const Binary_Op &x, const typename Binary_Op::second_argument_type &y)
            : op(x), value(y) {}

        typename Binary_Op::result_type
        operator()(const typename Binary_Op::first_argument_type &x)
        {
            return op(x, value);
        }
    };

    template <class Binary_Op, class Value_Type>
    inline _BinderSecond<Binary_Op> _BindSecond(const Binary_Op &op, const Value_Type &val)
    {
        typedef typename Binary_Op::second_argument_type second_type;
        return _BinderSecond(op, second_type(val));
    };
}

int main()
{
    vector<int> v{1, 3, 2, 5, 9, 8, 7, 6, 4, 10};
    cout << count_if(v.begin(), v.end(),
                     fuck::_BindSecond(less<int>(), 5)) // 绑定第二参数
         << endl;

    return 0;
}
