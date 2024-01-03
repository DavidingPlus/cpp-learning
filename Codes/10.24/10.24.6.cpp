#include <iostream>
using namespace std;

// 1.���캯���ķ��༰����
// ����
//  ���ղ������� �޲ι���(Ĭ�Ϲ���) �� �вι���
//  �������ͷ��� ��ͨ���캯�� �� �������캯��
class Person {
public:
    // ���캯��
    Person() {
        cout << "Person���޲ι��캯������" << endl;
    }

    Person(int a) {
        age = a;
        cout << "Person���вι��캯������" << endl;
    }

    // �������캯��
    Person(const Person &p)  // ���ܰѱ���ı���,�����ô���
    {
        // ������������ϵ���������,������������
        age = p.age;
        cout << "Person�Ŀ������캯������" << endl;
    }

    ~Person() {
        cout << "Person��������������" << endl;
    }

    int age;
};

// ����
void test01() {
    // 1.���ŷ�
    // Person p1;     //Ĭ�Ϲ��캯���ĵ���
    // Person p2(10); //�вι��캯���ĵ���
    // Person p3(p2); //�������캯���ĵ���

    // ע������
    // ����Ĭ�Ϲ��캯���͵�ʱ��,��Ҫ��()
    // ��Ϊ�������д���,����������Ϊ��һ������������,������Ϊ�ڴ�������
    //  Person p1();

    // cout << "p2������: " << p2.age << endl;
    // cout << "p3������: " << p3.age << endl;

    // 2.��ʾ��
    // Person p1;
    // Person p2 = Person(10); //�вι���
    // Person p3 = Person(p2); //��������

    // Person(10); //�������� �ص�:��ǰ�н�����,ϵͳ���������յ���������
    // cout << "aaaaa" << endl;

    // ע������2
    // ��Ҫ���ÿ������캯�� ����ʼ����������
    //  Person(p3); //����������Ϊ Person(p3) === Person p3; ���������

    // 3.��ʽת����
    Person p4 = 10;  // �൱�� Person p4 = Person(10); �вι���
    Person p5 = p4;  // ��������
}

int main() {
    test01();

    return 0;
}
