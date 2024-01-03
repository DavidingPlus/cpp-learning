//普通员工文件
#pragma once
#include <iostream>
using namespace std;
#include "worker.h"

class Employee : public Worker
{
public:
    //构造函数
    Employee(int id, string name, int dId);
    //显示个人信息
    void showInfo();
    //获取岗位名称
    string getDeptName();
};

Employee::Employee(int id, string name, int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = dId;
}

void Employee::showInfo()
{
    cout << "职工编号: " << this->m_Id
         << "\t职工姓名: " << this->m_Name
         << "\t岗位: " << this->getDeptName()
         << "\t岗位职责: 完成经理交成的任务" << endl;
}

string Employee::getDeptName()
{
    return string("员工");
}