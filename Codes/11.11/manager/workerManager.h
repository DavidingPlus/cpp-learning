#pragma once         //防止头文件重复包含
#include <iostream>  //包含输入输入流的头文件
using namespace std; //使用标准空间
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>
#define FILENAME "empFile.txt"

class WorkerManager
{
public:
    //构造函数
    WorkerManager();

    //展示菜单
    void Show_Menu();

    //退出系统
    void ExitSystem();

    //记录职工人数
    int m_EmpNum;

    //职工数组指针
    Worker **m_EmpArray;

    //添加职工
    void Add_Emp();

    //保存文件
    void save();

    //析构函数
    ~WorkerManager();
};

//类外实现(在外面创建一个cpp会出问题)
WorkerManager::WorkerManager() {}

void WorkerManager::Show_Menu()
{
    cout << "********************************************" << endl;
    cout << "*********  欢迎使用职工管理系统！ **********" << endl;
    cout << "*************  0.退出管理程序  *************" << endl;
    cout << "*************  1.增加职工信息  *************" << endl;
    cout << "*************  2.显示职工信息  *************" << endl;
    cout << "*************  3.删除离职职工  *************" << endl;
    cout << "*************  4.修改职工信息  *************" << endl;
    cout << "*************  5.查找职工信息  *************" << endl;
    cout << "*************  6.按照编号排序  *************" << endl;
    cout << "*************  7.清空所有文档  *************" << endl;
    cout << "********************************************" << endl;
    cout << endl;
}

WorkerManager::~WorkerManager()
{
    this->m_EmpNum = 0;
    if (this->m_EmpArray)
    {
        delete[] this->m_EmpArray;
        this->m_EmpArray = nullptr;
    }
}

void WorkerManager::ExitSystem()
{
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);
}

void WorkerManager::Add_Emp()
{
    cout << "请输入添加职工数量: " << endl;

    int addNum = 0; //保存用户的输入数量
    cin >> addNum;
    if (addNum)
    {
        //添加
        //计算添加新空间大小
        int newSize = this->m_EmpNum + addNum; //新空间人数 = 原来记录人数 + 新增加人数

        //开辟新空间
        Worker **newSpace = new Worker *[newSize];

        //将原来空间数据,拷贝到新空间下
        if (this->m_EmpArray)
        {
            for (int i = 0; i < this->m_EmpNum; ++i)
                newSpace[i] = this->m_EmpArray[i];
            //批量添加新数据
            for (int i = 0; i < addNum; ++i)
            {
                int id;      //职工编号
                string name; //职工姓名
                int dSelect; //部门选择

                cout << "请输入第" << i + 1 << "个新职工编号: " << endl;
                cin >> id;
                cout << "请输入第" << i + 1 << "个新职工姓名: " << endl;
                cin >> name;
                cout << "请选择该职工岗位: " << endl;
                cout << "1.普通职工:  " << endl;
                cout << "2.经理: " << endl;
                cout << "3.老板: " << endl;
                cin >> dSelect;

                Worker *worker = nullptr;
                switch (dSelect)
                {
                case 1: //普通员工
                    worker = new Employee(id, name, 1);
                    break;
                case 2: //经理
                    worker = new Manager(id, name, 2);
                    break;
                case 3: //老板
                    worker = new Boss(id, name, 3);
                    break;
                default:
                    break;
                }
                //将创建职工职责,保存到数组中
                newSpace[this->m_EmpNum + i] = worker;
            }
            //释放原有空间
            delete[] this->m_EmpArray;

            //更改新空间的指向
            this->m_EmpArray = newSpace;

            //更新新的职工个数
            this->m_EmpNum = newSize;

            //提示信息
            cout << "成功添加" << addNum << "名新职工！" << endl;

            this->save();
        }
    }
    else
        cout << "数据有误" << endl;

    system("pause");
    system("cls");
}

void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out); //用输出的方式打开文件 写文件

    //将每个人的数据写入文件
    for (int i = 0; i < this->m_EmpNum; ++i)
        ofs << this->m_EmpArray[i]->m_Id << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptId << endl;

    //关闭文件
    ofs.close();
}