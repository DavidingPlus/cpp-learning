#include <iostream>  //std::cin std::cout
#include <iterator>  //std::istream_iterator

int main() {
    double value1, value2;
    std::cout << "Please,insert two values: ";
    std::istream_iterator<double> eos;             // end-of-stream iterator
    std::istream_iterator<double> iter(std::cin);  // stdin iterator

    if (iter != eos)
        value1 = *iter;
    ++iter;
    if (iter != eos)
        value2 = *iter;

    std::cout << value1 << " * " << value2 << " == " << value1 * value2 << std::endl;

    return 0;
}
