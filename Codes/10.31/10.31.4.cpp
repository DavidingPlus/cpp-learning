#include <iostream>
using namespace std;

//��ͨʵ��

// Javaҳ��
// class Java
// {
// public:
//     void header()
//     {
//         cout << "��ҳ,������,��¼,ע�ᡭ��(����ͷ��)" << endl;
//     }

//     void footer()
//     {
//         cout << "��������,��������,վ�ڵ�ͼ����(�����ײ�)" << endl;
//     }

//     void left()
//     {
//         cout << "Java,Python,C++����(���������б�)" << endl;
//     }

//     void content()
//     {
//         cout << "Javaѧ����Ƶ" << endl;
//     }
// };

// // Pythonҳ��
// class Python
// {
// public:
//     void header()
//     {
//         cout << "��ҳ,������,��¼,ע�ᡭ��(����ͷ��)" << endl;
//     }

//     void footer()
//     {
//         cout << "��������,��������,վ�ڵ�ͼ����(�����ײ�)" << endl;
//     }

//     void left()
//     {
//         cout << "Java,Python,C++����(���������б�)" << endl;
//     }

//     void content()
//     {
//         cout << "Pythonѧ����Ƶ" << endl;
//     }
// };

// // C++ҳ��
// class CPP
// {
// public:
//     void header()
//     {
//         cout << "��ҳ,������,��¼,ע�ᡭ��(����ͷ��)" << endl;
//     }

//     void footer()
//     {
//         cout << "��������,��������,վ�ڵ�ͼ����(�����ײ�)" << endl;
//     }

//     void left()
//     {
//         cout << "Java,Python,C++����(���������б�)" << endl;
//     }

//     void content()
//     {
//         cout << "C++ѧ����Ƶ" << endl;
//     }
// };

//�̳�ʵ��ҳ��
//����ҳ����
class BasePage
{
public:
    void header()
    {
        cout << "��ҳ,������,��¼,ע�ᡭ��(����ͷ��)" << endl;
    }

    void footer()
    {
        cout << "��������,��������,վ�ڵ�ͼ����(�����ײ�)" << endl;
    }

    void left()
    {
        cout << "Java,Python,C++����(���������б�)" << endl;
    }
};

// �̳еĺô�:�����ظ�����!!!
// �﷨: class ���� : �̳з�ʽ ����
// ���� Ҳ��Ϊ ������
// ���� Ҳ��Ϊ ����

// Javaҳ��
class Java : public BasePage
{
public:
    void content()
    {
        cout << "Javaѧ����Ƶ" << endl;
    }
};

// Pythonҳ��
class Python : public BasePage
{
public:
    void content()
    {
        cout << "Pythonѧ����Ƶ" << endl;
    }
};

// C++ҳ��
class CPP : public BasePage
{
public:
    void content()
    {
        cout << "C++ѧ����Ƶ" << endl;
    }
};

void test01()
{
    cout << "Java������Ƶҳ������: " << endl;
    Java ja;
    ja.header();
    ja.footer();
    ja.left();
    ja.content();

    cout << "-------------------" << endl;

    cout << "Python������Ƶҳ������: " << endl;
    Python py;
    py.header();
    py.footer();
    py.left();
    py.content();

    cout << "-------------------" << endl;

    cout << "C++������Ƶҳ������: " << endl;
    CPP cpp;
    cpp.header();
    cpp.footer();
    cpp.left();
    cpp.content();
}

int main()
{
    test01();

    return 0;
}