#include <iostream>
using namespace std;

void process(int& i) {
    cout << "process(int&): " << i << endl;
}

void process(int&& i) {
    cout << "process(int&&): " << i << endl;
}

void forward(int&& i) {
    cout << "process(int&&): " << i << endl;
    process(i);
}

int main() {
    int a = 0;
    process(a);
    process(1);
    process(move(a));

    forward(2);  // process(int&):2
    // Rvalue经forward()传递之后变成了Lvalue

    // forward(a);  // 不能把int Lvalue绑定在Ravlue上

    const int& b = 1;
    // process(b);//没有 const int& 重载的例子
    // process(move(b));  //没有 process(remove_reference<const int&>::type) 重载的例子

    // int& x(5);//5不为左值

    return 0;
}
