#include <iostream>
using namespace std;
#include <complex>
#include <string>

// string测试
namespace testString {

void test() {
    string s1("hello");
    string s2("world");
    s1 + s2 = s2;        // 竟然可以用过编译
    cout << s1 << endl   // hello
         << s2 << endl;  // world

    string() = "world";  // 竟然可以对临时对象赋值
}

}  // namespace testString

namespace testComplex {

void test() {
    complex<int> c1(3, 8), c2(1, 0);
    c1 + c2 = complex<int>(4, 9);
    cout << "c1: " << c1 << endl;  //(3,8)
    cout << "c2: " << c2 << endl;  //(1,0)
    complex<int>() = complex<int>(4, 9);
}

}  // namespace testComplex

int main() {
    testString::test();
    testComplex::test();

    return 0;
}
