//老板文件
#pragma once
#include <iostream>
using namespace std;
#include "worker.h"

class Boss : public Worker
{
public:
    //构造函数
    Boss(int id, string name, int dId);
    //显示个人信息
    void showInfo();
    //获取岗位名称
    string getDeptName();
};

Boss::Boss(int id, string name, int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = dId;
}

void Boss::showInfo()
{
    cout << "职工编号: " << this->m_Id
         << "\t职工姓名: " << this->m_Name
         << "\t岗位: " << this->getDeptName()
         << "\t岗位职责: 管理公司所有事务" << endl;
}

string Boss::getDeptName()
{
    return string("总裁");
}