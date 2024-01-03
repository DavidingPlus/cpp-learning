#pragma once         // 防止头文件重复包含
#include <iostream>  //包含输入输出流头文件
#include <string>

using namespace std;  // 使用标准的命名空间

class WorkerManager {
public:
    // 展示菜单
    void showMenu();

    // 退出系统
    void exitSystem();

    // 构造函数
    WorkerManager();

    // 析构函数
    ~WorkerManager();
};
