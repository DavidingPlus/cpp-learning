#pragma once
using namespace std;
#include <iostream>
#include <algorithm>
#include <deque>
#include <numeric>
#include <vector>
#include <string>
#include "speaker.hpp"
#include <ctime>

//创建一些容器
//第一轮比赛选手容器
vector<Speaker> sps_round1;

//第二轮比赛选手容器
vector<Speaker> sps_round2;

//前三名选手容器
vector<Speaker> sps_victory;

//整个比赛的管理类
class Speech_Manager
{
public:
    Speech_Manager();

    //展示菜单
    void showMenu();

    //初始化演讲
    void InitSpeech();

    //初始化选手信息
    void InitSpeaker(vector<Speaker> &sps);

    //退出程序
    void exitSystem();

    //开始比赛
    void startSpeech();

    //抽签
    void speakDraw(int Round);

    //具体比赛
    void speechContest(int Round);

    ~Speech_Manager();
};

Speech_Manager::Speech_Manager() {}

//展示菜单
void Speech_Manager::showMenu()
{
    cout << "********************************************" << endl;
    cout << "*************  欢迎参加演讲比赛 ************" << endl;
    cout << "*************  1.开始演讲比赛  *************" << endl;
    cout << "*************  2.查看往届记录  *************" << endl;
    cout << "*************  3.清空比赛记录  *************" << endl;
    cout << "*************  0.退出比赛程序  *************" << endl;
    cout << "********************************************" << endl;
    cout << endl;
}

Speech_Manager::~Speech_Manager() {}

void Speech_Manager::exitSystem()
{
    cout << "欢迎下次使用" << endl;
    exit(1);
}

//初始化选手信息
void Speech_Manager::InitSpeaker(vector<Speaker> &sps)
{
    string NameSeed = "ABCDEFGHIJkL";
    int IDSeed = 10001;
    //开始创建选手对象并且插入容器中
    for (auto i = 0; i < 12; ++i)
    {
        string name = "选手";
        name += NameSeed[i];
        int id = IDSeed + i;
        //创建选手对象
        Speaker speaker(name, id);
        //插入容器
        sps.push_back(speaker);
    }
}

void Speech_Manager::InitSpeech()
{
    //将所有容器置空
    sps_round1.clear();
    sps_round2.clear();
    sps_victory.clear();
    //创建选手对象并初始化
    InitSpeaker(sps_round1);
}

//抽签
void Speech_Manager::speakDraw(int Round)
{
    cout << "第 << " << Round << " >> 轮比赛选手正在抽签" << endl;
    cout << "---------------------" << endl;
    cout << "抽签后演讲顺序如下：" << endl;

    //第一轮
    if (Round == 1)
    {
        //打乱容器顺序
        random_shuffle(sps_round1.begin(), sps_round1.end());
        //遍历输出顺序
        for (auto iter = sps_round1.begin(); iter != sps_round1.end(); ++iter)
            cout << iter->get_Id() << ' ';
        cout << endl;
    }
    else
    {
        //打乱容器顺序
        random_shuffle(sps_round2.begin(), sps_round2.end());
        //遍历输出顺序
        for (auto iter = sps_round2.begin(); iter != sps_round2.end(); ++iter)
            cout << iter->get_Id() << ' ';
        cout << endl;
    }
    cout << "---------------------" << endl;
}

//开始比赛
void Speech_Manager::startSpeech()
{
    //初始化
    InitSpeech();
    //第一轮比赛
    // 1、抽签
    speakDraw(1);
    // 2、比赛
    speechContest(1);
    //第二轮比赛
    // 1、抽签
    speakDraw(2);
    // 2、比赛
    speechContest(2);
    cin.get();
    cin.get();
    // 3、保存分数
}

class myCompare1
{
public:
    bool operator()(Speaker &sps1, Speaker &sps2) const
    {
        return sps1.get_Score(1) >= sps2.get_Score(1);
    }
};

class myCompare2
{
public:
    bool operator()(Speaker &sps1, Speaker &sps2) const
    {
        return sps1.get_Score(2) >= sps2.get_Score(2);
    }
};

//具体比赛
void Speech_Manager::speechContest(int Round)
{

    cout << "------------- 第" << Round << "轮正式比赛开始：------------- " << endl;
    //打乱顺序中前六个是一组,后六个是一组
    //创建一个临时比赛容器
    vector<Speaker> game;
    if (Round == 1)
        game = sps_round1;
    else
        game = sps_round2;
    //遍历所有参赛选手
    for (auto iter = game.begin(); iter != game.end(); ++iter)
    {
        //评委打分
        deque<double> S;
        for (int i = 0; i < 10; ++i)
        {
            double s = (rand() % 151 + 800) / 10; // 80~ 95
            S.push_back(s);
        }
        //掐头去尾
        sort(S.begin(), S.end());
        S.pop_back();
        S.pop_front();
        //统计分数
        double score = (double)accumulate(S.begin(), S.end(), 0) / S.size();
        //更新选手的得分信息
        iter->set_Score(Round, score);
    }
    //进行排序
    if (Round == 1)
    {
        //找到迭代器
        auto mid = game.begin();
        for (int i = 0; i < 6; ++i)
            ++mid; //指向第7个
        //第一组和第二组的成绩分别降序排序
        sort(game.begin(), mid, myCompare1()); //注意end是容器最后一个元素的下一个!!!
        sort(mid, game.end(), myCompare1());

        //打印
        cout << "第一小组比赛名次: " << endl;
        auto iter = game.begin();
        for (int i = 0; i < 6; ++i, iter++)
            iter->PrintSpeaker(Round); //第一组
        cout << endl
             << "第二小组比赛名次: " << endl;

        for (int i = 0; i < 6; ++i, mid++)
            mid->PrintSpeaker(Round); //第二组

        cout << "------------- 第" << Round << "轮比赛完毕  ------------- " << endl;

        //打印前6
        //整体排序得出前6
        sort(game.begin(), game.end(), myCompare1());
        cout << endl
             << "---------第" << Round << "轮晋级选手信息如下：-----------" << endl
             << endl;

        game.resize(game.size() / 2);
        for (auto iter = game.begin(); iter != game.end(); ++iter)
            iter->PrintSpeaker(Round);

        //将这前6个转移到第二个容器中
        sps_round2.resize(game.size());
        sps_round2 = game;
    }
    else
    {
        //降序排序找到前三
        sort(game.begin(), game.end(), myCompare2());
        //打印成绩
        //打印
        cout << "比赛名次: " << endl;
        auto iter = game.begin();
        for (int i = 0; i < 6; ++i, iter++)
            iter->PrintSpeaker(Round);

        cout << "------------- 第" << Round << "轮比赛完毕  ------------- " << endl;

        //打印前3
        cout << endl
             << "---------第" << Round << "轮晋级选手信息如下：-----------" << endl
             << endl;

        game.resize(game.size() / 2);
        for (auto iter = game.begin(); iter != game.end(); ++iter)
            iter->PrintSpeaker(Round);
    }
}
