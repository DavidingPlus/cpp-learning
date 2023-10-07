#include <iostream>
using namespace std;

void f(int)
{
    cout << "call of int" << endl;
}

void f(void *)
{
    cout << "call of void*" << endl;
}

int main()
{
    f(0); // calls f(int)
    // f(NULL);    // 这里会报错，因为NULL既可以指是int 也可以是指针
    f(nullptr); // calls f(void*)

    return 0;
}
