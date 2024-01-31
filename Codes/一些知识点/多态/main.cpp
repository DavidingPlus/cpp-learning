#include <iostream>
using namespace std;

class Animal {
public:
    virtual void bite() = 0;
};

class Dog : public Animal {
public:
    void bite() { cout << "Dog bite" << endl; }
};

class Cat : public Animal {
public:
    void bite() { cout << "Cat bite" << endl; }
};

int main() {
    Animal *dog = new Dog();
    dog->bite();

    Animal *cat = new Cat();
    cat->bite();

    return 0;
}
