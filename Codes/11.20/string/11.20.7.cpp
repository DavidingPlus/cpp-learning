
#include <iostream>
using namespace std;
#include <cstring>

//字符串的查找和替换

/*
int find(const string &str, int pos = 0) const;     //查找str第一次出现位置,从pos开始查找
int find(const char *s, int pos = 0) const;         //查找s第一次出现位置,从pos开始查找
int find(const char *s, int pos, int n) const;      //从pos位置查找s的前n个字符第一次位置
int find(const char c, int pos = 0) const;          //查找字符c第一次出现位置
int rfind(const string &str, int pos = npos) const; //查找str最后一次位置,从pos开始查找
int rfind(const char *s, int pos = npos) const;     //查找s最后一次出现位置,从pos开始查找
int rfind(const char *s, int pos, int n) const;     //从pos查找s的前n个字符最后一次位置
int rfind(const char c, int pos = 0) const;         //查找字符c最后一次出现位置
string &replace(int pos, int n, const string &str); //替换从pos开始n个字符为字符串str
string &replace(int pos, int n, const char *s);     //替换从pos开始的n个字符为字符串s
*/

// 1.查找
void test01()
{
    // find
    string str1 = "abcdefgde";

    int pos = str1.find("de"); // find函数未找到返回-1
    if (pos == -1)
        cout << "未找到字符串" << endl;
    else
        cout << "pos= " << pos << endl;

    // rfind和find区别
    // rfind从右往左查找 find从左往右查找!!!!
    pos = str1.rfind("de");
    if (pos == -1)
        cout << "未找到字符串" << endl;
    else
        cout << "pos= " << pos << endl;
}

// 2.替换
void test02()
{
    string str2 = "abcdefg";
    str2.replace(1, 3, "1111");
    // a1111efg
    //从1号位置起 3个字符 替换为"1111"
    cout << "str2= " << str2 << endl;
}

int main()
{
    // test01();
    test02();

    return 0;
}
