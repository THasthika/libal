#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <THB/sort.h>

#define PARENT(i) ((i+1)/2) - 1
#define LEFT(i) (2*(i+1)) - 1
#define RIGHT(i) (2*(i+1)+1) - 1

void swap(void *i, void *j, size_t size) {
	void *tmp = malloc(size);
	memcpy(tmp, i, size);
	memcpy(i, j, size);
	memcpy(j, tmp, size);
	free(tmp);
}

void max_heapify(void *arr, size_t size, unsigned int count, unsigned int i, int (*comp)(void *key1, void *key2)) {
	unsigned int l = LEFT(i);
	unsigned int r = RIGHT(i);
	unsigned int largest = i;
	if(l < count && comp(arr + size * l, arr + size * i) == 1)
		largest = l;
	if(r < count && comp(arr + size * r, arr + size * largest) == 1)
		largest = r;
	if(largest != i) {
		swap(arr + size * i, arr + size * largest, size);
		max_heapify(arr, size, count, largest, comp);
	}
}

unsigned int build_max_heapify(void *arr, size_t size, unsigned int count, int (*comp)(void *key1, void *key2)) {
	for(int i = (count / 2); i >= 0; i--) {
		max_heapify(arr, size, count, i, comp);
	}
	return count;
}

void min_heapify(void *arr, size_t size, unsigned int count, unsigned int i, int (*comp)(void *key1, void *key2)) {
	unsigned int l = LEFT(i);
	unsigned int r = RIGHT(i);
	unsigned int smallest = i;
	if(l < count && comp(arr + size * l, arr + size * i) == -1)
		smallest = l;
	if(r < count && comp(arr + size * r, arr + size * smallest) == -1)
		smallest = r;
	if(smallest != i) {
		swap(arr + size * i, arr + size * smallest, size);
		min_heapify(arr, size, count, smallest, comp);
	}
}

unsigned int build_min_heapify(void *arr, size_t size, unsigned int count, int (*comp)(void *key1, void *key2)) {
	for(int i = (count / 2); i >= 0; i--) {
		min_heapify(arr, size, count, i, comp);
	}
	return count;
}

void THB_heap_sort(void *arr, size_t size, unsigned int count, int (*comp)(void *key1, void *key2)) {
	unsigned int heapsize = build_max_heapify(arr, size, count, comp);
	for(int i = count - 1; i >= 1; i--) {
		swap(arr, arr + size * i, size);
		heapsize--;
		max_heapify(arr, size, heapsize, 0, comp);
	}

        // unsigned int heapsize = build_min_heapify(arr, size, count, comp);
        // for(int i = count - 1; i >= 1; i--) {
        //         swap(arr, arr + size * i, size);
        //         heapsize--;
        //         min_heapify(arr, size, heapsize, 0, comp);
        // }
}
