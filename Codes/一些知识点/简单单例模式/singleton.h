#ifndef _SIGLETON_H_
#define _SIGLETON_H_

#include <iostream>

class Singleton {
public:
    static Singleton* getInstance();

    void print();

protected:
    Singleton() = default;
    virtual ~Singleton() = default;

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

private:
    static Singleton* m_instance;
};

#endif
