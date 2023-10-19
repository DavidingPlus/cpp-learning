#include <iostream>
using namespace std;
#include "2_print.h"
#include "2_hash.h"
#include <bitset>

class Stone
{
public:
    Stone();
    Stone(double len, double wid, double hei, double wei)
        : length(len), width(wid), height(hei), weight(wei) {}

public:
    double length;
    double width;
    double height;
    double weight;
};

int main()
{
    Print()("hello");
    // bitset可以把十进制数转化为二进制数，尖括号内表示要显示的位数，从后往前数起
    Print()("hello", 1, 3.14, bitset<16>(377));

    // 测试万用的hash函数
    Stone stone(1.2, 2.5, 3.6, 22.5);
    cout << GetHashCode().HashCode(stone.length, stone.width, stone.height, stone.weight) << endl;

    return 0;
}
