#ifndef _SIGLETON_H_
#define _SIGLETON_H_

#include <iostream>
#include <unistd.h>

class Singleton
{
public:
    static Singleton *getInstance();

    static void releaseInstance();

    void print();

    unsigned long threadID() { return (unsigned long)pthread_self(); }

protected:
    Singleton() = default;
    virtual ~Singleton() { releaseInstance(); }

    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

    Singleton(Singleton &&) = delete;
    Singleton &operator=(Singleton &&) = delete;

private:
    static Singleton *m_instance;
};

#endif
