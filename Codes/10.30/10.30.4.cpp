#include <iostream>
#include <string.h>
using namespace std;

//������Ԫ
class Building;

class GoodGay
{
public:
    GoodGay();

    void visit(); //�ιۺ��� ����Building�е�����

    Building *building;
};

class Building
{
    // GoodGay���Ǳ���ĺ�����,���Է��ʱ����е�˽�г�Ա
    friend class GoodGay;

public:
    Building();

    string m_SittingRoom; //����
private:
    string m_BedRoom; //����
};

//����д��Ա����
Building::Building()
{
    m_SittingRoom = "����";
    m_BedRoom = "����";
}

GoodGay::GoodGay()
{
    //�������������
    building = new Building;
}

void GoodGay::visit()
{
    cout << "�û��������ڷ���: " << building->m_SittingRoom << endl;
    cout << "�û��������ڷ���: " << building->m_BedRoom << endl;
}

void test01()
{
    GoodGay gg;
    gg.visit();
}

int main()
{
    test01();

    return 0;
}