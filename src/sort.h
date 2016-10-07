#ifndef THB_SORT_H
#define THB_SORT_H 1

void THB_insertion_sort(void *arr, size_t size, unsigned int count, int (*comp)(void *key1, void *key2));
void THB_merge_sort(void *arr, void *p, void *r, size_t size, int (*comp)(void *key1, void *key2));
void THB_heap_sort(void *arr, size_t size, unsigned int count, int (*comp)(void *key1, void *key2));

#endif // THB_SORT_H
