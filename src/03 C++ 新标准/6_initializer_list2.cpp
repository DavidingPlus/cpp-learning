#include <iostream>
using namespace std;
#include <initializer_list>
#include <string>
#include <vector>

class Algorithm {
public:
    // 传入的是一个initializer_list<>
    template <typename Value_Type>
    inline Value_Type
    _min(const initializer_list<Value_Type> &init_list) {
        return Min(init_list.begin(), init_list.end());
    }

    template <typename Value_Type>
    inline Value_Type
    _max(const initializer_list<Value_Type> &init_list) {
        return Max(init_list.begin(), init_list.end());
    }

private:
    template <typename Input_Iterator>
    inline typename iterator_traits<Input_Iterator>::value_type
    Min(Input_Iterator first, Input_Iterator last) {
        auto Min = *first;
        for (; first != last; ++first)
            Min = Min <= *first ? Min : *first;
        return Min;
    }

    template <typename Input_Iterator>
    inline typename iterator_traits<Input_Iterator>::value_type
    Max(Input_Iterator first, Input_Iterator last) {
        auto Max = *first;
        for (; first != last; ++first)
            Max = Max >= *first ? Max : *first;
        return Max;
    }
};

template <typename Container>
inline void print(const Container &con) {
    for (auto val : con)
        cout << val << ' ';
    cout << endl;
}

int main() {
    vector<int> v1{2, 5, 7, 13, 69, 83, 50};
    vector<int> v2({2, 5, 7, 13, 69, 83, 50});
    vector<int> v3;
    v3 = {2, 5, 7, 13, 69, 83, 50};
    v3.insert(v3.begin() + 2, {0, 1, 2, 3, 4});
    print(v3);

    cout << Algorithm()._max({54, 16, 48, 5}) << endl;
    cout << Algorithm()._min({string("Ace"), string("Hello"), string("Fuck"), string("Zion")}) << endl;

    return 0;
}
