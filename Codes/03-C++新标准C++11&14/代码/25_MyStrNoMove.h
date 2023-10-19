#ifndef _MYSTRNOMOVE_H_
#define _MYSTRNOMOVE_H_

using namespace std;
#include <cstring>
#include <iostream>
#include <string>

class MyStrNoMove {
    // 拿掉move ctor和 move asgn
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
    MyStrNoMove() : _data(nullptr), _len(0) { ++DCtor; }

    // ctor
    MyStrNoMove(const char* p) : _len(strlen(p)) {
        ++Ctor;
        _init_data(p);
    }

    // copy-ctor
    MyStrNoMove(const MyStrNoMove& str) : _len(str._len) {
        ++CCtor;
        _init_data(str._data);
    }

    // copy-asgn
    MyStrNoMove& operator=(const MyStrNoMove& str) {
        ++CAsgn;
        // 自我赋值检查
        if (this != &str) {
            _len = str._len;
            _init_data(str._data);
        } else
            throw invalid_argument("cannot assign yourself.");
        return *this;
    }

    // dtor
    virtual ~MyStrNoMove() {
        ++DCtor;
        if (_data)
            delete _data;
    }

    // operator <
    bool operator<(const MyStrNoMove& rhs) const {  // 为了set
        return string(this->_data) < string(rhs._data);
    }

    // operator ==
    bool operator==(const MyStrNoMove& rhs) const {  // 为了set
        return string(this->_data) == string(rhs._data);
    }

    char* get() const { return _data; }
};

// 初始化静态变量
size_t MyStrNoMove::DCtor = 0;  // 累计 default-ctor呼叫次数
size_t MyStrNoMove::Ctor = 0;   // 累计 ctor呼叫次数
size_t MyStrNoMove::CCtor = 0;  // 累计 copy-ctor呼叫次数
size_t MyStrNoMove::CAsgn = 0;  // 累计 copy-asgn呼叫次数
size_t MyStrNoMove::MCtor = 0;  // 累计 move-ctor呼叫次数
size_t MyStrNoMove::MAsgn = 0;  // 累计 move-asgn呼叫次数
size_t MyStrNoMove::Dtor = 0;   // 累计 default-ctor呼叫次数

// 处理hashcode 放在std中和标准库合并
namespace std {
template <>
struct hash<MyStrNoMove> {
    size_t operator()(const MyStrNoMove& s) {
        return hash<string>()(string(s.get()));
    }
};
}  // namespace std

#endif
