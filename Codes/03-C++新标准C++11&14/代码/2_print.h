#ifndef __PRINT__
#define __PRINT__

using namespace std;
#include <iostream>
class Print
{
public:
    template <typename... Types, typename Type>
    inline void operator()(const Type &val, const Types &...args)
    {
        _print(val, args...);
    }

private:
    // 在写的时候注意写边界条件!!!!
    inline void _print() {}

    template <typename... Types, typename Type>
    inline void _print(const Type &val, const Types &...args)
    {
        cout << val << endl;
        _print(args...);
    }
};

#endif