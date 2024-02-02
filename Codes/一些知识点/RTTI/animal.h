#ifndef _ANIMAL_H_
#define _ANIMAL_H_

#include <iostream>

class Animal {
public:
    Animal() = default;
    virtual ~Animal() = default;

    virtual void speak() = 0;
};

class Dog : public Animal {
public:
    Dog() = default;
    ~Dog() = default;

    void speak() override final;
};

class Cat : public Animal {
public:
    Cat() = default;
    ~Cat() = default;

    void speak() override final;
};

#endif
