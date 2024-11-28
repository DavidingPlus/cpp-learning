#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <bits/stl_numeric.h> //accumulate
#include <string>
#include <cmath>

struct Sum_Square
{
    template <class Value_Double>
    inline Value_Double &operator()(Value_Double &val, Value_Double val_iter)
    {
        val += pow(val_iter, 2.0);
        return val;
    }
};

struct String_Append
{
    template <class Value_String>
    inline Value_String &operator()(Value_String &val, Value_String val_iter)
    {
        val_iter.append(" ");
        val.append(val_iter);
        return val;
    }
};

struct Algorithm
{
    template <class Iterator, class Value_Type>
    inline static Value_Type Accumulate(Iterator begin, Iterator end, Value_Type val)
    {
        for (; begin != end; ++begin)
            val += *begin;
        return val;
    }

    template <class Iterator, class Value_Type, class Binary_Operation>
    inline static Value_Type Accumulate(Iterator begin, Iterator end, Value_Type val, Binary_Operation binary_op)
    {
        for (; begin != end; ++begin)
            val = binary_op(val, *begin);
        return val;
    }
};

int main()
{
    vector<double> v{5.5, 3.4, 6.3, 9.1, 10.8};
    cout << Algorithm::Accumulate(v.begin(), v.end(), double(0), Sum_Square()) << endl; // 280.95
    list<string> l{"hello", "I", "want", "to", "fuck", "you", "my", "friend."};
    cout << Algorithm::Accumulate(l.begin(), l.end(), string(), String_Append()) << endl;

    return 0;
}
