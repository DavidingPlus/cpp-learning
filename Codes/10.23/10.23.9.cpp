#include <iostream>
using namespace std;

//Բ����
const double PI = 3.14;

// C++����������������:��װ,�̳�,��̬

//���һ��Բ��,��Բ���ܳ�
//Բ���ܳ��Ĺ�ʽ: 2*PI*�뾶

// class �������һ����,���������ŵľ���������
class Circle
{
    //����Ȩ��
    //����Ȩ��
public:
    //����
    //�뾶
    int m_r;

    //��Ϊ
    //��ȡԲ���ܳ�
    double calculateZC()
    {
        return 2 * PI * m_r;
    }
};

int main()
{
    //ͨ��Բ��������һ�������Բ(����)
    //ʵ���� (ͨ��һ���� ����һ������Ĺ���)
    Circle c1{10};
    //��Բ��������Խ��и�ֵ

    // 2 * PI * 10 = 62.8
    cout << "Բ���ܳ�Ϊ: " << c1.calculateZC() << endl;

    return 0;
}