#ifndef THB_HASH_TABLE_H
#define THB_HASH_TABLE_H 1

#include <stdlib.h>

#include <THB/list.h>

typedef struct {
	void *key;
	void *data;
} THB_HashItem;

typedef struct {
	size_t item_size;
	unsigned int count;
	void (*destroy)(void *data);
	THB_List **table;
} THB_HashTable;

void THB_hash_table_create(THB_HashTable *table, size_t item_size, unsigned int count, void (*destroy)(void *data));
void THB_hash_table_destroy(THB_HashTable *table);

void THB_hash_table_insert(THB_HashTable *table, char *key, void *data);
void THB_hash_table_remove(THB_HashTable *table, char *key, void *data);
void THB_hash_table_search(THB_HashTable *table, char *key, void *data);

#endif // THB_HASH_TABLE_H
