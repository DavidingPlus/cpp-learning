//经理文件
#pragma once
#include <iostream>
using namespace std;
#include "worker.h"

class Manager : public Worker
{
public:
    //构造函数
    Manager(int id, string name, int dId);
    //显示个人信息
    void showInfo();
    //获取岗位名称
    string getDeptName();
};

Manager::Manager(int id, string name, int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = dId;
}

void Manager::showInfo()
{
    cout << "职工编号: " << this->m_Id
         << "\t职工姓名: " << this->m_Name
         << "\t岗位: " << this->getDeptName()
         << "\t岗位职责: 完成老板交成的任务,并下发给员工" << endl;
}

string Manager::getDeptName()
{
    return string("经理");
}