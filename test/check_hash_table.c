#include <stdlib.h>
#include <assert.h>

#include "hash_table.h"

int main(int argc, char **argv)
{
	int arr[] = {5123, 1232, 124123, 12423, 1231, 123, 32, 21};

	AL_HashTable *hash_table = (AL_HashTable*) malloc(sizeof(AL_HashTable));
	AL_hash_table_create(hash_table, sizeof(int), 5, NULL);

	AL_hash_table_insert(hash_table, "one", &arr[0]);

	int b;

	AL_hash_table_remove(hash_table, "one", &b);

	assert(b == arr[0]);

	AL_hash_table_insert(hash_table, "one", &arr[1]);

	int *c;

	if(AL_hash_table_search(hash_table, "one", (void**)&c))
		assert(*c == arr[1]);

	assert(AL_hash_table_search(hash_table, "two", NULL) == 0);

	AL_hash_table_insert(hash_table, "two", &arr[2]);

	assert(AL_hash_table_search(hash_table, "two", NULL) == 1);

	AL_hash_table_insert(hash_table, "three", &arr[3]);

	AL_hash_table_insert(hash_table, "four", &arr[4]);

	AL_hash_table_destroy(hash_table);
	free(hash_table);
	return 0;
}
