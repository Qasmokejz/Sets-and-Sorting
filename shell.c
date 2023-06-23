#include "shell.h"

#include "gaps.h"
#include "stats.h"

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (int k = 0; k < GAPS; k++) {
        uint32_t temp, j;
        uint32_t gap = gaps[k];
        for (uint32_t i = gap; i < n; i++) {
            j = i;
            temp = move(stats, A[i]);
            while (j >= gap && cmp(stats, temp, A[j - gap]) < 0) {
                A[j] = move(stats, A[j - gap]);
                j -= gap;
            }
            A[j] = move(stats, temp);
        }
    }
}
