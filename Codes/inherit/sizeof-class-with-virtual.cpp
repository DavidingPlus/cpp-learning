// sizeof-class-with-virtual.cpp
#include <iostream>

// alignas()，内存对齐
class alignas(8) noVirtual {
    char a;
    void f() {}
};

class alignas(8) oneVirtual {
    char a;
    virtual void f() {}
};

class alignas(8) manyVirtual {
    char a;
    virtual void f() {}
    virtual int g() {
        return 0;
    }
    virtual double h(double) {
        return 1.0;
    }
};

int main() {
    std::cout << "size of noVirtual: " << sizeof(noVirtual) << std::endl;      // 8
    std::cout << "size of oneVirtual: " << sizeof(oneVirtual) << std::endl;    // 16
    std::cout << "size of manyVirtual: " << sizeof(manyVirtual) << std::endl;  // 16
    std::cout << "ref: size of pointer: " << sizeof(void *) << std::endl;      // 8

    return 0;
}
