#include <iostream>
using namespace std;

//���μ̳�

//������
class Animal
{
public:
    int m_age;
};

//������̳п��Խ�����μ̳е�����
//�ڼ̳�֮ǰ���Ϲؼ��� virtual ��Ϊ��̳�
// Animal���Ϊ �����

//����
class Sheep : virtual public Animal
{
};

//����
class Tuo : virtual public Animal
{
};

//������
class SheepTuo : public Sheep, public Tuo
{
};

void test01()
{
    SheepTuo st;

    st.Sheep::m_age = 18;
    st.Tuo::m_age = 28;
    //���������μ̳е�ʱ��,��������ӵ����ͬ����,��Ҫ��������������
    cout << "st.Sheep::m_age= " << st.Sheep::m_age << endl;
    cout << "st.Tuo::m_age= " << st.Tuo::m_age << endl;
    cout << "st.m_age= " << st.m_age << endl;

    //�����������֪����һ�ݾͿ�����,�������μ̳е�ʦ����������,��Դ�˷�!
}

int main()
{
    test01();

    return 0;
}