#include "batcher.h"
#include "gaps.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_lst(uint32_t *pointer, int size, int elements) {
    /*prints randint array*/
    if (elements) {
        int last = 0;
        for (int i = 0; i < size; i++) {
            last = 0;
            printf("%13" PRIu32, pointer[i]);
            if (i + 1 == elements) {
                break;
            }
            if ((i + 1) != 0 && (i + 1) % 5 == 0) {
                printf("\n");
                last = 1;
            }
        }
        if (!last) {
            printf("\n");
        }
    }
}
void set_lst(uint32_t *pointer, int size) {
    /*sets/resets randint array*/
    for (int i = 0; i < size; i++) {
        uint32_t randint = random();
        randint &= 0x3FFFFFFF;
        pointer[i] = randint;
    }
}

void make_lst(uint32_t *lst1, uint32_t *lst2, int size) {
    /*copies lst1 into lst2*/
    for (int i = 0; i < size; i++) {
        lst2[i] = lst1[i];
    }
}

int main(int argc, char *argv[]) {
    int SEED = 13371453; // random seed
    int SIZE = 100; // array size
    int ELEMENTS = 100; // print number of elements
    /* sorts: ihsqb*/
    Set sorts = set_empty(); // 8-bits, bitwise represented: 000ihsqb
    int opt_H = 0;

    int option;

    while ((option = getopt(argc, argv, "aihsqbr:n:p:H")) != -1) {
        switch (option) {
        case 'a': sorts = set_universal(); break;
        case 'i': sorts = set_insert(sorts, 4); break;
        case 'h': sorts = set_insert(sorts, 3); break;
        case 's': sorts = set_insert(sorts, 2); break;
        case 'q': sorts = set_insert(sorts, 1); break;
        case 'b': sorts = set_insert(sorts, 0); break;
        case 'r': SEED = atoi(optarg); break;
        case 'n': SIZE = atoi(optarg); break;
        case 'p': ELEMENTS = atoi(optarg); break;
        case 'H': opt_H = 1; break;
        default: opt_H = 1; break;
        }
    }
    srandom(SEED);
    if (opt_H || !sorts) {
        printf("SYNOPSIS\n   A collection of comparison-based sorting algorithms.\n\nUSAGE\n   "
               "./sorting-arm [-Hahbsqi] [-n length] [-p elements] [-r seed]\n\nOPTIONS\n   -H     "
               "         Display program help and usage.\n   -a              Enable all sorts.\n   "
               "-h              Enable Heap Sort.\n   -b              Enable Batcher Sort.\n   -s  "
               "            Enable Shell Sort.\n   -q              Enable Quick Sort.\n   -i       "
               "       Enable Insertion Sort.\n   -n length       Specify number of array elements "
               "(default: 100).\n   -p elements     Specify number of elements to print (default: "
               "100).\n   -r seed         Specify random seed (default: 13371453).\n");
    } else {

        /* allocating mem for array*/
        uint32_t *lst = malloc(SIZE * 4); // uint32_t is 4 bytes
        uint32_t *arr = malloc(SIZE * 4);
        /*populating array*/
        set_lst(lst, SIZE);
        Stats stat; //declare stat

        if (set_member(sorts, 4)) { // Insertion sort
            reset(&stat);
            make_lst(lst, arr, SIZE);
            insertion_sort(&stat, arr, SIZE);
            print_stats(&stat, "Insertion Sort", SIZE);
            print_lst(arr, SIZE, ELEMENTS);
        }
        if (set_member(sorts, 3)) { // Heap sort
            reset(&stat);
            make_lst(lst, arr, SIZE);
            heap_sort(&stat, arr, SIZE);
            print_stats(&stat, "Heap Sort", SIZE);
            print_lst(arr, SIZE, ELEMENTS);
        }
        if (set_member(sorts, 2)) { // Shell sort
            reset(&stat);
            make_lst(lst, arr, SIZE);
            shell_sort(&stat, arr, SIZE);
            print_stats(&stat, "Shell Sort", SIZE);
            print_lst(arr, SIZE, ELEMENTS);
        }
        if (set_member(sorts, 1)) { // Quick sort
            reset(&stat);
            make_lst(lst, arr, SIZE);
            quick_sort(&stat, arr, SIZE);
            print_stats(&stat, "Quick Sort", SIZE);
            print_lst(arr, SIZE, ELEMENTS);
        }
        if (set_member(sorts, 0)) { // Batcher sort
            reset(&stat);
            make_lst(lst, arr, SIZE);
            batcher_sort(&stat, arr, SIZE);
            print_stats(&stat, "Batcher Sort", SIZE);
            print_lst(arr, SIZE, ELEMENTS);
        }

        /*cleanup*/
        free(lst);
        lst = NULL;
        free(arr);
        arr = NULL;
    }
    return 0;
}
