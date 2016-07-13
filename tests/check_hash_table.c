#include <stdlib.h>
#include <assert.h>


#include <THB/hash_table.h>

int main(int argc, char **argv) {

	int arr[] = {5123, 1232, 124123, 12423, 1231, 123, 32, 21};

	THB_HashTable *hash_table = (THB_HashTable*) malloc(sizeof(THB_HashTable));
	THB_hash_table_create(hash_table, sizeof(int), 20, NULL);

	THB_hash_table_insert(hash_table, "one", &arr[0]);

	int a;
	THB_hash_table_search(hash_table, "one", &a);

	assert(a == arr[0]);

	THB_hash_table_destroy(hash_table);
	free(hash_table);
	return 0;
}
