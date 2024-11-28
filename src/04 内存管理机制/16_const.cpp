#include <iostream>
using namespace std;

class Fuck {
public:
    void fuck() const {
        cout << "const version" << endl;
    }

    void fuck() {
        cout << "non-const version" << endl;
    }
};

void test() {
    const Fuck f1;
    f1.fuck();

    Fuck f2;
    f2.fuck();
}

int main() {
    test();

    return 0;
}
