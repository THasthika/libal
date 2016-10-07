#include <stdlib.h>
#include <assert.h>

#include "hash_table.h"

int main(int argc, char **argv)
{
	int arr[] = {5123, 1232, 124123, 12423, 1231, 123, 32, 21};

	THB_HashTable *hash_table = (THB_HashTable*) malloc(sizeof(THB_HashTable));
	THB_hash_table_create(hash_table, sizeof(int), 5, NULL);

	THB_hash_table_insert(hash_table, "one", &arr[0]);

	int b;

	THB_hash_table_remove(hash_table, "one", &b);

	assert(b == arr[0]);

	THB_hash_table_insert(hash_table, "one", &arr[1]);

	if(THB_hash_table_search(hash_table, "one", &b))
		assert(b == arr[1]);

	assert(THB_hash_table_search(hash_table, "two", NULL) == 0);

	THB_hash_table_insert(hash_table, "two", &arr[2]);

	assert(THB_hash_table_search(hash_table, "two", NULL) == 1);

	THB_hash_table_insert(hash_table, "three", &arr[3]);

	THB_hash_table_insert(hash_table, "four", &arr[4]);

	THB_hash_table_destroy(hash_table);
	free(hash_table);
	return 0;
}
