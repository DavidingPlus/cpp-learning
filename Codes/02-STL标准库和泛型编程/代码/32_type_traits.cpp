#include <iostream>
#include <type_traits>
#include <typeinfo>
using namespace std;

template <typename Value_type>
inline void type_traits_output(const Value_type& val) {
    cout << "type traits for type: " << typeid(val).name() << endl;

    cout << "is_void: " << is_void<Value_type>::value << endl;
}

int main() {
    type_traits_output(double(2.0));

    return 0;
}
