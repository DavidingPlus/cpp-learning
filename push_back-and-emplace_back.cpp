#include <iostream>
using namespace std;
#include <string>
#include <vector>

class A {
public:
    A() = default;

    A(int a, string b) : a(a), b(b) { cout << "A(int a, string b)" << endl; }

    A(const A& other) : a(other.a), b(other.b) { cout << "A(const A& other)" << endl; }

    A(A&& other) {
        swap(a, other.a);
        swap(b, other.b);

        cout << "A(A&& other)" << endl;
    }

    ~A() { cout << "~A()" << endl; }

private:
    int a;
    string b;
};

int main() {
    // test1
    vector<A> v1;
    v1.reserve(100);

    A a1{1, "fuck"};

    v1.push_back(a1);
    v1.emplace_back(a1);

    cout << endl;

    // test2
    vector<A> v2;
    v2.reserve(100);

    A a2{1, "fuck"};

    v2.push_back(move(a2));
    v2.emplace_back(move(a2));

    cout << endl;

    // test3
    vector<A> v3;
    v3.reserve(100);

    v3.push_back(A{1, "fuck"});
    v3.emplace_back(A{1, "fuck"});
    v3.emplace_back(1, "fuck");  // 这里就是不同之处!!!

    cout << endl;

    // 可能会出现的问题
    vector<vector<int>> v4;
    v4[0].push_back(1 << 20);
    v4[0].emplace_back(1 << 20);

    // v4.push_back(1 << 20);
    v4.emplace_back(1 << 20);  // 这里匹配到的构造函数是size，意思是创建了一个数组长度是 1<<20
    // v4.push_back(vector<int>(1 << 20));

    return 0;
}
