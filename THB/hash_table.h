#ifndef HASH_TABLE_H
#define HASH_TABLE_H 1

#include <stdlib.h>

#include <THB/list.h>

typedef struct {
	char *key;
	ListItem *item;
} HashItem;

typedef struct {
	size_t item_size;
	unsigned int count;
	void (*destroy)(void *data);
	List *data;
	List *table;
} HashTable;

void hash_table_create(HashTable *hash_table, size_t item_size, unsigned int count, void (*destroy)(void *data));
void hash_table_destroy(HashTable *hash_table);

void hash_table_insert(HashTable *hash_table, char *key, void *data);
void hash_table_remove(HashTable *hash_table, char *key, void *data);
short hash_table_search(HashTable *hash_table, char *key, void *data);
short hash_table_exists(HashTable *hash_table, char *key);

#endif // HASH_TABLE_H
