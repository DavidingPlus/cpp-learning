#include <iostream>
using namespace std;
#include <list>

int main()
{
    list<int> foo, bar;
    for (int i = 1; i <= 5; ++i)
    {
        foo.push_back(i);
        bar.push_back(i * 10);
    }

    auto iter = foo.begin();
    advance(iter, 3);
    copy(bar.begin(), bar.end(), inserter(foo, iter));
    for (auto val : foo)
        cout << val << ' ';
    cout << endl;

    return 0;
}
