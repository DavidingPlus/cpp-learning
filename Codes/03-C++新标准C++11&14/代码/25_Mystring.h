#ifndef _MYSTRING_H_
#define _MYSTRING_H_

using namespace std;
#include <cstring>
#include <iostream>
#include <string>
// 写一个 move aware class
class Mystring {
public:
    static size_t DCtor;  // 累计 default-ctor呼叫次数
    static size_t Ctor;   // 累计 ctor呼叫次数
    static size_t CCtor;  // 累计 copy-ctor呼叫次数
    static size_t CAsgn;  // 累计 copy-asgn呼叫次数
    static size_t MCtor;  // 累计 move-ctor呼叫次数
    static size_t MAsgn;  // 累计 move-asgn呼叫次数
    static size_t Dtor;   // 累计 default-ctor呼叫次数
private:
    char* _data;
    size_t _len;

    void _init_data(const char* s) {
        _data = new char[_len + 1];
        memcpy(_data, s, _len);  // 这是一个深拷贝
        _data[_len] = '\0';
    }

public:
    // default-ctor
    Mystring() : _data(nullptr), _len(0) { ++DCtor; }

    // ctor
    Mystring(const char* p) : _len(strlen(p)) {
        ++Ctor;
        _init_data(p);
    }

    // copy-ctor
    Mystring(const Mystring& str) : _len(str._len) {
        ++CCtor;
        _init_data(str._data);
    }

    // copy-asgn
    Mystring& operator=(const Mystring& str) {
        ++CAsgn;
        // 自我赋值检查
        if (this != &str) {
            _len = str._len;
            _init_data(str._data);
        } else
            throw invalid_argument("cannot assign yourself.");
        return *this;
    }

    // move ctor, with noexcept
    Mystring(Mystring&& str) noexcept : _data(str._data), _len(str._len) {  // 指针相同表示指向同一块内存，就是一个偷的动作，是浅拷贝!!!
        // 完事之后将原来的str处理一下，能够传入右值引用都表示今后这个东西不用了
        // 所以不用了，但是也不要删除掉
        ++MCtor;
        str._len = 0;
        str._data = nullptr;  // 重要!!!
    }

    // move asgn, with noexcept
    Mystring& operator=(Mystring&& str) {
        ++MAsgn;
        // 自我赋值检查
        if (this != &str) {
            _data = str._data;
            _len = str._len;

            str._len = 0;
            str._data = nullptr;
        }
        return *this;
    }

    // dtor
    virtual ~Mystring() {
        ++DCtor;
        if (_data)
            delete _data;
    }

    // operator <
    bool operator<(const Mystring& rhs) const {  // 为了set
        return string(this->_data) < string(rhs._data);
    }

    // operator ==
    bool operator==(const Mystring& rhs) const {  // 为了set
        return string(this->_data) == string(rhs._data);
    }

    char* get() const { return _data; }
};

// 初始化静态变量
size_t Mystring::DCtor = 0;  // 累计 default-ctor呼叫次数
size_t Mystring::Ctor = 0;   // 累计 ctor呼叫次数
size_t Mystring::CCtor = 0;  // 累计 copy-ctor呼叫次数
size_t Mystring::CAsgn = 0;  // 累计 copy-asgn呼叫次数
size_t Mystring::MCtor = 0;  // 累计 move-ctor呼叫次数
size_t Mystring::MAsgn = 0;  // 累计 move-asgn呼叫次数
size_t Mystring::Dtor = 0;   // 累计 default-ctor呼叫次数

// 处理hashcode 放在std中和标准库合并
namespace std {
template <>
struct hash<Mystring> {
    size_t operator()(const Mystring& s) {
        return hash<string>()(string(s.get()));
    }
};
}  // namespace std

#endif
