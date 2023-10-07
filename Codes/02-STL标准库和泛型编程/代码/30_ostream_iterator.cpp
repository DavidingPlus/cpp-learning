#include <algorithm>  //std::copy
#include <iostream>   //std::cout
#include <iterator>   //std::ostream_iterator
#include <vector>     //std::vector

int main() {
    std::vector<int> v;
    for (int i = 0; i < 10; ++i) v.push_back(i * 10);

    std::ostream_iterator<int> out_it(std::cout, ",");
    std::copy(v.begin(), v.end(), out_it);
    std::cout << std::endl;

    return 0;
}
