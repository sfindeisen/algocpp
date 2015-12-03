/**
 * A dynamic (resizable) array. The first element always has the index 0.
 *
 * This implementation stores the elements in a cyclic buffer.
 */
template <class T> class array : public container<T> {
    public:
        array();
        array(const array<T>& another);
        virtual ~array();
        virtual array<T>& operator=(const array<T>& another);

        virtual T&   operator[](t_index index) const;

        virtual void    addFirst(T value);
        virtual void deleteFirst();
        virtual T&         first() const;

        virtual void    addLast(T value);
        virtual void deleteLast();
        virtual T&         last() const;

        /** Number of elements in this container. */
        virtual t_index    size() const;
        virtual    bool isEmpty() const;
        virtual    void   clear();

    protected:
        t_index physicalIndex(const t_index logicalIndex) const;

        void  resizeBuffer(const t_index newSize);
        void enlargeBuffer();
        void  shrinkBuffer();

    private:
        /** The buffer */
        T*  buffer;

        /** Length of the buffer (number of element slots). */
        t_index  bufferSize;

        /** Start of data in the buffer. */
        t_index  dataStart;

        /** Number of elements stored in the buffer. */
        t_index  dataLength;
};

template <class T> array<T>::array() : container<T>(), buffer(NULL), bufferSize(0), dataStart(0), dataLength(0) {
}

template <class T> array<T>::array(const array<T>& another) : container<T>(another) {
    this->buffer     = NULL;
    this->bufferSize = another.bufferSize;
    this->dataStart  = another.dataStart;
    this->dataLength = another.dataLength;

    if (another.buffer) {
        EBDS_NEW   (buffer, T[bufferSize]);
        EBDS_MEMCPY(buffer, another.buffer, (sizeof(T*) * bufferSize));
    }
}

template <class T> array<T>& array<T>::operator=(const array<T>& another) {
    container<T>::operator=(another);

    if (this != &another) {
        if (buffer) {
            EBDS_DELETE_ARRAY(buffer);
            buffer = NULL;
        }

        this->bufferSize = another.bufferSize;
        this->dataStart  = another.dataStart;
        this->dataLength = another.dataLength;

        if (another.buffer) {
            EBDS_NEW_ARRAY(buffer, T, bufferSize);
            EBDS_MEMCPY   (buffer, another.buffer, (sizeof(T*) * bufferSize));
        }
    }

    return *this;
}

template <class T> array<T>::~array() {
    if (buffer) {
        EBDS_DELETE_ARRAY(buffer);
        buffer = NULL;
    }
}

template <class T> inline t_index array<T>::size() const {
    return dataLength;
}

template <class T> inline bool array<T>::isEmpty() const {
    return (0 == dataLength);
}

template <class T> inline void array<T>::clear() {
    dataStart  = 0;
    dataLength = 0;
    shrinkBuffer();
}

template <class T> inline t_index array<T>::physicalIndex(t_index index) const {
    return ((dataStart + index) < bufferSize) ? (dataStart + index) : (dataStart + index - bufferSize);
}

/** Retrieves the value for index in range [0 .. dataLength-1] */
template <class T> T& array<T>::operator[](t_index index) const {
    if ((index < 0) || (dataLength <= index))
        EBDS_THROW_ARGS(array_index_out_of_range_exception, index);
    return buffer[physicalIndex(index)];
}

template <class T> void array<T>::addFirst(T value) {
    if (bufferSize <= dataLength)   // buffer full
        enlargeBuffer();
    if ((--dataStart) < 0)
        dataStart = bufferSize - 1;
    buffer[dataStart] = value;
    dataLength++;
}

template <class T> void array<T>::addLast(T value) {
    if (bufferSize <= dataLength)   // buffer full
        enlargeBuffer();
    const t_index physIndex = physicalIndex(dataLength++);
    buffer[physIndex] = value;
}

template <class T> T& array<T>::first() const {
    return operator[](0);
}

template <class T> T& array<T>::last() const {
    return operator[](dataLength - 1);
}

template <class T> void array<T>::deleteFirst() {
    if (0 == dataLength) {
        EBDS_THROW_ARGS(array_index_out_of_range_exception, 0);
    }

    if (0 == (--dataLength)) {
        dataStart = 0;
    } else {
        dataStart++;
        if (bufferSize <= dataStart)
            dataStart = 0;
    }
    shrinkBuffer();
}

template <class T> void array<T>::deleteLast() {
    if (0 == dataLength)
        EBDS_THROW_ARGS(array_index_out_of_range_exception, 0);
    if (0 == (--dataLength))
        dataStart = 0;
    shrinkBuffer();
}

///////////////////////////////////////////////////////////
// Cyclic buffer implementation
///////////////////////////////////////////////////////////

/** newSize must be big enough! */
template <class T> void array<T>::resizeBuffer(const t_index newSize) {
    const t_index oldSize = bufferSize;
    T*          newBuffer = NULL;
    EBDS_NEW_ARRAY(newBuffer, T, newSize);

    if (1 <= dataLength) {
        if (dataStart + dataLength <= bufferSize) {
            EBDS_MEMCPY(newBuffer, buffer + dataStart, sizeof(T*) * dataLength);
        } else {
            // There is a buffer wrap to eliminate
            t_index suffixLen = oldSize - dataStart;

            EBDS_MEMCPY(newBuffer,             buffer + dataStart, sizeof(T*) * suffixLen);
            EBDS_MEMCPY(newBuffer + suffixLen, buffer,             sizeof(T*) * (dataLength - suffixLen));
        }
    }

    if (buffer) {
        EBDS_DELETE_ARRAY(buffer);
    }

    this->buffer     = newBuffer;
    this->bufferSize = newSize;
    this->dataStart  = 0;
}

/** After enlarge operation there is no buffer wrap. */
template <class T> void array<T>::enlargeBuffer() {
    if (1 <= bufferSize)
        resizeBuffer(bufferSize * 2);
    else
        resizeBuffer(10);
}

template <class T> void array<T>::shrinkBuffer() {
    while ((bufferSize >= 10) && (bufferSize > (4 * dataLength))) {
        // TODO wyrzucic petle, od razu znalezc najlepsza wielkosc
        resizeBuffer(bufferSize / 2);
    }
}
