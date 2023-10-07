#include <iostream>
using namespace std;
#include <string>
#include <ostream>

class Stu
{
public:
    // 类内的函数会默认为内置inline函数
    Stu();
    Stu(int id, string name) : _ID(id), _name(name) {}

    int getID() { return this->_ID; }
    string getName() { return this->_name; }

private:
    int _ID;
    string _name;
};

inline ostream &
operator<<(ostream &os, Stu &s)
{
    os << s.getID() << ' ' << s.getName() << endl;
    // return cout;
}

int main()
{
    Stu s(1, "张三");
    cout << s;

    return 0;
}
