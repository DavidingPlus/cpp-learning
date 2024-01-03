#include <iostream>
using namespace std;
#include <vector>

// vector容器 预留空间

// reserve(int len);//容器预留len个元素长度，预留位置不初始化，元素不可访问.

void test01()
{
    vector<int> v;

    //利用reserve预留空间
    v.reserve(100000);
    int num = 0; //统计开辟次数
    int *p = nullptr;
    for (auto i = 0; i < 100000; ++i)
    {
        v.push_back(i);
        //地址变化则表示开辟了新的空间
        if (p != &v[0])
        {
            p = &v[0];
            ++num;
        }
    }
    cout << "num = " << num << endl;
}

int main()
{
    test01();

    return 0;
}
