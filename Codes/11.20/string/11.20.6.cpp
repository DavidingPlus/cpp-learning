#include <iostream>
using namespace std;
#include <string.h>

// string�ַ���ƴ��

/*
string &operator+=(const char *str);             //����+=������
string &operator+=(const char c);                //����+=������
string &operator+=(const string &str);           //����+=������
string &append(const char *s);                   //���ַ���s���ӵ���ǰ�ַ�����β
string &append(const char *s, int n);            //���ַ���s��ǰn���ַ����ӵ���ǰ�ַ�����β
string &append(const string &s);                 //ͬoperator+=(const string& str)
string &append(const string &s, int pos, int n); //�ַ���s�д�pos��ʼ��n���ַ����ӵ��ַ�����β
*/

void test01()
{
    string str1 = "我";
    str1 += "爱玩游戏";
    str1 += ':';
    string str2 = "LOL DNF";
    str1 += str2;
    cout << "str1= " << str1 << endl;

    string str3 = "I";
    str3.append(" love ");
    str3.append("game abcde", 5);
    // str3.append(str2);
    // str3.append(str2, 0, 3); //只截取到LOL
    str3.append(str2, 4, 3); //只截取到DNF 参数2:从哪个位置开始截取; 参数3:截取字符个数
    cout << "str3= " << str3 << endl;
}

int main()
{
    test01();

    return 0;
}
