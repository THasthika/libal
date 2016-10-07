#ifndef SORT_H
#define SORT_H 1

void insertion_sort(void *arr, size_t size, unsigned int count, int (*comp)(void *key1, void *key2));
void merge_sort(void *arr, void *p, void *r, size_t size, int (*comp)(void *key1, void *key2));
void heap_sort(void *arr, size_t size, unsigned int count, int (*comp)(void *key1, void *key2));

#endif // SORT_H
