#include <iostream>
using namespace std;
#include <string>
#include <map>
#include "employee.hpp"
#include <vector>
#include <ctime>

/*
公司今天招聘了10个员工（ABCDEFGHIJ），10名员工进入公司之后，需要指派员工在那个部门工作
员工信息有: 姓名  工资组成；部门分为：策划、美术、研发
随机给10名员工分配部门和工资
通过multimap进行信息的插入  key(部门编号) value(员工)
分部门显示员工信息
*/

//步骤
/*
1. 创建10名员工，放到vector中
2. 遍历vector容器，取出每个员工，进行随机分组
3. 分组后，将员工部门编号作为key，具体员工作为value，放入到multimap容器中
4. 分部门显示员工信息
*/

//创建部门信息
using Dep_name = string;
using DeptId = size_t;
map<DeptId, Dep_name> Create_Dep()
{
    map<DeptId, Dep_name> deps;
    deps.insert(make_pair(1, "策划"));
    deps.insert(make_pair(2, "美术"));
    deps.insert(make_pair(3, "研发"));

    return deps;
}

//创建员工信息
vector<Employee> Create_Emp()
{
    vector<Employee> emps;
    //初始化信息
    string Namebase = "ABCDEFGHIJ";
    for (auto i = 0; i < 10; ++i)
    {
        string name = "员工";
        name.append(Namebase, i, 1);
        int salary = rand() % 10000 + 10000; // 10000 ~ 19999

        Employee emp(name, salary);
        emps.push_back(emp);
    }
    return emps;
}

//将员工进行随机分组
using Key = DeptId;
using Value = Employee;
multimap<Key, Value> setGroup(vector<Employee> &emps, map<DeptId, Dep_name> &deps)
{
    multimap<Key, Value> memps;
    //遍历员工进行分组
    for (vector<Employee>::iterator iter = emps.begin(); iter != emps.end(); ++iter)
    {
        //产生随机部门编号
        size_t deptId = rand() % 3 + 1; // 1 2 3
        memps.insert(make_pair(deptId, *iter));
    }

    return memps;
}

void showEmployees(multimap<Key, Value> &memps)
{
    cout << "策划部门: " << endl; // ID 1
    for (auto iter = memps.begin(); iter != memps.end(); ++iter)
        if (iter->first == 1)
            cout << "姓名: " << iter->second.get_Name() << " 工资: " << iter->second.get_Salary() << endl;
    cout << "----------------------" << endl;
    cout << "美术部门: " << endl; // ID 2
    for (auto iter = memps.begin(); iter != memps.end(); ++iter)
        if (iter->first == 2)
            cout << "姓名: " << iter->second.get_Name() << " 工资: " << iter->second.get_Salary() << endl;
    cout << "----------------------" << endl;
    cout << "研发部门: " << endl; // ID 3
    for (auto iter = memps.begin(); iter != memps.end(); ++iter)
        if (iter->first == 3)
            cout << "姓名: " << iter->second.get_Name() << " 工资: " << iter->second.get_Salary() << endl;
}

int main()
{
    //随机数参数
    srand((size_t)time(NULL));

    //创建部门信息
    auto departments = Create_Dep();
    // for (auto iter = departments.begin(); iter != departments.end(); ++iter)
    //     cout << "编号: " << iter->first << " 部门: " << iter->second << endl;

    //创建员工信息
    auto employees = Create_Emp();
    // for (auto iter = employees.begin(); iter != employees.end(); ++iter)
    //     cout << "姓名： " << iter->get_Name() << " 工资： " << iter->get_Salary() << endl;

    //将员工进行随机分组
    auto memployees = setGroup(employees, departments);

    //打印输出
    showEmployees(memployees);

    return 0;
}
