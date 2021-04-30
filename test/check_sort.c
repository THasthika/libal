#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <sort.h>

#define ASC 1
#define DSC 2

int comp_int(void *key1, void *key2)
{
	if(*(int *)key1 > *(int *)key2)
		return 1;
	else if(*(int *)key1 < *(int *)key2)
		return -1;
	else
		return 0;
}

void check_array(int *arr, long count, short dir)
{
	int *p, *q;
	for(long i = 1; i < count; i++) {
		p = arr + i - 1;
		q = arr + i;
		if(dir == ASC)
			assert(*p <= *q);
		else if(dir == DSC)
			assert(*p >= *q);
	}
}

void init_array(int *arr, long count)
{
	for(long i = 0; i < count; i++) {
		*(arr + i) = ((float)rand() / (float)RAND_MAX) * 10000;
	}
}

void check_insertion_sort(long count)
{
	int arr[count];
	init_array(arr, count);
	AL_insertion_sort(arr, sizeof(int), count, comp_int);
	check_array(arr, count, ASC);
}

void check_heap_sort(long count)
{
	int arr[count];
	init_array(arr, count);
	AL_heap_sort(arr, sizeof(int), count, comp_int);
	check_array(arr, count, ASC);
}

void check_merge_sort(long count)
{
	int arr[count];
	init_array(arr, count);
	AL_merge_sort(arr, sizeof(int), count, comp_int);
	check_array(arr, count, ASC);
}

void check_quick_sort(long count)
{
	int arr[count];
	init_array(arr, count);
	AL_quick_sort(arr, sizeof(int), count, comp_int);
	check_array(arr, count, ASC);
}

int main(int argc, char **argv)
{
	srand(time(NULL));

	check_insertion_sort(100);
	check_heap_sort(100);
	check_merge_sort(100);
	check_quick_sort(10);

	return 0;
}
