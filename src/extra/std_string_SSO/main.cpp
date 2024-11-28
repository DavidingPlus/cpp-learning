#include <iostream>
#include <string>

int main()
{
    std::string a{"one"};
    auto b = a;

    std::string c{"twooooooooooooooooooooooooooooooooooooooooooooo"};

    printf("a address: %p, c_str address: %p\n", &a, a.c_str());
    printf("b address: %p, c_str address: %p\n", &b, b.c_str());
    printf("c address: %p, c_str address: %p\n", &c, c.c_str());

    return 0;
}
