#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "util.h"
#include <THB/sort.h>

int comp_int(void *key1, void *key2) {
	if(*(int *)key1 > *(int *)key2)
		return 1;
	else if(*(int *)key1 < *(int *)key2)
		return -1;
	else
		return 0;
}

int main(int argc, char **argv) {
	srand(time(NULL));
	
	unsigned int count = 5;
	int arr[count];

	for(int i = 0; i < count; i++) {
		arr[i] = ((float)rand() / (float)RAND_MAX) * 10000;
	}
	
	print_array(arr, count);
	// THB_insertion_sort(arr, sizeof(int), count, comp_int);
	// THB_heap_sort(arr, sizeof(int), count, comp_int);
	THB_merge_sort(arr, &arr[0], &arr[count-1], sizeof(int), comp_int);

	

	print_array(arr, count);
	
	return 0;
}
