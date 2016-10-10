#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "sort.h"

/************************** HEAP SORT ***************************/

#define HEAP_PARENT(i) ((i+1)/2) - 1
#define HEAP_LEFT(i) (2*(i+1)) - 1
#define HEAP_RIGHT(i) (2*(i+1)+1) - 1

void swap(void *i, void *j, size_t size)
{
	void *tmp = malloc(size);
	memcpy(tmp, i, size);
	memcpy(i, j, size);
	memcpy(j, tmp, size);
	free(tmp);
}

void max_heapify(void *arr, size_t size, unsigned int count, unsigned int i, int (*comp)(void *key1, void *key2)) 
{
	unsigned int l = HEAP_LEFT(i);
	unsigned int r = HEAP_RIGHT(i);
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

unsigned int build_max_heapify(void *arr, size_t size, unsigned int count, int (*comp)(void *key1, void *key2))
{
	for(int i = (count / 2); i >= 0; i--) {
		max_heapify(arr, size, count, i, comp);
	}
	return count;
}

void min_heapify(void *arr, size_t size, unsigned int count, unsigned int i, int (*comp)(void *key1, void *key2)) 
{
	unsigned int l = HEAP_LEFT(i);
	unsigned int r = HEAP_RIGHT(i);
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

unsigned int build_min_heapify(void *arr, size_t size, unsigned int count, int (*comp)(void *key1, void *key2))
{
	for(int i = (count / 2); i >= 0; i--) {
		min_heapify(arr, size, count, i, comp);
	}
	return count;
}

void THB_heap_sort(void *arr, size_t size, unsigned int count, int (*comp)(void *key1, void *key2))
{
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

/********************** INSERTION SORT ***************************/

void THB_insertion_sort(void *arr, size_t size, unsigned int count, int (*comp)(void *key1, void *key2))
{
	void *key = malloc(size);
	for(int j = 1; j < count; j++) {
		memcpy(key, (arr + size*j), size);
		int i = j - 1;
		while(i >= 0 && (*comp)(key, (arr + size*i)) == -1) {
			memcpy((arr + size*(i+1)), (arr + size*i), size);
			i--;
		}
		memcpy((arr + size*(i+1)), key, size);
	}
	free(key);
}

/************************** MERGE SORT *****************************/

void merge(void *arr, void *p, void *q, void *r, size_t size, int (*comp)(void *key1, void *key2))
{
	void *tmp_arr = malloc(r - p + size);
	void *i = p;
	void *j = q + size;
	void *k = tmp_arr;
	while(i != (q + size) && j != (r + size)) {
		if(comp(i, j) == -1) {
			memcpy(k, i, size);
			i += size;
		} else {
			memcpy(k, j, size);
			j += size;
		}
		k += size;
	}
	while(i != (q + size)) {
		memcpy(k, i, size);
		k += size;
		i += size;
	}
	while(j != (r + size)) {
		memcpy(k, j, size);
		j += size;
		k += size;
	}
	memcpy(p, tmp_arr, r - p + size);
	free(tmp_arr);
}

void THB_merge_sort(void *arr, void *p, void *r, size_t size, int (*comp)(void *key1, void *key2))
{
	void *q = p;
	if(r - p > size) {
		q = p + ((r - p + size) / (2 * size)) * size;
		THB_merge_sort(arr, p, q, size, comp);
		THB_merge_sort(arr, q+size, r, size, comp);
	}
	merge(arr, p, q, r, size, comp);
}
