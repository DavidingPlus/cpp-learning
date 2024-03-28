    /**
     * @brief 定义前向迭代器。迭代器是容器的内部类（模板）
     * 
     */
    template <typename iterator>
    class base_list_iterator : public random_access_iterator_tag {
    public:
        // 从容器引入必要的类型
        // 原则上，迭代器至少要包含以下四种类型
        using value_type = container_type::value_type;
        using pointer = container_type::pointer;
        using reference = container_type::reference;
        using difference_type = container_type::difference_type;

        using iterator_category = random_access_iterator_tag;

    private:
        using dataptr_type = container_type::dataptr_type;

        dataptr_type p; // 被包装的指针，指向容器的内部存储结构

        // 内部函数，用于指针的前移或后移
        void _next(dataptr_type& p) { p = p->next; }
        void _prev(dataptr_type& p) { p = p->prior; }
        
        // 判断指针是否移到链表外
        constexpr bool _is_exceed(dataptr_type p) const { return p == nullptr; }
        constexpr bool _is_next_exceed(dataptr_type p) const { return p->next == nullptr; }
        constexpr bool _is_prev_exceed(dataptr_type p) const { return p->prior == nullptr; }

    public:
        base_list_iterator(dataptr_type _p = nullptr) : p(_p) {}

        /**
         * @brief 向前移动内部指针方法
         * 
         * @param n 移动距离。如果是负数，则向后移动
         * @return constexpr iterator& 迭代器本身
         */
        constexpr iterator& advance(difference_type n = 1) try {
            if (n >= 0) {
                for (auto i = 0; i < n and not _is_exceed(p); ++i) _next(p);
            } else {
                for (auto i = 0; i < -n and not _is_exceed(p); ++i) _prev(p);
            }
            if (p == nullptr)
                throw std::out_of_range(std::format("advance distance {} causes out of range", n));
        
            return *this;
        } catch (std::out_of_range& e) {
            std::cout << e.what() << std::endl;
            exit(1);
        }

        /**
         * @brief 计算this迭代器和指定迭代器之间的距离
         * 
         * @param itr 指定的迭代器
         * @return constexpr difference_type 两个迭代器之间的距离。可能为负值
         */
        constexpr difference_type distance(iterator const &itr) const try {
            iterator tmp{p}; // 生成一个临时迭代器。因为distance方式是const方法，所以应该这么做。
            difference_type n = 0;

            // 先向后找，看看是否能遇到itr.p
            for (; tmp.p != itr.p and not tmp._is_next_exceed(tmp.p); tmp._next(tmp.p), ++n);
            if (tmp.p == itr.p) return n;

            // 再向后找
            for (n = 0, tmp.p = p; tmp.p != itr.p and not tmp._is_prev_exceed(tmp.p); tmp._prev(tmp.p), --n);
            if (tmp.p == itr.p) return n;

            // 未找到，抛出异常
            throw std::out_of_range("distance: cannot evaluate the distance");
        } catch (std::out_of_range &e) {
            std::cout << e.what() << std::endl;
            exit(1);
        }

        // 生成一个指向当前项后项的迭代器
        constexpr iterator next() const {
            auto itr{*this};
            _next(itr.p);
            return itr;
        }

        // 生成一个指向当前项前项的迭代器
        constexpr iterator prev() const {
            auto itr{*this};
            _prev(itr.p);
            return itr;
        }
    
        // 重载的!=运算符
        constexpr bool operator!=(iterator const& itr) const {
            return p != itr.p;
        }

        // 重载的++运算符：前缀
        constexpr iterator& operator++() {
            return advance();
        }

        // 重载的++运算符：后缀
        constexpr iterator operator++(int) {
            auto t = p;
            advance();
            return iterator(t);
        }

        // 重载的--运算符：前缀
        constexpr iterator& operator--() {
            return advance(-1);
        }

        // 重载的--运算符：后缀
        constexpr iterator operator--(int) {
            auto t = p;
            advance(-1);
            return iterator(t);
        }

        // 重载的*运算符。注意：返回数据的左值引用
        constexpr reference operator*() const {
            return p->data;
        }

        // 重载的+运算符，是迭代器具备随机访问能力
        constexpr iterator operator+(difference_type n) const {
            return iterator(p).advance(n);
        }

        // 重载的-运算符，是迭代器具备随机访问能力
        constexpr iterator operator-(difference_type n) const {
            return iterator(p).advance(-n);
        }
    };