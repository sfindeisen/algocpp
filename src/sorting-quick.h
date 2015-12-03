inline void swap(long i1, long i2) {
    long n1 = edges[i1].n1;
    long n2 = edges[i1].n2;

    edges[i1].n1 = edges[i2].n1;
    edges[i1].n2 = edges[i2].n2;
    edges[i2].n1 = n1;
    edges[i2].n2 = n2;
}

/** [left..right]: obustronnie domkniety przedzial indeksow */
void qsort(long left, long right) {
    if (left < right) {
        swap(left, (left + right) / 2);

        long m = t[left];
        long k = left;

        for (long i = left + 1; i <= right; ++i) {
            if (t[i] <= m)
                swap(i, ++k);
        }

        swap (left, k);
        qsort(left, k - 1);
        qsort(k + 1, right);
    }
}
