#include <stdlib.h>
#include <assert.h>


#include <THB/hash_table.h>

int main(int argc, char **argv) {

	int arr[] = {5123, 1232, 124123, 12423, 1231, 123, 32, 21};

	HashTable *hash_table = (HashTable*) malloc(sizeof(HashTable));
	hash_table_create(hash_table, sizeof(int), 20, NULL);

	hash_table_insert(hash_table, "one", &arr[0]);

	hash_table_insert(hash_table, "one", &arr[1]);

	hash_table_insert(hash_table, "a", &arr[2]);

	hash_table_insert(hash_table, "three", &arr[3]);

	short res;
	res = hash_table_exists(hash_table, "P");
	assert(res == 0);

	int a;
	hash_table_search(hash_table, "one", &a);

	assert(a == arr[1]);

	hash_table_destroy(hash_table);
	free(hash_table);
	return 0;
}
