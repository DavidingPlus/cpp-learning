#include <iostream>
using namespace std;

//�����������ķ���ֵ
// 1.��Ҫ���ؾֲ�����������
int &test01()
{
    int a = 10; //�ֲ����� ����������е� ջ��
    return a;
}

// 2.�����ĵ��ÿ�����Ϊ��ֵ
int &test02()
{
    static int a = 10; //��̬����,�����ȫ����,ȫ�����ϵ������ڳ��������ϵͳ�Ż��ͷ�
    return a;
}

int main()
{
    // int &ref = test01();
    // cout << "ref= " << ref << endl; //��һ�ν����ȷ,����Ϊ���������˱���
    // cout << "ref= " << ref << endl; //�ڶ��ν������,��Ϊa���ڴ��Ѿ��ͷ�

    int &ref2 = test02();
    cout << "ref2= " << ref2 << endl;
    cout << "ref2= " << ref2 << endl;
    cout << "ref2= " << ref2 << endl;

    test02() = 1000; //��������ķ���ֵ������,��������ĵ��ÿ�����Ϊ��ֵ

    cout << "ref2= " << ref2 << endl;
    cout << "ref2= " << ref2 << endl;

    return 0;
}