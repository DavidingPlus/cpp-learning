#include <iostream>
#include <string.h>
using namespace std;

//虚析构和纯虚析构
class Animal
{
public:
    Animal() { cout << "Animal构造函数调用" << endl; }
    //纯虚函数
    virtual void speak() = 0;

    // //利用虚析构可以解决 父类指针释放子类对象时不干净的问题
    // virtual ~Animal() { cout << "Animal析构函数调用" << endl; }

    //纯虚析构 需要声明,也需要实现,并且在外部实现
    //有了纯虚析构,这个类也属于抽象类,无法实例化对象!!!
    virtual ~Animal() = 0;
};

Animal::~Animal() { cout << "Animal纯虚析构函数调用" << endl; }

class Cat : public Animal
{
public:
    Cat(string name)
    {
        cout << "Cat构造函数调用" << endl;
        m_Name = new string(name);
    }

    void speak() { cout << *m_Name << "小猫在说话" << endl; }

    ~Cat()
    {
        if (m_Name)
        {
            cout << "Cat析构函数调用" << endl;
            delete m_Name;
            m_Name = nullptr;
        }
    }

    string *m_Name;
};

void test01()
{
    Animal *animal = new Cat("Tom");
    animal->speak();

    //父类的指针在析构的时候不会调用子类中析构函数,导致子类如果有堆区属性,出现泄露
    delete animal;
}

int main()
{
    test01();

    return 0;
}
