#include <iostream>
using namespace std;

class C1 {
    int m_A;  // Ĭ��Ȩ�� �� ˽��
};

struct C2 {
    int m_A;  // Ĭ��Ȩ�� �� ����
};

int main() {
    // struct��class����
    // structĬ��Ȩ���� ���� public
    // class Ĭ��Ȩ���� ˽�� private
    C1 c1;  // ��classĬ��Ȩ��Ϊ˽��,��˲����Է���
    // c1.m_A = 100;

    C2 c2;
    c2.m_A = 100;  // ��structĬ�ϵ�Ȩ��Ϊ����,��˿��Է���

    return 0;
}