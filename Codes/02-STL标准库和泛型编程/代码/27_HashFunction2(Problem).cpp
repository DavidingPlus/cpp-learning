#include <iostream>
#include <unordered_set>
#include <functional>
#include <string>
#include "27_HashFunction.h"

using string = std::string;

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

// 放在std内表示在标准库std里面进行操作修改
namespace std
{
    template <>
    class hash<Customer>
    {
        size_t operator()(const Customer &c)
        {
            return HashFunction().hash_val(c.fname, c.lname, c.no);
        }
    };
}

int main()
{
    // 这个特化出问题了，还在找原因
    std::unordered_set<Customer> custset;
    custset.insert(Customer("Ace", "Hou", 1L));
    custset.insert(Customer("Sabri", "Hou", 2L));
    custset.insert(Customer("Stacy", "Chen", 3L));
    custset.insert(Customer("Mike", "Tseng", 4L));
    custset.insert(Customer("Paili", "Chen", 5L));
    custset.insert(Customer("Light", "Shiau", 6L));
    custset.insert(Customer("Shally", "Hwung", 7L));
    // 这个篮子个数会自己调整，一般都是质数
    // 当元素个数增加到等于篮子个数的时候重构，保证篮子个数大于元素个数!!!
    std::cout << "custset current bucket_count: " << custset.bucket_count() << std::endl; // 13

    for (int i = 0; i < custset.bucket_count(); ++i)
        std::cout << "bucket #" << i << " has " << custset.bucket_size(i) << " elements." << std::endl;

    return 0;
}
