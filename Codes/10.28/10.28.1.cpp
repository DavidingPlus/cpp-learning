#include <iostream>
using namespace std;

//��Ա���� �� ��Ա���� �Ƿֿ��洢��
class Person
{
    int m_A; //�Ǿ�̬��Ա���� ������Ķ�����

    static int m_B; //��̬��Ա���� ��������Ķ�����

    void func() {} //�Ǿ�̬��Ա���� ��������Ķ�����

    static void func2() {} //��̬��Ա���� ��������Ķ�����
};

int Person::m_B = 0;

void test01()
{
    Person p;
    //�ն���ռ���ڴ�ռ�Ϊ: 1
    // c++���������ÿ���ն���Ҳ����һ���ֽڿռ�,��Ϊ�����ֿն���ռ�ڴ��λ��
    //ÿ���ն���ҲӦ����һ����һ�޶����ڴ��ַ
    cout << "size of p = " << sizeof(p) << endl;
}

void test02()
{
    Person p;
    cout << "size of p = " << sizeof(p) << endl;
}

int main()
{
    // test01();
    test02();

    return 0;
}