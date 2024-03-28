/*
 * Copyright (c) 2023 白忠建 电子科技大学信息与软件工程学院
 * 现代C++程序设计课程源码及其构建系统 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 */


//bzj^_^
//computer.cpp

#include <iostream>
#include <map>
#include <string>
using namespace std;

//traits
template <typename ...types>
struct readable {
    virtual readable *read(types...) = 0;
};

template <typename ...types>
struct writeable {
    virtual writeable *write(types...) = 0;
};

//interface
template <typename ...types>
struct device {
    virtual device *run(types...) = 0;
    virtual ~device() {}
};

//implements
using stream = string;
using stream_ref = stream&;

template <typename ...types>
struct input_device : public device<types...>, public readable<types...> {
    using readable<types...>::read;
    input_device *run(types ...args) override {
        read(args...);
        return this;
    }
};

template <typename ...types>
struct output_device : public device<types...>, public writeable<types...> {
    using writeable<types...>::write;
    output_device *run(types ...args) override {
        write(args...);
        return this;
    }
};

struct keyboard : public input_device<stream_ref> {
    keyboard *read(stream_ref buffer) override {
        cout << "[KEYBOARD]";
        cin >> buffer;
        return this;
    }
};

struct monitor : public output_device<stream_ref> {
    monitor *write(stream_ref buffer) override {
        cout << "[MONITOR]" << buffer << endl;
        return this;
    }
};

struct touchpad : public input_device<stream_ref> {
    touchpad *read(stream_ref buffer) override {
        cout << "[TOUCH]";
        cin >> buffer;
        return this;
    }
};

class computer {
protected:
    using stream_device_ptr = device<stream_ref> *;
    map<string, stream_device_ptr> io_devices;
public:
    computer() {}
    ~computer() {
        for (auto& [key, p] : io_devices) delete p;
    }

    computer &connect(string dev_name, stream_device_ptr dev) {
        io_devices.emplace(dev_name, dev);
        return *this;
    }
    //wrappers
    stream_device_ptr typein(stream_ref buffer) {
        return io_devices["keyboard"]->run(buffer);
    }
    stream_device_ptr touchin(stream_ref buffer) {
        return io_devices["touchpad"]->run(buffer);
    }
    stream_device_ptr display(stream_ref data) {
        return io_devices["monitor"]->run(data);
    }
};

int main() {
    computer c;
    c.connect("keyboard", new keyboard()).connect("monitor", new monitor()).connect("touchpad", new touchpad);
    stream data;
    c.typein(data); c.display(data);
    c.touchin(data); c.display(data);
    return 0;
}
