#ifndef AL_DYNAMIC_H
#define AL_DYNAMIC_H 1

#include "common.h"

int AL_longest_common_subsequence(size_t size, void *arr1, int arr1len, void *arr2, int arr2len, int (*comp)(void *key1, void *key2), void **ret);

#endif // AL_DYNAMIC_H