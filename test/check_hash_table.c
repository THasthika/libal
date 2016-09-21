#include <stdlib.h>
#include <assert.h>


#include <THB/hash_table.h>

void check(HashTable *table, char *key, int val)
{
	int x;
	hash_table_search(table, key, &x);
	assert(x == val);
}

int main(int argc, char **argv)
{
	HashTable ht;

	hash_table_create(&ht, sizeof(int), 2, NULL);

	int t;

	t = 1;
	hash_table_insert(&ht, "a", &t);

	t = 8;
	hash_table_insert(&ht, "ab", &t);

	t = 10;
	hash_table_insert(&ht, "abc", &t);

	check(&ht, "a", 1);

	check(&ht, "ab", 8);


	hash_table_destroy(&ht);

	return 0;
}
