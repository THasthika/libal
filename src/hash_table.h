#ifndef THB_HASH_TABLE_H
#define THB_HASH_TABLE_H 1

#include <stdlib.h>

#include "list.h"

typedef struct {
	char *key;
	THB_ListItem *item;
} THB_HashItem;

typedef struct {
	size_t item_size;
	unsigned int count;
	void (*destroy)(void *data);
	THB_List *data;
	THB_List *table;
} THB_HashTable;

void THB_hash_table_create(THB_HashTable *hash_table, size_t item_size, unsigned int count, void (*destroy)(void *data));
void THB_hash_table_destroy(THB_HashTable *hash_table);

void THB_hash_table_insert(THB_HashTable *hash_table, char *key, void *data);
void THB_hash_table_remove(THB_HashTable *hash_table, char *key, void *data);
short THB_hash_table_search(THB_HashTable *hash_table, char *key, void *data);
short THB_hash_table_exists(THB_HashTable *hash_table, char *key);

#endif // THB_HASH_TABLE_H
