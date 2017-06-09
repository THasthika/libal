#ifndef AL_HASH_TABLE_H
#define AL_HASH_TABLE_H 1

#include <stdlib.h>

typedef struct _AL_HashItem {
	struct _AL_HashItem *prev;
	struct _AL_HashItem *next;
	char *key;
	void *data;
} AL_HashItem;

typedef struct {
	size_t item_size;
	unsigned int count;
	void (*destroy)(void *data);
	AL_HashItem **table;
} AL_HashTable;

void AL_hash_table_create(AL_HashTable *hash_table, size_t item_size, unsigned int count, void (*destroy)(void *data));
void AL_hash_table_destroy(AL_HashTable *hash_table);

void AL_hash_table_insert(AL_HashTable *hash_table, char *key, void *data);
void AL_hash_table_remove(AL_HashTable *hash_table, char *key, void *data);
int AL_hash_table_search(AL_HashTable *hash_table, char *key, void **data);

#endif // AL_HASH_TABLE_H
