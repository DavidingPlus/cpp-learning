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
//lkp-switch.cpp

#include <iostream>
#include <string>
#include <map>
using namespace std;

template <typename ...types>
void println(types ...args) {
    (cout << ... << args);
    cout << endl;
}

using port_t = unsigned char;
struct message {
    port_t src;
    port_t dest;
    string text;
};

class Switch;
struct communicator { //traits
    string id;
    const Switch &sw;
    port_t port;
    communicator(const string &i, const Switch &s) : id(i), sw(s) {}
    void send(communicator &dest, const string &msg);
    void receive(const message &m);
    void plugin(port_t p);
};

class Switch {
private:
    mutable map<port_t, communicator *> port_map_table;
public:
    enum : port_t { P0 = 'A', P1, P2, P3, P4, P5, P6, P7, END};

    Switch() {
        for (port_t p = P0; p < END; ++p) port_map_table.emplace(p, nullptr);
    }
    Switch(const Switch &) = delete; //copy is banned
    Switch(Switch &&) = delete; //move is banned
    bool bind(port_t p, communicator *c) const {
        if (port_map_table[p] != nullptr) {
            println("port ", p, " is taken");
            return false;
        } else {
            port_map_table[c->port = p] = c;
            return true;
        }
    }
    void forward(message &&m) const {
        if (port_map_table[m.dest] == nullptr) println("port ", m.dest, " is not available");
        else port_map_table[m.dest]->receive(m);
    }
};

void communicator::send(communicator &dest, const string &msg) {
    println(id, "@port ", port, ": prepare sending message to port ", dest.port);
    sw.forward({port, dest.port, msg});
}
void communicator::receive(const message &m) {
    println(id, "@port ", m.dest, ": receiving forwarding message from port ", m.src);
    println("[message received]: ", m.text);
}
void communicator::plugin(port_t p) {
    sw.bind(p, this);
}

template <typename ...base_classes>
struct X : public communicator, public base_classes... {
    X(const string &id, const Switch &sw) : communicator(id, sw), base_classes()... {}
    };

int main() {
    const Switch sw; //only 1 switch exists
    X a("Object A", sw), b("Object B", sw), c("Object C", sw), d("Object D", sw);
    a.plugin(Switch::P0); b.plugin(Switch::P1); c.plugin(Switch::P4); d.plugin(Switch::P5);

    a.send(b, "Ciao!");
    a.send(c, "Good morning!");
    b.send(d, "Are you ready?");
    d.send(c, "Object B sent me a message.");

    X<> *e = new X<>("Object E", sw);
    e->plugin(Switch::P7);
    a.send(*e, "Hello, new comer!");
    delete e;

    return 0;
}
