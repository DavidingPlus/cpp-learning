#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    for_each()它可以返回其仿函数(返回所传入的函数对象的最终状态).
    这样我们就可以通过for_each()的返回值来获取仿函数的状态.
*/

/* 仿函数 */
class CSum
{
public:
    CSum() { m_sum = 0; }

    void operator()(int n) { m_sum += n; }

    int GetSum() const { return m_sum; }

private:
    int m_sum;
} cs;

int main()
{
    vector<int> vi;
    for (int i = 1; i <= 100; i++)
        vi.push_back(i);
    // 通过for_each返回值访问其最终状态(返回所传入的函数对象的最终状态).
    cs = for_each(vi.begin(), vi.end(), cs); // 返回的是一个新创建的对象，未返回引用，不会修改实参
    cout << cs.GetSum() << endl;

    return 0;
}
