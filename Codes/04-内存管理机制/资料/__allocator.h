#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include <iostream>
using namespace std;

class __allocator {
private:
    struct obj {
        struct obj *next;  // embedded pointer
    };

public:
    void *allocate(size_t);
    void deallocate(void *, size_t);
    void check();

private:
    obj *freeStore = nullptr;
    const int CHUNK = 5;  // 小一點方便觀察
};

void *__allocator::allocate(size_t size) {
    obj *p;

    if (!freeStore) {
        // linked list 是空的，所以攫取一大塊 memory
        size_t chunk = CHUNK * size;
        freeStore = p = (obj *)malloc(chunk);

        // cout << "empty. malloc: " << chunk << "  " << p << endl;

        // 將分配得來的一大塊當做 linked list 般小塊小塊串接起來
        for (int i = 0; i < (CHUNK - 1); ++i) {  // 沒寫很漂亮, 不是重點無所謂.
            p->next = (obj *)((char *)p + size);
            p = p->next;
        }
        p->next = nullptr;  // last
    }
    p = freeStore;
    freeStore = freeStore->next;

    // cout << "p= " << p << "  freeStore= " << freeStore << endl;

    return p;
}
void __allocator::deallocate(void *p, size_t) {
    // 將 deleted object 收回插入 free list 前端
    ((obj *)p)->next = freeStore;
    freeStore = (obj *)p;
}
void __allocator::check() {
    obj *p = freeStore;
    int count = 0;

    while (p) {
        cout << p << endl;
        p = p->next;
        count++;
    }
    cout << count << endl;
}

#endif
