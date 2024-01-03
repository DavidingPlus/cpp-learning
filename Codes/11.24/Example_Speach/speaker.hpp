#pragma once
#include <iostream>
#include <string>
using namespace std;

class Speaker
{
public:
    Speaker();
    Speaker(string name, int id);

    string get_Name();
    int get_Id();

    //因为set_Score中需要用到这一个函数得到成绩进行修改,所以返回左值引用 &
    double &get_Score(int round); //根据第几轮来得到得分

    void set_Score(int round, double score); //设置分数

    void PrintSpeaker(int Round); //打印信息

private:
    string Name;           //姓名
    int Id;                //编号
    double Score[2] = {0}; //两轮分数
};

Speaker::Speaker() {}

Speaker::Speaker(string name, int id)
{
    this->Name = name;
    this->Id = id;
}

int Speaker::get_Id()
{
    return this->Id;
}

string Speaker::get_Name()
{
    return this->Name;
}

double &Speaker::get_Score(int round)
{
    return this->Score[round - 1];
}

void Speaker::set_Score(int round, double score)
{
    this->get_Score(round) = score;
}
void Speaker::PrintSpeaker(int Round)
{
    cout << "编号: " << this->get_Id() << " 姓名: " << this->get_Name() << " 成绩: " << this->get_Score(Round) << endl;
}