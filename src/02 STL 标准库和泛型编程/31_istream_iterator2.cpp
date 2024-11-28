#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

int main() {
    vector<int> v;

    istream_iterator<int> iter(cin), eos;
    copy(iter, eos, inserter(v, v.begin()));

    return 0;
}
