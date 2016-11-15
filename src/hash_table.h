#ifndef THB_HASH_TABLE_H
#define THB_HASH_TABLE_H 1

#include <stdlib.h>

typedef struct _THB_HashItem {
	struct _THB_HashItem *prev;
	struct _THB_HashItem *next;
	char *key;
	void *data;
} THB_HashItem;

typedef struct {
	size_t item_size;
	unsigned int count;
	void (*destroy)(void *data);
	THB_HashItem **table;
} THB_HashTable;

void THB_hash_table_create(THB_HashTable *hash_table, size_t item_size, unsigned int count, void (*destroy)(void *data));
void THB_hash_table_destroy(THB_HashTable *hash_table);

void THB_hash_table_insert(THB_HashTable *hash_table, char *key, void *data);
void THB_hash_table_remove(THB_HashTable *hash_table, char *key, void *data);
int THB_hash_table_search(THB_HashTable *hash_table, char *key, void **data);

#endif // THB_HASH_TABLE_H
