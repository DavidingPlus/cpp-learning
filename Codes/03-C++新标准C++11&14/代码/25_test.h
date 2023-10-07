#ifndef _TEST_H_
#define _TEST_H_

#include <ctime>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <unordered_set>
#include <vector>
using namespace std;
#include "25_MyStrNoMove.h"
#include "25_Mystring.h"

namespace Test {
//--------------------------------------------------------
template <typename MyString>
void output_static_data(const MyString &str) {
    cout << typeid(str).name() << "--" << endl;
    cout << "CCtor= " << MyString::CCtor
         << " MCtor= " << MyString::MCtor
         << " CAsgn= " << MyString::CAsgn
         << " MAsgn= " << MyString::MAsgn
         << " Dtor= " << MyString::Dtor
         << " Ctor= " << MyString::Ctor
         << " DCtor= " << MyString::DCtor
         << endl;
}

// test_moveable
template <typename M, typename NM>
void test_moveable(M c1, NM c2, long &value) {
    char buf[10];

    // 测试 moveable
    cout << "\ntest, with moveable elements" << endl;
    typedef typename iterator_traits<typename M::iterator>::value_type V1type;
    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        snprintf(buf, 10, "%d", rand());
        auto ite = c1.end();
        c1.insert(ite, V1type(buf));
    }
    cout << "construction, milli-seconds : " << double(clock() - timeStart) / 1000 << endl;
    cout << "size()= " << c1.size() << endl;
    output_static_data(*(c1.begin()));

    timeStart = clock();
    M c11(c1);
    cout << "copy, milli-seconds : " << double(clock() - timeStart) / 1000 << endl;

    timeStart = clock();
    M c12(std::move(c1));
    cout << "move copy, milli-seconds : " << double(clock() - timeStart) / 1000 << endl;

    timeStart = clock();
    c11.swap(c12);
    cout << "swap, milli-seconds : " << double(clock() - timeStart) / 1000 << endl;

    // 测试 non-moveable
    cout << "\ntest, with non-moveable elements" << endl;
    typedef typename iterator_traits<typename NM::iterator>::value_type V2type;
    timeStart = clock();
    for (long i = 0; i < value; ++i) {
        snprintf(buf, 10, "%d", rand());
        auto ite = c2.end();
        c2.insert(ite, V2type(buf));
    }

    cout << "construction, milli-seconds : " << double(clock() - timeStart) / 1000 << endl;
    cout << "size()= " << c2.size() << endl;
    output_static_data(*(c2.begin()));

    timeStart = clock();
    NM c21(c2);
    cout << "copy, milli-seconds : " << double(clock() - timeStart) / 1000 << endl;

    timeStart = clock();
    NM c22(std::move(c2));
    cout << "move copy, milli-seconds : " << double(clock() - timeStart) / 1000 << endl;

    timeStart = clock();
    c21.swap(c22);
    cout << "swap, milli-seconds : " << double(clock() - timeStart) / 1000 << endl;
}
//--------------------------------------------------------

// 将标识位 清0
void clear() {
    Mystring::DCtor = 0;
    Mystring::Ctor = 0;
    Mystring::CCtor = 0;
    Mystring::CAsgn = 0;
    Mystring::MCtor = 0;
    Mystring::MAsgn = 0;
    Mystring::Dtor = 0;

    MyStrNoMove::DCtor = 0;
    MyStrNoMove::Ctor = 0;
    MyStrNoMove::CCtor = 0;
    MyStrNoMove::CAsgn = 0;
    MyStrNoMove::MCtor = 0;
    MyStrNoMove::MAsgn = 0;
    MyStrNoMove::Dtor = 0;
}

// test_vector
void test_vector(long &value) {
    cout << "\ntest_vector().......... \n";
    test_moveable(vector<Mystring>(), vector<MyStrNoMove>(), value);
    cout << endl;
}

// test_list
void test_list(long &value) {
    cout << "\ntest_list().......... \n";
    test_moveable(list<Mystring>(), list<MyStrNoMove>(), value);
    cout << endl;
}

// test_deque
void test_deque(long &value) {
    cout << "\ntest_deque().......... \n";
    test_moveable(deque<Mystring>(), deque<MyStrNoMove>(), value);
    cout << endl;
}

// test_multiset
void test_multiset(long &value) {
    cout << "\ntest_multiset().......... \n";
    test_moveable(multiset<Mystring>(), multiset<MyStrNoMove>(), value);
    cout << endl;
}

// test_unordered_multiset
// void test_unordered_multiset(long &value) {
//     cout << "\ntest_unordered_multiset().......... \n";
//     test_moveable(unordered_multiset<Mystring>(), unordered_multiset<MyStrNoMove>(), value);
//     cout << endl;
// }
}  // namespace Test

#endif
