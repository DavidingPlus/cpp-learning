#ifndef __MYSTRING__
#define __MYSTRING__
#include <cstring>

class String
{
public:
    String(const char *cstr = 0);
    // 只要类带指针，一定要重写以下两个函数!!!
    String(const String &str);            // 拷贝构造
    String &operator=(const String &str); // 拷贝赋值

    ~String();

    char *get_c_str() const { return this->_data; }

private:
    char *_data;
};

inline String::String(const char *cstr)
{
    if (!cstr)
    {
        this->_data = new char[1];
        this->_data[0] = '\0'; // 放结束符
    }
    else
    {
        this->_data = new char[strlen(cstr) + 1]; // 多一个放存结束符'\0'
        strcpy(this->_data, cstr);
    }
}

inline String::String(const String &str)
{
    // 深拷贝
    this->_data = new char[strlen(str._data) + 1];
    strcpy(this->_data, str._data);
}

inline String::~String()
{
    delete[] this->_data;
    this->_data = nullptr;
}

inline String &
String::operator=(const String &str)
{
    // 深拷贝赋值 先把自身杀掉 然后重新创建
    // 检测自我赋值
    if (this == &str)
        return *this;

    delete[] this->_data;
    // 深拷贝
    this->_data = new char[strlen(str._data) + 1];
    strcpy(this->_data, str._data);
    return *this;
}

// 全局的输出函数
inline ostream &
operator<<(ostream &os, const String &str)
{
    os << str.get_c_str();
    return os;
}

#endif
