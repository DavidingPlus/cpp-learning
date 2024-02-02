#include <iostream>
#include <typeinfo>

#include "animal.h"

// RTTI机制，运行时类型识别，主要是在用在多态里面，程序能使用基类的指针来识别实际使用的派生类类型
void test1();
void test2();

int main() {
    test1();
    std::cout << "----------------------------------" << '\n';
    test2();

    return 0;
}

void test1() {
    // dynamic_cast
    Animal* dog = new Dog;

    // 检查dog的类型
    // 如果能安全转换返回转换后的指针，不则返回空指针或者抛出异常
    Dog* res = dynamic_cast<Dog*>(dog);  // success
    if (res)
        std::cout << "Dog success.\n";

    Cat* res2 = dynamic_cast<Cat*>(dog);  // fail
    if (res2)
        std::cout << "Cat success.\n";
}

void test2() {
    // typeinfo
    // typeinfo类将构造函数，拷贝构造，移动构造等全部都删除了，因此不能实例化，其中含有方法name()，==，!=
    // 使用typeinfo的唯一方式是通过关键字typeid
    int a = 1;

    // 不同的编译器输出的结果不同，Ubuntu下这里返回的是 i
    std::cout << typeid(a).name() << '\n';

    // 但是尽管编译器的实现存在差异，typeid是可以进行==号和!=号的比较的
    std::cout << (typeid(a) == typeid(int)) << '\n';     // true
    std::cout << (typeid(a) == typeid(double)) << '\n';  // false

    // typeid作用于自定义类
    // 可以看出是有一定规律的，可以在构造函数的时候做一定解析存入类中
    std::cout << typeid(Animal).name() << '\n';  // 6Animal
    std::cout << typeid(Dog*).name() << '\n';    // P3Dog
    std::cout << typeid(Cat**).name() << '\n';   // PP3Cat
}
