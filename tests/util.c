#include <stdio.h>

#include "util.h"


void print_array(void *arr, long count) {
        int *k = (int *)arr;
        for(long i = 0; i < count; i++) {
                printf("%d ", *(k++));
        }
        printf("\n");
}
