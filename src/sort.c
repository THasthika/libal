#include <stdio.h>
#include "common.h"
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

void max_heapify(void *arr, size_t size, size_t count, size_t i, int (*comp)(void *key1, void *key2))
{
	long l = HEAP_LEFT(i);
	long r = HEAP_RIGHT(i);
	long largest = i;
	if(l < count && comp(arr + size * l, arr + size * i) == 1)
		largest = l;
	if(r < count && comp(arr + size * r, arr + size * largest) == 1)
		largest = r;
	if(largest != i) {
		swap(arr + size * i, arr + size * largest, size);
		max_heapify(arr, size, count, largest, comp);
	}
}

size_t build_max_heapify(void *arr, size_t size, size_t count, int (*comp)(void *key1, void *key2))
{
	for(long long i = (count / 2); i >= 0; i--) {
		max_heapify(arr, size, count, i, comp);
	}
	return count;
}

void min_heapify(void *arr, size_t size, size_t count, size_t i, int (*comp)(void *key1, void *key2))
{
	long l = HEAP_LEFT(i);
	long r = HEAP_RIGHT(i);
	long smallest = i;
	if(l < count && comp(arr + size * l, arr + size * i) == -1)
		smallest = l;
	if(r < count && comp(arr + size * r, arr + size * smallest) == -1)
		smallest = r;
	if(smallest != i) {
		swap(arr + size * i, arr + size * smallest, size);
		min_heapify(arr, size, count, smallest, comp);
	}
}

size_t build_min_heapify(void *arr, size_t size, size_t count, int (*comp)(void *key1, void *key2))
{
	for(long i = (count / 2); i >= 0; i--) {
		min_heapify(arr, size, count, i, comp);
	}
	return count;
}

void AL_heap_sort(void *arr, size_t size, size_t count, int (*comp)(void *key1, void *key2))
{
	size_t heapsize = build_max_heapify(arr, size, count, comp);
	for(size_t i = count - 1; i >= 1; i--) {
		swap(arr, arr + size * i, size);
		heapsize--;
		max_heapify(arr, size, heapsize, 0, comp);
	}

        // size_t heapsize = build_min_heapify(arr, size, count, comp);
        // for(int i = count - 1; i >= 1; i--) {
        //         swap(arr, arr + size * i, size);
        //         heapsize--;
        //         min_heapify(arr, size, heapsize, 0, comp);
        // }
}

/********************** INSERTION SORT ***************************/

/**
j = 2 & i = j - 1
is because that j and i are unsigned long (size_t)
**/
void AL_insertion_sort(void *arr, size_t size, size_t count, int (*comp)(void *key1, void *key2))
{
	void *key = malloc(size);
	size_t j, i;
	for(j = 2; j < (count + 1); j++) {
		memcpy(key, (arr + size*(j-1)), size);
		i = j - 1;
		while(i > 0 && (*comp)(key, (arr + size*(i-1))) == -1) {
			memcpy((arr + size*(i)), (arr + size*(i-1)), size);
			i--;
		}
		memcpy((arr + size*(i)), key, size);
	}
	free(key);
}

/************************** MERGE SORT *****************************/

void merge(void *l, void *q, void *r, size_t size, int (*comp)(void *key1, void *key2))
{
	void *tmp_arr = malloc(r - l + size);
	void *i = l;
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
	memcpy(l, tmp_arr, r - l + size);
	free(tmp_arr);
}

void merge_sort(void *l, void *r, size_t size, int(*comp)(void *key1, void *key2))
{
	void *q = l;
	if(r - l > size) {
		q = l + ((r - l + size) / (2 * size)) * size;
		merge_sort(l, q, size, comp);
		merge_sort(q+size, r, size, comp);
	}
	merge(l, q, r, size, comp);
}

/**
* arr - pointer to the list
* size - size of an item in the list
* count - number of items in the list
* comp - a function to compare two items in the list
**/
void AL_merge_sort(void *arr, size_t size, size_t count, int (*comp)(void *key1, void *key2))
{
	void *l = arr;
	void *r = arr + size * count;
	merge_sort(l, r, size, comp);
}

/************************** QUICK SORT ***************************/

void partition(void *l, void *r, size_t size, int (*comp)(void *key1, void *key2), void **ret) {
	void *x = r;
	void *i = l - size;
	for (void *j = l; j < r; j += size) {
		// j <= x
		if (comp(j, x) < 1) {
			i += size;
			swap(i, j, size);
		}
	}
	i += size;
	swap(i, r, size);
	*ret = i;
}

void quick_sort(void *l, void *r, size_t size, int (*comp)(void *key1, void *key2), int lvl) {
	if(l < r) {
		void *q;
		partition(l, r, size, comp, &q);
		quick_sort(l, q - size, size, comp, lvl+1);
		quick_sort(q + size, r, size, comp, lvl+1);
	}
}

void AL_quick_sort(void *arr, size_t size, size_t count, int (*comp)(void *key1, void *key2))
{
	void *l = arr;
	void *r = arr + size * (count - 1);
	quick_sort(l, r, size, comp, 0);
}
