//device.cpp

#include <iostream>
#include <format>
#include <cstdint>

// interfaces
struct device {
    virtual int run() = 0;
    virtual ~device() {}
};

template <typename buff_base_type, size_t buff_size>
class buffered_device : public device {
protected:
    buff_base_type buffer[buff_size];
};

// traits
struct readable {
    virtual int read() = 0;
};

// implements
class keyboard : public buffered_device<char, 128>, public readable {
public:
    int read() override {
        std::cout << "keyboard is reading...\n";
        return 0;
    }

    int run() override {
        return read();
    }
};

using byte = uint8_t;
class harddisk : public buffered_device<byte, 4096>, public readable {
public:
    int read() override {
        std::cout << "harddisk is reading...\n";
        return 0;
    }

    int run() override {
        return read();
    }
};

int main() {
    keyboard().run();
    harddisk().run();
    
    return 0;
}