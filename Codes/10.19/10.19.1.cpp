#include <iostream>
using namespace std;

// 1.���ñ���Ҫ��ʼ��(int&b �����)
// 2.����һ����ʼ����,�Ͳ����Ը�����

int main()
{
    int a = 10;
    int b = 20;
    // int &c; //�������ñ����ʼ��
    int &c = a; //һ����ʼ���󣬾Ͳ����Ը���
    c = b;      //���Ǹ�ֵ���������Ǹ�������

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;

    system("pause");

    return 0;
}