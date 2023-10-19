#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include "17_Advance.h"

int main()
{
    vector<int> v{3, 5, 6, 7};
    cout << *myadvance().Advance(v.begin() + 2, -1) << endl; // 5
    list<int> l{3, 5, 6, 7, 12};
    cout << *myadvance().Advance(l.begin(), 4) << endl; // 12

    return 0;
}
