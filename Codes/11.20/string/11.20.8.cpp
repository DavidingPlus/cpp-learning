#include <iostream>
using namespace std;
#include <cstring>

//字符串比较

/*
int compare(const string &s) const; //与字符串s比较
int compare(const char *s) const;   //与字符串s比较
*/

void test01()
{
    string str1 = "hello";
    string str2 = "xello";

    if (str1.compare(str2) == 0)
        cout << "str1 == str2" << endl;
    else if (str1.compare(str2) > 0)
        cout << "str1 > str2" << endl;
    else
        cout << "str1 < str2" << endl;
}

int main()
{
    test01();

    return 0;
}
