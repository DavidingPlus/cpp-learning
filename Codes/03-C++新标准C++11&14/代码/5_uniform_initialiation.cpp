#include <iostream>
using namespace std;
#include <complex>
#include <vector>

template <typename Container>
inline void print(const Container &con) {
    for (auto val : con) cout << val << ' ';
    cout << endl;
}

int main() {
    vector<int> v{1, 2, 3};
    vector<string> cities{"Berlin", "New York", "London"};
    print(v);
    print(cities);

    // int i;//i has undefined value
    int j{};  // j is initialized by 0
    // int *p;//p has undefined value
    int *q{};  // q is initialized by nullptr
    cout << "j = " << j << " q = " << q << endl;

    // int x1 = {5.0};//不能这么转化
    // 把double转化为int，由于double类型的数字包含int的数字，这么转化相当于窄化了，narrowing
    // conversion error cout << x1 << endl;
    double x2 = {5.1};
    cout << x2 << endl;

    return 0;
}
