#include <iostream>
using namespace std;

//抽象不同零件类
//抽象CPU类
class CPU
{
public:
    //抽象的计算函数
    virtual void calculate() = 0;
};

//抽象显卡类
class VideoCard
{
public:
    //抽象的计算函数
    virtual void display() = 0;
};

//抽象内存条类
class Memory
{
public:
    //抽象的计算函数
    virtual void storage() = 0;
};

//电脑类
class Computer
{
public:
    Computer(CPU *cpu, VideoCard *vc, Memory *mem) : m_cpu(cpu), m_vc(vc), m_mem(mem) {}

    //提供工作函数
    void Work()
    {
        //让零件工作起来,调用接口
        m_cpu->calculate();
        m_vc->display();
        m_mem->storage();
    }

    //提供析构函数 释放三个电脑零件
    ~Computer()
    {
        //释放CPU零件
        if (m_cpu)
        {
            delete m_cpu;
            m_cpu = nullptr;
        }
        //释放显卡零件
        if (m_vc)
        {
            delete m_vc;
            m_vc = nullptr;
        }
        //释放内存条零件
        if (m_mem)
        {
            delete m_mem;
            m_mem = nullptr;
        }
    }

private:
    CPU *m_cpu;      // CPU的零件指针
    VideoCard *m_vc; //显卡零件指针
    Memory *m_mem;   //内存条零件指针
};

//具体厂商
// Intel厂商
class IntelCPU : public CPU
{
    void calculate() { cout << "Intel的CPU开始计算了!" << endl; }
};

class IntelVideoCard : public VideoCard
{
    void display() { cout << "Intel的显卡开始显示了!" << endl; }
};

class IntelMemory : public Memory
{
    void storage() { cout << "Intel的内存条开始存储了!" << endl; }
};

// Lenovo厂商
class LenovoCPU : public CPU
{
    void calculate() { cout << "Lenovo的CPU开始计算了!" << endl; }
};

class LenovoVideoCard : public VideoCard
{
    void display() { cout << "Lenovo的显卡开始显示了!" << endl; }
};

class LenovoMemory : public Memory
{
    void storage() { cout << "Lenovo的内存条开始存储了!" << endl; }
};

void test01()
{
    //第一台电脑零件
    cout << "第一台电脑开始工作: " << endl;
    //创建第一台电脑
    Computer *computer1 = new Computer(new IntelCPU, new IntelVideoCard, new IntelMemory);
    computer1->Work();
    delete computer1;

    cout << "-------------------------------" << endl;
    cout << "第二台电脑开始工作: " << endl;
    //第二台电脑组装
    Computer *computer2 = new Computer(new LenovoCPU, new LenovoVideoCard, new LenovoMemory);
    computer2->Work();
    delete computer2;
}

int main()
{
    test01();

    return 0;
}
