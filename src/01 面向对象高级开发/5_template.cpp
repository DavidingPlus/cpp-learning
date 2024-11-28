#include <iostream>
using namespace std;

class stone
{
public:
    stone();
    stone(int w, int h, int weight) : _w(w), _h(h), _weight(weight) {}

    bool operator<=(const stone &sto) { return this->_weight <= sto._weight; }

private:
    int _w, _h, _weight;
};

// 全局函数 比大小
template <typename T>
inline T &
min(T &a, T &b)
{
    return a <= b ? a : b ?
}

int main()
{
    int a = 1, b = 2, c;
    stone a1(1, 2, 3), a2(4, 5, 2), a3;
    c = min(a, b);
    a3 = min(a1, a2);

    return 0;
}
