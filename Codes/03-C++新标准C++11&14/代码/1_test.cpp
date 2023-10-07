#include <iostream>
using namespace std;

int main()
{
    // 检测 __cplusplus关键字查看是不是符合c++2.0新标准
    cout << __cplusplus << endl; // 201703
    return 0;
}
