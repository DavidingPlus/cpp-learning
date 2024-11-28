#ifndef __DISTANCE__
#define __DISTANCE__

#include <iostream>
class mydistance
{
public:
    template <class Random_Iterator>
    inline
        typename std::iterator_traits<Random_Iterator>::difference_type
        _distance(Random_Iterator &first, Random_Iterator &last, random_access_iterator_tag)
    {
        return last - first;
    }

    template <class Input_Iterator>
    inline
        typename std::iterator_traits<Input_Iterator>::difference_type
        _distance(Input_Iterator &first, Input_Iterator &last, input_iterator_tag)
    {
        typename iterator_traits<Input_Iterator>::difference_type n = 0;
        for (; first != last; ++first, ++n)
            ;
        return n;
    }

    template <class Iterator>
    inline
        typename std::iterator_traits<Iterator>::difference_type
        Distance(Iterator first, Iterator last)
    // 这里最好不传入引用类型，因为第一下面没有更改iter的值，不用担心实参形参的问题；
    // 第二，外部可能传入的是begin()和end()这类没有办法直接修改的迭代器
    // 我们在使用的时候都是声明了一个运动迭代器，他的初值是begin(),这样来操作的
    // 所以传入引用会出问题，最好传值，但是后面就可以传入引用了，因为我们是创建了一个新的迭代器对象
    {
        // 问萃取机这个迭代器的类型
        typename iterator_traits<Iterator>::iterator_category Iterator_Category;
        return _distance(first, last, Iterator_Category);
    }
};

#endif
