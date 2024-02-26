#include "singleton.h"

Singleton *Singleton::m_instance = nullptr;

Singleton *Singleton::getInstance()
{
    if (nullptr == m_instance)
        m_instance = new Singleton();
    return m_instance;
}

void Singleton::releaseInstance()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

void Singleton::print()
{
    std::cout << "address: " << m_instance << '\n';
}
