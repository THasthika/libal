#ifndef AL_SORT_H
#define AL_SORT_H 1

#include "common.h"

void AL_insertion_sort(void *arr, size_t size, size_t count, int (*comp)(void *key1, void *key2));
void AL_merge_sort(void *arr, size_t size, size_t count, int (*comp)(void *key1, void *key2));
void AL_heap_sort(void *arr, size_t size, size_t  count, int (*comp)(void *key1, void *key2));
void AL_quick_sort(void *arr, size_t size, size_t count, int (*comp)(void *key1, void *key2));

#endif // AL_SORT_H
