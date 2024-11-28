#include <iostream>
using namespace std;
#include <queue>
#include <list>

int main()
{
    queue<int, vector<int>> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(5);
    q.push(6);
    q.push(7);
    cout << q.size() << endl;
    q.pop(); // 编译器会报错,因为vector没有pop_front()函数
    cout << q.size() << endl;

    return 0;
}
