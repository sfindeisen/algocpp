/** doubly linked list insert (at the end) */
void double_list_insert_last(TDoubleLinkedList& dl, const long item) {
    neighbours[item].prev = dl.lastItem;
    neighbours[item].next = 0;

    if (dl.lastItem)
        neighbours[dl.lastItem].next = item;
    else
        dl.firstItem = item;

    dl.lastItem = item;
    dl.itemCount++;
}

void double_list_delete(TDoubleLinkedList& dl, const long item) {
    const long itemPrev = neighbours[item].prev;
    const long itemNext = neighbours[item].next;

    if (itemPrev)
        neighbours[itemPrev].next = itemNext;
    else
        dl.firstItem = itemNext;

    if (itemNext)
        neighbours[itemNext].prev = itemPrev;
    else
        dl.lastItem = itemPrev;

    neighbours[item].next = 0;
    neighbours[item].prev = 0;
    dl.itemCount--;
}

void double_list_clear(TDoubleLinkedList& dl) {
    long p2 = dl.firstItem;

    while (p2) {
        const long p1 = neighbours[p2].next;
        neighbours[p2].prev = 0;
        neighbours[p2].next = 0;
        p2 = p1;
    }

    dl.firstItem = 0;
    dl. lastItem = 0;
    dl.itemCount = 0;
}
