#include <iostream>
using namespace std;
#include <tuple>
#include "29_tuple_print.h"

class stone
{
public:
    stone();
    stone(const double &len, const double &wid, const double &hei, const double &wei)
        : length(len), width(wid), height(hei), weight(wei) {}
    double getlength() const { return length; }
    double getwidth() const { return width; }
    double getheight() const { return height; }
    double getweight() const { return weight; }

private:
    double length;
    double width;
    double height;
    double weight;
};

inline ostream &
operator<<(ostream &os, const stone &s)
{
    os << "length: " << s.getlength()
       << " width: " << s.getwidth()
       << " height: " << s.getheight()
       << " weight: " << s.getweight();
    return os;
}

int main()
{
    stone s(1.2, 3.4, 5.6, 22.45);
    using Type = tuple<string, int, double, stone>;
    Type t{"hello", 1, 3.14, s};
    cout << t << endl;

    return 0;
}
