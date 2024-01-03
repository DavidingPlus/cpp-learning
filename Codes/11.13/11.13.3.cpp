#include <iostream>
using namespace std;

//实现通用对数组进行排序的函数
//规则 从大到小
//算法 选额
//测试 char数组 int数组

template <typename T>
void mySwap(T &a, decltype(a) &b)
{
    T temp = a;
    a = b;
    b = temp;
}

//排序算法
template <typename T>
void mySort(T arr[], int len)
{
    for (int i = 0; i < len; ++i)
    {
        int max = i; //认定最大值的下表
        for (int j = i + 1; j < len; ++j)
            if (arr[max] >= arr[j])
                max = j;
        if (max != i)
            mySwap(arr[max], arr[i]);
    }
}

template <typename T>
void printArray(T arr[], int len)
{

    for (int i = 0; i < len; i++)
    {
        cout << arr[i];
    }
    cout << endl;
}

void test01()
{
    //测试char数组
    char charArr[] = "badcfe";
    int num = sizeof(charArr) / sizeof(char) - 1; //减1是为了去掉后面的'\0'
    mySort(charArr, num);
    printArray(charArr, num);
}

void test02()
{
    //测试int数组
    int intArr[] = {7, 5, 8, 1, 3, 9, 2, 4, 6};
    int num = sizeof(intArr) / sizeof(int);
    mySort(intArr, num);
    printArray(intArr, num);
}

int main()
{
    test01();
    test02();

    return 0;
}
