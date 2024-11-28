#include <iostream>
using namespace std;
#include <algorithm>
#include <vector>

class LambdaFunctor {
public:
    LambdaFunctor(int x, int y)
        : _x(x), _y(y) {}

    bool operator()(int val) {
        return val > _x && val < _y;
    }

private:
    int _x;
    int _y;
};

template <typename Value_Type>
inline void printVector(const vector<Value_Type>& vec) {
    for (auto val : vec)
        cout << val << ' ';
    cout << endl;
}

int main() {
    int x = 30, y = 100;

    vector<int> v1{5, 28, 50, 83, 70, 590, 245, 59, 24};
    vector<int> v2{5, 28, 50, 83, 70, 590, 245, 59, 24};

    // 注意remove系列操作是假remove，需要erase才能真正删除
    auto newEnd1 = remove_if(v1.begin(), v1.end(), [x, y](int val) {
        return val > x && val < y;
    });
    v1.erase(newEnd1, v1.end());

    v2.erase(remove_if(v1.begin(), v1.end(), LambdaFunctor(x, y)), v2.end());

    printVector(v1);
    printVector(v2);

    return 0;
}
