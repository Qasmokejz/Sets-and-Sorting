#include "batcher.h"

void comparator(Stats *stats, uint32_t *A, int x, int y) {
    if (cmp(stats, A[x], A[y]) > 0) {
        swap(stats, &A[x], &A[y]);
    }
}

uint32_t bit_len(uint32_t n) {
    uint32_t bit = 0;
    while (n > 0) {
        n >>= 1;
        bit++;
    }
    return bit;
}
void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    if (n == 0) {
        return;
    }
    uint32_t N = n;
    uint32_t t = bit_len(N);
    uint32_t p = 1 << (t - 1);
    uint32_t q, r, d;
    while (p > 0) {
        q = 1 << (t - 1);
        r = 0;
        d = p;

        while (d > 0) {
            for (uint32_t i = 0; i < N - d; i++) {
                if ((i & p) == r) {
                    comparator(stats, A, i, i + d);
                }
            }
            d = q - p;
            q >>= 1;
            r = p;
        }
        p >>= 1;
    }
}
