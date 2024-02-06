#include <iostream>
using namespace std;

class Animal {
public:
    virtual void speak() = 0;
};

class Dog : public Animal {
public:
    void speak() { cout << "Dog speak." << endl; }
};

class Cat : public Animal {
public:
    void speak() { cout << "Cat speak." << endl; }
};

int main() {
    Animal *dog = new Dog();
    dog->speak();

    Animal *cat = new Cat();
    cat->speak();

    return 0;
}
