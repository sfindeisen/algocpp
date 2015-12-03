#include <iostream>
#include <cstring>

const int MaxN = 100;

int primes [MaxN + 1];
int primes2[MaxN + 1];

using namespace std;

int main() {
    memset(primes,  0, sizeof(primes));
    memset(primes2, 0, sizeof(primes2));

    primes [0] = 2;
    primes2[0] = primes[0] * primes[0];
    primes [1] = 3;
    primes2[1] = primes[1] * primes[1];
    int pcount = 2;

    cerr << "0 => " << 2 << std::endl;
    cerr << "1 => " << 3 << std::endl;

    for (int candidate = primes[1] + 2; (pcount < MaxN); candidate += 2) {
        bool ok = true;

        for (int j = 0; ok && (j < pcount) && (primes2[j] <= candidate); ++j) {
            if (0 == (candidate % primes[j]))
                ok = false;
        }

        if (ok) {
            primes [pcount] = candidate;
            primes2[pcount] = candidate * candidate;
            // cerr << pcount << " => " << candidate << std::endl;
            cerr << candidate << ", ";
            ++pcount;
        }
    }
}
