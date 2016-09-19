#include <stdlib.h>
#include <string.h>

#include <THB/sort.h>

void insertion_sort(void *arr, size_t size, unsigned int count, int (*comp)(void *key1, void *key2)) {
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
}
