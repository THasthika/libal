#include "common.h"
#include "dynamic.h"

#include <stdio.h>
#include <string.h>

#define max(X, Y)  ((X) > (Y) ? (X) : (Y))

int AL_longest_common_subsequence(size_t size, void *arr1, int arr1len, void *arr2, int arr2len, int (*comp)(void *key1, void *key2), void **ret)
{
    int M[arr1len+1][arr2len+1];

    for (int j = 0; j < arr1len+1; j++) {
        for (int i = 0; i < arr2len+1; i++) {
            if (i == 0 || j == 0) {
                M[j][i] = 0;
            } else {
                void *k1 = arr1 + (size * (j-1));
                void *k2 = arr2 + (size * (i-1));
                if (comp(k1, k2) == 0) {
                    M[j][i] = M[j-1][i-1] + 1;
                } else {
                    M[j][i] = max(M[j-1][i], M[j][i-1]);
                }
            }
        }
    }

    int p = M[arr1len][arr2len];
    int i, j;
    i = arr2len;
    j = arr1len;

    if (p > 0) {
        *ret = malloc(size * p);
        void *k = *ret + (size * (p-1));
        void *s = NULL;
        while (p > 0 && j > 0 && i > 0) {
            if (M[j-1][i] == p) {
                j--;
            } else if (M[j][i-1] == p) {
                i--;
            } else {
                i--;
                j--;
                s = arr1 + (size * j);
                memcpy(k, s, size);
                p = M[j][i];
                k -= size;
            }
        }
    } else {
        *ret = NULL;
    }

    return M[arr1len][arr2len];
}