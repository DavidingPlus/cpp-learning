#include <iostream>
using namespace std;

struct Foo
{
    void method(void);
};

template <class T>
class shared_ptr
{
public:
    shared_ptr(T *p) : _px(p) {}

    T &operator*() const
    {
        return *(this->_px);
    }

    T *operator->() const
    {
        return this->_px;
    }

private:
    T *_px;
};

int main()
{
    shared_ptr<Foo> sp(new Foo);
    Foo f(*sp);
    sp->method();

    return 0;
}
