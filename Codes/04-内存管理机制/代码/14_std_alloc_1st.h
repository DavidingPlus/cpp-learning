#ifndef _STD_ALLOC_1ST_H_
#define _STD_ALLOC_1ST_H_

#define __THROW_BAD_ALLOC            \
    cerr << "out of memory" << endl; \
    exit(1)
//----------------------------------------------
// 第1級配置器。
//----------------------------------------------
template <int inst>
class __malloc_alloc_template {
private:
    static void *oom_malloc(size_t);
    static void *oom_realloc(void *, size_t);
    static void (*__malloc_alloc_oom_handler)();

public:
    static void *allocate(size_t n) {
        void *result = malloc(n);  // 直接使用 malloc()
        if (0 == result)
            result = oom_malloc(n);
        return result;
    }
    static void deallocate(void *p, size_t /* n */) {
        free(p);  // 直接使用 free()
    }
    static void *reallocate(void *p, size_t /* old_sz */, size_t new_sz) {
        void *result = realloc(p, new_sz);  // 直接使用 realloc()
        if (0 == result)
            result = oom_realloc(p, new_sz);
        return result;
    }
    static void (*set_malloc_handler(void (*f)()))() {  // 類似 C++ 的 set_new_handler().
        void (*old)() = __malloc_alloc_oom_handler;
        __malloc_alloc_oom_handler = f;
        return (old);
    }
};
//----------------------------------------------
template <int inst>
void (*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;

template <int inst>
void *__malloc_alloc_template<inst>::oom_malloc(size_t n) {
    void (*my_malloc_handler)();
    void *result;

    for (;;) {  // 不斷嘗試釋放、配置、再釋放、再配置…
        my_malloc_handler = __malloc_alloc_oom_handler;
        if (0 == my_malloc_handler) {
            __THROW_BAD_ALLOC;
        }
        (*my_malloc_handler)();  // 呼叫處理常式，企圖釋放記憶體
        result = malloc(n);      // 再次嘗試配置記憶體
        if (result)
            return (result);
    }
}

template <int inst>
void *__malloc_alloc_template<inst>::oom_realloc(void *p, size_t n) {
    void (*my_malloc_handler)();
    void *result;

    for (;;) {  // 不斷嘗試釋放、配置、再釋放、再配置…
        my_malloc_handler = __malloc_alloc_oom_handler;
        if (0 == my_malloc_handler) {
            __THROW_BAD_ALLOC;
        }
        (*my_malloc_handler)();  // 呼叫處理常式，企圖釋放記憶體。
        result = realloc(p, n);  // 再次嘗試配置記憶體。
        if (result)
            return (result);
    }
}
//----------------------------------------------

typedef __malloc_alloc_template<0> malloc_alloc;

template <class T, class Alloc>
class simple_alloc {
public:
    static T *allocate(size_t n) {
        return 0 == n ? 0 : (T *)Alloc::allocate(n * sizeof(T));
    }
    static T *allocate(void) {
        return (T *)Alloc::allocate(sizeof(T));
    }
    static void deallocate(T *p, size_t n) {
        if (0 != n)
            Alloc::deallocate(p, n * sizeof(T));
    }
    static void deallocate(T *p) {
        Alloc::deallocate(p, sizeof(T));
    }
};

#endif