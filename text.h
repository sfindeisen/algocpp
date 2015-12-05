char tekst[MaxN + 3];
long ptab [MaxN + 3];           // KMP "P array": ptab[i] is max k<i : there is prefix/suffix of length k in tekst[1..i]

/** Tablica P; tekst must be 1-based string! (tekst[1], tekst[2]...) */
void tablicaP() {
    long k  = 0;
    ptab[0] = 0;
    ptab[1] = 0;

    for (long i = 2; i <= N; ++i) {
        const char c = tekst[i];
        while (k && (tekst[k+1] != c))
            k = ptab[k];
        if (tekst[k+1] == c)
            ++k;
        ptab[i] = k;
    }
}

/** Tablica P: wersja dla napisow 1 za 2-gim w tablicy (bez '\0's); ii is word number */
void tablicaP(const long ii) {
    const long offset = tind[ii];           // poczatki slow
    const long len    = tlen[ii];           // dlugosci slow

    if (0 == len)
        return;

          long k      = 0;
    parr[offset]      = 0;    // prefix of length 1: P is 0

    for (long i = 1; i < len; ++i) {
        const char c = tkst[offset + i];
        while (k && (tkst[offset + k] != c))
            k = parr[offset + k - 1];
        if (tkst[offset + k] == c)
            ++k;
        parr[offset + i] = k;
    }
}
