#include <iostream>
using namespace std;

class Animal
{
public:
    virtual void speak() = 0;
};

class Cat : public Animal
{
public:
    virtual void speak() { cout << "喵喵喵" << endl; }
};

class Dog : public Animal
{
public:
    virtual void speak() { cout << "汪汪汪" << endl; }
};

int main()
{
    Animal *cat = new Cat();
    cat->speak(); // 喵喵喵

    Animal *dog = new Dog();
    dog->speak(); // 汪汪汪

    return 0;
}
