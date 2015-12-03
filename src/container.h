template <class T> class container {
    public:
        container();
        container(const container<T>& another);
        virtual ~container();
        virtual container<T>& operator=(const container<T>& another);

        /** Number of elements in this container. */
        virtual t_index    size() const = 0;
        virtual    bool isEmpty() const = 0;
        virtual    void   clear()       = 0;
};

template <class T> container<T>::container() {
}

template <class T> container<T>::container(const container<T>& another) {
}

template <class T> container<T>::~container() {
}

template <class T> container<T>& container<T>::operator=(const container<T>& another) {
    return *this;
}
