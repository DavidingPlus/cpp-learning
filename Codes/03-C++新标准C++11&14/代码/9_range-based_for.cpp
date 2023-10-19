#include <iostream>
using namespace std;
#include <vector>
#include <string>

class C
{
public:
    explicit C(const string &s);
};

int main()
{
    vector<string> vs;
    // for (const C &elem : vs) // error 因为加了explicit关键字 无法隐式转换
    // {
    // }

    return 0;
}
