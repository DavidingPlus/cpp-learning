#include <iostream>
using namespace std;
#include <set>
#include <string>

namespace Test {

class Person {
public:
    Person() = default;
    Person(string firstname, string lastname)
        : _firstname(firstname), _lastname(lastname) {}

public:
    string _firstname;
    string _lastname;
};

ostream&
operator<<(ostream& os, const Person& p) {
    os << '(' << p._firstname << ',' << p._lastname << ')';
    return os;
}

auto CmpPerson = [](const Person& p1, const Person& p2) {
    return (p1._lastname < p2._lastname) ||
           (p1._lastname == p2._lastname) && (p1._firstname < p2._firstname);
};

struct Cmp
    : binary_function<Person, Person, bool> {
    // 被比较的不能被修改，编译器非常灵敏，需要加上const
    bool operator()(const Person& p1, const Person& p2) const {
        return (p1._lastname < p2._lastname) ||
               (p1._lastname == p2._lastname) && (p1._firstname < p2._firstname);
    }
} cmps;

template <typename Container>
inline void print(const Container& con) {
    for (auto val : con)
        cout << val << ' ';
    cout << endl;
}

}  // namespace Test

using namespace Test;
int main() {
    Person p1("John", "Wall");
    Person p2("David", "Paul");
    Person p3("Steve", "Paul");

    // 这里需要如果括号里不给CmpPerson参数，会调用CmpPerson的默认构造函数，不幸的是没有默认构造，所以需要给出
    set<Person, decltype(CmpPerson)> s({p1, p2, p3}, CmpPerson);
    print(s);

    return 0;
}
