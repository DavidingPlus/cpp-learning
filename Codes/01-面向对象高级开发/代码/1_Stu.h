#ifndef __STU__
#define __STU__

#include <string>
using namespace std;
class Stu
{
public:
    static Stu &getInstance() { return s; }
    void setup()
    {
        ; // 一系列的接口操作
    }

private:
    Stu();
    Stu(int id, string name);
    int _ID;
    string _name;

    static Stu s;
};

class Stu2
{
public:
    static Stu2 &getInstance();
    void setup()
    {
        ; // 一系列的接口操作
    }

private:
    Stu2();
    Stu2(int id, string name);
    int _ID;
    string _name;
};

Stu2 &Stu2::getInstance()
{
    static Stu2 s;
    return s;
}

#endif