#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <THB/sort.h>

void merge(void *arr, void *p, void *q, void *r, size_t size, int (*comp)(void *key1, void *key2)) {
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

void merge_sort(void *arr, void *p, void *r, size_t size, int (*comp)(void *key1, void *key2)) {
	void *q = p;
	if(r - p > size) {
		q = p + ((r - p + size) / (2 * size)) * size;
		merge_sort(arr, p, q, size, comp);
		merge_sort(arr, q+size, r, size, comp);
	}
	merge(arr, p, q, r, size, comp);
}
