#include <iostream>
using namespace std;
#include <vector>
#include <ctime>
#include <algorithm>

// random_shuffle(iterator beg, iterator end);
//  指定范围内的元素随机调整次序
//  beg 开始迭代器
//  end 结束迭代器

//常用排序算法 random_shuffle
void myPrint(const int val)
{
    cout << val << ' ';
}

void test01()
{
    //按照时间生成一个随机数种子 每次执行结果不相同
    srand((unsigned int)time(NULL));

    vector<int> v;
    for (int i = 0; i < 10; i++)
        v.push_back(i);
    //利用洗牌算法打乱顺序
    random_shuffle(v.begin(), v.end());

    //打印输出
    for_each(v.begin(), v.end(), myPrint);
    cout << endl;
}

int main()
{
    test01();

    return 0;
}
