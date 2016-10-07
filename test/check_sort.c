#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <sort.h>

#define ASC 1
#define DSC 2

int comp_int(void *key1, void *key2) {
	if(*(int *)key1 > *(int *)key2)
		return 1;
	else if(*(int *)key1 < *(int *)key2)
		return -1;
	else
		return 0;
}

void check_array(int *arr, unsigned int count, short dir) {
	int *p, *q;
	for(int i = 1; i < count; i++) {
		p = arr + i - 1;
		q = arr + i;
		if(dir == ASC)
			assert(*p <= *q);
		else if(dir == DSC)
			assert(*p >= *q);
	}
}

void init_array(int *arr, unsigned int count) {
	for(int i = 0; i < count; i++) {
		*(arr + i) = ((float)rand() / (float)RAND_MAX) * 10000;
	}
}

void check_insertion_sort(unsigned int count) {
	int arr[count];
	init_array(arr, count);
	THB_insertion_sort(arr, sizeof(int), count, comp_int);
	check_array(arr, count, ASC);
}

void check_heap_sort(unsigned int count) {
	int arr[count];
	init_array(arr, count);
	THB_heap_sort(arr, sizeof(int), count, comp_int);
	check_array(arr, count, ASC);
}

void check_merge_sort(unsigned int count) {
	int arr[count];
	init_array(arr, count);
	THB_merge_sort(arr, &arr[0], &arr[count - 1], sizeof(int), comp_int);
	check_array(arr, count, ASC);
}

int main(int argc, char **argv) {
	srand(time(NULL));

	check_insertion_sort(10000);
	check_heap_sort(10000);
	check_merge_sort(10000);
	// THB_insertion_sort(arr, sizeof(int), count, comp_int);
	// THB_heap_sort(arr, sizeof(int), count, comp_int);
	// THB_merge_sort(arr, &arr[0], &arr[count-1], sizeof(int), comp_int);
	
	return 0;
}
