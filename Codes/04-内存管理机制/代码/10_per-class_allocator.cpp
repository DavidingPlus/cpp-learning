#include <iostream>
using namespace std;

class Screen
{
public:
    Screen() = default;
    Screen(int x) : _i(x){};
    int get() const { return _i; }

    inline void *operator new(size_t);
    inline void operator delete(void *, size_t);

private:
    Screen *next; // 这种设计会引发一个疑问，就是多消耗了一个指针的内存空间，但是可以抹除数组元素之间的cookie，只在数组头尾放cookie
    static Screen *freeStore;
    static const int screenChunk;

private:
    int _i;
};
Screen *Screen::freeStore = nullptr;
const int Screen::screenChunk = 24;

void *Screen::operator new(size_t size)
{
    Screen *p;
    if (!freeStore)
    {
        // linked list 是空的，所以攫取一大塊 memory
        // 以下呼叫的是 global operator new
        size_t chunk = screenChunk * size; // 这是乘法，计算需要的字节数
        freeStore = p =
            reinterpret_cast<Screen *>(new char[chunk]);
        // 將分配得來的一大塊 memory 當做 linked list 般小塊小塊串接起來
        for (; p != &freeStore[screenChunk - 1]; ++p)
            p->next = p + 1;
        p->next = 0;
    }
    p = freeStore;
    freeStore = freeStore->next;
    return p;
}

//! void Screen::operator delete(void *p)		//(1)
void Screen::operator delete(void *p, size_t) //(2)二擇一
{
    // 將 deleted object 收回插入 free list 前端
    (static_cast<Screen *>(p))->next = freeStore;
    freeStore = static_cast<Screen *>(p);
}

//-------------
void test_per_class_allocator_1()
{
    cout << "test_per_class_allocator_1().......... \n";

    cout << sizeof(Screen) << endl; // 8

    size_t const N = 100;
    Screen *p[N];

    for (int i = 0; i < N; ++i)
        p[i] = new Screen(i);

    // 輸出前 10 個 pointers, 用以比較其間隔
    for (int i = 0; i < 10; ++i)
        cout << p[i] << endl;

    for (int i = 0; i < N; ++i)
        delete p[i];
}

void test_global_allocator()
{
    cout << "test_global_allocator().......... \n";

    cout << sizeof(Screen) << endl; // 8

    size_t const N = 100;
    Screen *p[N];

    for (int i = 0; i < N; ++i)
        p[i] = ::new Screen(i);

    // 輸出前 10 個 pointers, 用以比較其間隔
    for (int i = 0; i < 10; ++i)
        cout << p[i] << endl;

    for (int i = 0; i < N; ++i)
        ::delete p[i];
}

int main()
{
    test_per_class_allocator_1();
    cout << endl
         << endl;
    test_global_allocator();

    return 0;
}
