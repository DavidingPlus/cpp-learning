#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

namespace fuck
{
    // 对谓词做否定
    template <class Predicate>
    class _unary_negate
        // 继承为了后续的改造
        : public unary_function<typename Predicate::argument_type, bool>
    {
    protected:
        Predicate pred;

    public:
        // ctor
        _unary_negate(const Predicate &x) : pred(x) {}
        
        bool operator()(const typename Predicate::argument_type &x) const
        {
            return !pred(x);
        }
    };

    template <class Predicate>
    inline _unary_negate<Predicate> _Not1(const Predicate &pred)
    {
        return _unary_negate<Predicate>(pred);
    }
}

int main()
{
    vector<int> v{1, 3, 2, 5, 9, 8, 7, 6, 4, 10};
    cout << count_if(v.begin(), v.end(),
                     fuck::_Not1(bind2nd(less<int>(), 5))) // 绑定第二参数
         << endl;

    return 0;
}
