#include <iostream>
using namespace std;
#include "26_Stone.h"

// 接受参数包,计算hashcode
namespace Hash {

template <typename Value_type>
void ChangeSeed(size_t &seed, const Value_type &val) {
    seed ^= hash<Value_type>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename Value_type, typename... Args>
void ChangeSeed(size_t &seed, const Value_type &val, const Args &...args) {
    ChangeSeed(seed, val);
    ChangeSeed(seed, args...);
}

template <typename... Args>
size_t HashCode(const Args &...args) {
    size_t seed = 0;
    ChangeSeed(seed, args...);
    return seed;
}

};  // namespace Hash

namespace std {
template <>
struct hash<Stone> {
    size_t operator()(const Stone &sto) {
        return Hash::HashCode(sto.getLen(), sto.getWid(), sto.getHei(), sto.getWei());
    }
};
};  // namespace std

namespace Test {
void testHash() {
    size_t hCode1 = hash<const char *>()("kiwi");
    size_t hCode2 = hash<const char *>()("plum");
    size_t hCode3 = hash<const char *>()("apple");

    cout << "HashCode of kiwi is : " << hCode1 << endl;
    cout << "HashCode of plum is : " << hCode2 << endl;
    cout << "HashCode of apple is : " << hCode3 << endl;
}

void testStone() {
    Stone s1(1.23, 2.34, 3.45, 4.56);
    size_t hCode1 = hash<Stone>()(s1);
    cout << "HashCode of s1 is : " << hCode1 << endl;
}
};  // namespace Test

int main() {
    Test::testHash();
    cout << endl;
    Test::testStone();

    return 0;
}
