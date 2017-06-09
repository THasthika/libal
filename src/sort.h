#ifndef AL_SORT_H
#define AL_SORT_H 1

void AL_insertion_sort(void *arr, size_t size, unsigned int count, int (*comp)(void *key1, void *key2));
void AL_merge_sort(void *arr, void *p, void *r, size_t size, int (*comp)(void *key1, void *key2));
void AL_heap_sort(void *arr, size_t size, unsigned int count, int (*comp)(void *key1, void *key2));

#endif // AL_SORT_H
