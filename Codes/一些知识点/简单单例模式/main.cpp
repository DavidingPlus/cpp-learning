#include <iostream>

#include "singleton.h"

int main() {
    // Singleton s;  // error

    Singleton *s1 = Singleton::getInstance();
    Singleton *s2 = Singleton::getInstance();

    s1->print();
    s2->print();

    return 0;
}
