inline long heap_value(long index) {
    return (nodes[nodeHeap[index]].predList.itemCount + nodes[nodeHeap[index]].succList.itemCount);
}

inline void heap_swap(long i, long j) {
    const long tmp = nodeHeap[i];
    nodeHeap[i] = nodeHeap[j];
    nodeHeap[j] = tmp;
}

/** bigger first */
void heap_up(long current) {
    long parent = 0;
    while ((2 <= current) && (heap_value(current) > heap_value(parent=(current/2)))) {
        heap_swap(current, parent);
        current = parent;
    }
}

/** bigger first */
void heap_down(long current) {
    const long sz    = heapPtr;
          long child = 0;

    while (current <= sz) {
        child = 2 * current;

        if ((child <  sz) && (heap_value(child+1) > heap_value(child)))
            child++;
        if ((child <= sz) && (heap_value(child) > heap_value(current))) {
            heap_swap(current, child);
            current = child;
        } else
            break;
    }
}

inline long heap_top() {
    return nodeHeap[1];
}

long heap_pop() {
    const long topv = heap_top();

    if (2 <= heapPtr) {
        nodeHeap[1] = nodeHeap[heapPtr--];
        heap_down(1);
    } else
        --heapPtr;

    return topv;
}

void heap_push(long nn) {
    nodeHeap[++heapPtr] = nn;
    heap_up(heapPtr);
}

/***********************************************************************/

template <class T> void push(T elem) {
    data.addLast(elem);
    upheap(data.size());
}

template <class T> T pop() {
    T result(data.first());      // if there are no elements, an exception will be thrown

    if (2 <= data.size()) {
        data[0] = data.last();
        data.deleteLast();
        downheap(1);
    } else {
        // This is the only element
        data.clear();
    }

    return result;
}

template <class T> T& top() const {
    // ALGO_TRACE;
    return data.first();
}

template <class T> void swap(t_index i, t_index j) {
    // ALGO_TRACE;
    T tmp(data[i-1]);
    data[i-1] = data[j-1];
    data[j-1] = tmp;
}

template <class T> void upheap(t_index current) {
    // ALGO_TRACE;
    t_index parent = 0;
    while ((2 <= current) && (data[current-1] < data[(parent=(current/2))-1])) {
        swap(current, parent);
        current = parent;
    }
}

template <class T> void downheap(t_index current) {
    // ALGO_TRACE;
    const t_index    sz = data.size();
          t_index child = 0;

    while (current <= sz) {
        child = 2 * current;
        if ((child <  sz) && (data[child] < data[child-1]))
            child++;
        if ((child <= sz) && (data[child-1] < data[current-1])) {
            swap(current, child);
            current = child;
        } else
            break;
    }
}

template <class T> inline t_index size() const {
    return data.size();
}

template <class T> inline bool isEmpty() const {
    return (data.isEmpty());
}

template <class T> inline void clear() {
    data.clear();
}
