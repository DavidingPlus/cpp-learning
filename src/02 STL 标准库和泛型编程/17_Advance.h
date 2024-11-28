#ifndef __ADVANCE__
#define __ADVANCE__

class myadvance
{
public:
    template <typename Iterator, typename Distance>
    inline Iterator &_advance(Iterator &iter, Distance n, std::random_access_iterator_tag)
    {
        iter += n;
        return iter;
    }

    template <typename Iterator, typename Distance>
    inline Iterator &_advance(Iterator &iter, Distance n, std::bidirectional_iterator_tag)
    {
        if (n >= 0)
            while (n--)
                ++iter;
        else
            while (n++)
                --iter;
        return iter;
    }

    template <typename Iterator, typename Distance>
    inline Iterator &_advance(Iterator &iter, Distance n, std::input_iterator_tag)
    {
        while (n--)
            ++iter;
        return iter;
    }

    template <typename Iterator, typename Distance>
    inline Iterator Advance(Iterator iter, Distance n)
    // 这里最好不传入引用类型，因为第一下面没有更改iter的值，不用担心实参形参的问题；
    // 第二，外部可能传入的是begin()和end()这类没有办法直接修改的迭代器
    // 我们在使用的时候都是声明了一个运动迭代器，他的初值是begin(),这样来操作的
    // 所以传入引用会出问题，最好传值，但是后面就可以传入引用了，因为我们是创建了一个新的迭代器对象
    {
        typedef typename std::iterator_traits<Iterator>::iterator_category Iterator_Category;
        return _advance(iter, n, Iterator_Category());
    }
};

#endif
