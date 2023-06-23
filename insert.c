#include "insert.h"

#include "stats.h"

void insertion_sort(Stats *stats, uint32_t *arr, uint32_t length) {
    uint32_t j, k, temp;
    for (k = 1; k < length; k++) {
        j = k;
        temp = move(stats, arr[k]);
        //temp = arr[k];
        while ((j > 0) && (cmp(stats, temp, arr[j - 1]) < 0)) {
            arr[j] = move(stats, arr[j - 1]);
            j--;
        }
        arr[j] = move(stats, temp);
        //arr[j] = temp;
    }
}
