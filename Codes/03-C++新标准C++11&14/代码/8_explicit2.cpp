#include <iostream>
using namespace std;
#include <initializer_list>

struct P {
    P(int a, int b) { cout << "P (int a , int b) " << endl; }
    // P(initializer_list<int>) { cout << "P (initializer_list<int>) " << endl; }
    explicit P(int a, int b, int c) { cout << "explicit P (int a , int b , int c) " << endl; }
};

int main() {
    P p1(77, 5);
    P p2{77, 5};
    P p3 = {77, 5};

    P p4{77, 5, 42};
    // 这个是可以的,因为它既可以看作传入了三个参数，也可以看作传入了初始化序列
    // 而如果像下面一样加上括号并且有 explicit 关键字就只能传入 三个参数的形式

    // P p5({77, 5, 42}); // 这个在有 explicit 关键字的情况下没有办法把 initializer_list 的形式转化为 a,b,c 的形式，会报错

    return 0;
}
