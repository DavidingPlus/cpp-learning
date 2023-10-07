#include <iostream>
using namespace std;
#include <unordered_set>
#include <functional>
#include <string>
#include "27_HashFunction.h"

class Customer
{
public:
    Customer();
    Customer(string _fname, string _lname, long _no) : fname(_fname), lname(_lname), no(_no) {}

    bool operator==(const Customer &c) const
    {
        return this->fname == c.fname && this->lname == c.lname && this->no == c.no;
    }

public:
    string fname;
    string lname;
    long no;
};

class CustomerHash
{
public:
    size_t operator()(const Customer &c) const
    {
        return HashFunction().hash_val(c.fname, c.lname, c.no);
    }
};

// size_t customer_hash_func(const Customer &c)
// {
//     // 第一种思路就是这个类里面简单类型的hashcode全部相加
//     // 但是这么做的话设计者认为比较天真，没办法达到非常乱的结构
//     return HashFunction().hash_val(c.fname, c.lname, c.no);
// }

int main()
{
    // using function_pointer = size_t (*)(const Customer &); // 定义函数指针
    // unordered_set<Customer, function_pointer> custset2;    // 第一个参数篮子大小

    // cout << CustomerHash()(Customer("Ace", "Hou", 1L)) << endl;

    unordered_set<Customer, CustomerHash> custset;
    custset.insert(Customer("Ace", "Hou", 1L));
    custset.insert(Customer("Sabri", "Hou", 2L));
    custset.insert(Customer("Stacy", "Chen", 3L));
    custset.insert(Customer("Mike", "Tseng", 4L));
    custset.insert(Customer("Paili", "Chen", 5L));
    custset.insert(Customer("Light", "Shiau", 6L));
    custset.insert(Customer("Shally", "Hwung", 7L));
    // 这个篮子个数会自己调整，一般都是质数
    // 当元素个数增加到等于篮子个数的时候重构，保证篮子个数大于元素个数!!!
    cout << "custset current bucket_count: " << custset.bucket_count() << endl; // 13

    for (int i = 0; i < custset.bucket_count(); ++i)
        cout << "bucket #" << i << " has " << custset.bucket_size(i) << " elements." << endl;

    return 0;
}
