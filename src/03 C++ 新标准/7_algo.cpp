#include <iostream>
using namespace std;
#include <vector>

class Algorithm
{
public:
    // 如果传入的是一个容器
    template <typename Container>
    inline typename iterator_traits<typename Container::iterator>::value_type
    _min(const Container &con)
    {
        return Min(con.begin(), con.end());
    }

    template <typename Container>
    inline typename iterator_traits<typename Container::iterator>::value_type
    _max(const Container &con)
    {
        return Max(con.begin(), con.end());
    }

    // 如果传入的是一个initializer_list<>
    template <typename Value_Type>
    inline Value_Type
    _min(const initializer_list<Value_Type> &init_list)
    {
        return Min(init_list.begin(), init_list.end());
    }

    template <typename Value_Type>
    inline Value_Type
    _max(const initializer_list<Value_Type> &init_list)
    {
        return Max(init_list.begin(), init_list.end());
    }

private:
    template <typename Input_Iterator>
    inline typename iterator_traits<Input_Iterator>::value_type
    Min(Input_Iterator first, Input_Iterator last)
    {
        auto Min = *first;
        for (; first != last; ++first)
            Min = Min <= *first ? Min : *first;
        return Min;
    }

    template <typename Input_Iterator>
    inline typename iterator_traits<Input_Iterator>::value_type
    Max(Input_Iterator first, Input_Iterator last)
    {
        auto Max = *first;
        for (; first != last; ++first)
            Max = Max >= *first ? Max : *first;
        return Max;
    }
};

int main()
{
    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8};
    initializer_list<int> p{1, 2, 3, 4, 5, 6, 7, 8}; // 内部包含了一个array
    cout << Algorithm()._min(v) << endl;
    cout << Algorithm()._max(p) << endl;
    cout << Algorithm()._min({1, 2, 3, 4, 5, 6, 7, 8}) << endl;
    cout << Algorithm()._max({1, 2, 3, 4, 5, 6, 7, 8}) << endl;

    return 0;
}
