// device.cpp

#include <cstdint>
#include <format>
#include <iostream>

// 抽象类,device成为一个接口,interfaces
struct device {
    virtual ~device() = default;  // 添加虚析构函数，确保子类释放的时候正确的释放

    virtual int run() = 0;
};

// 两个参数，一个是缓冲区的基本类型(字节或者字符)，一个是缓冲区大小
template <typename buff_base_type, size_t buff_size>
class buffered_device : public device {
protected:
    buff_base_type buffer[buff_size];  // 缓冲区是一个数组
};

// traits
struct readable {
    virtual int read() = 0;
};

struct writeable {
    virtual int write() = 0;
};

// implements
class keyboard
    : public buffered_device<char, 128>,
      public readable {
public:
    int run() override {
        return read();
    }

    int read() override {
        std::cout << "keyboard is reading." << std::endl;
        return 0;
    }
};

using byte = uint8_t;  // 定义字节类型，8位

class harddisk
    : public buffered_device<byte, 4096>,
      public readable,
      public writeable {
public:
    int run() override {
        write();
        read();
        return 0;
    }

    int write() override {
        std::cout << "harddisk is writing." << std::endl;
        return 0;
    }

    int read() override {
        std::cout << "harddisk is reading." << std::endl;
        return 0;
    }
};

int main() {
    keyboard k;
    k.run();

    std::cout << std::endl;

    harddisk h;
    h.run();

    return 0;
}
