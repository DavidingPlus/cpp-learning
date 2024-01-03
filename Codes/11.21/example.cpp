#include <iostream>
using namespace std;
#include <vector>
#include <deque>
#include <cstring>
#include <algorithm>
#include <ctime>

/* 有5名选手：选手ABCDE，10个评委分别对每一名选手打分，去除最高分，去除评委中最低分，取平均分。
1. 创建五名选手，放到vector中
2. 遍历vector容器，取出来每一个选手，执行for循环，可以把10个评分打分存到deque容器中
3. sort算法对deque容器中分数排序，去除最高和最低分
4. deque容器遍历一遍，累加总分
5. 获取平均分 */

class Player
{
public:
    Player(string name, int score = 0) : m_Name(name), m_Score(score) {}
    void set_m_Score(int score) { this->m_Score = score; }
    string getName() { return this->m_Name; }
    int getScore() { return this->m_Score; }

private:
    string m_Name;
    int m_Score;
};

//创建容器对象 将姓名初始化
vector<Player> createPlayer()
{
    vector<Player> player;
    string str = "ABCDE";
    for (auto i = 0; i < 5; ++i)
    {
        string namebase = "选手";
        namebase += str[i];
        Player p(namebase);
        player.push_back(p);
    }
    return player;
}

//打分 将分数数据初始化 并且放到deque容器中
void setScore(vector<Player> &player)
{
    //随机数种子
    srand((unsigned int)time(NULL));
    //取出来每一个选手 十个评委对其打分
    for (vector<Player>::iterator iter = player.begin(); iter < player.end(); ++iter)
    {
        deque<int> dScore;
        //十个评委打分
        for (int i = 0; i < 10; ++i)
        {
            int score = rand() % 41 + 60; // 60 ~ 100
            //将该分数存到deque容器中
            dScore.push_back(score);
        }
        //排序
        sort(dScore.begin(), dScore.end());
        //去除最高分和最低分
        dScore.pop_back();
        dScore.pop_front();

        //遍历一遍获取总分
        int num = 0;
        for (deque<int>::iterator iter = dScore.begin(); iter < dScore.end(); ++iter)
            num += *iter;
        iter->set_m_Score(num / dScore.size());
    }
}

void showScore(vector<Player> &player)
{
    for (vector<Player>::iterator iter = player.begin(); iter < player.end(); ++iter)
        cout << iter->getName() << "得分为: " << iter->getScore() << endl;
}

int main()
{
    //创建五个选手
    auto player = createPlayer();
    //给五位选手打分
    setScore(player);
    //展示得分
    showScore(player);

    return 0;
}
