#pragma once
#include <iostream>
using namespace std;
#include <cstring>

//员工信息有: 姓名 工资组成;
class Employee
{
public:
    Employee(string name, int salary);

    string &get_Name();
    int &get_Salary();

private:
    string Name;
    int Salary;
};

// hpp中的文件都必须 类内声明 类外实现
Employee::Employee(string name, int salary)
{
    this->Name = name;
    this->Salary = salary;
}

string &Employee::get_Name()
{
    return this->Name;
}

int &Employee::get_Salary()
{
    return this->Salary;
}