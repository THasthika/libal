#include "common.h"
#include <string.h>

#include "hash_table.h"

size_t hash_key(char *key, size_t count)
{
	size_t k = 0;
	char *ptr = key;
	while(*ptr != '\0')
		k += (size_t)*(ptr++);
	return k % count;
}

void AL_hash_table_create(AL_HashTable *hash_table, size_t item_size, size_t count, void (*destroy)(void *data))
{
	hash_table->item_size = item_size;
	hash_table->count = count;
	hash_table->destroy = destroy;
	hash_table->table = calloc(count, sizeof(AL_HashItem*));
}

void AL_hash_table_destroy(AL_HashTable *hash_table)
{
	AL_HashItem *item = NULL;
	for(size_t i = 0; i < hash_table->count; i++) {
		item = hash_table->table[i];
		while(item != NULL) {
			if(hash_table->destroy != NULL)
				hash_table->destroy(item->data);
			free(item->key);
			free(item->data);
			if(item->next == NULL) {
				free(item);
				break;
			}
			item = item->next;
			free(item->prev);
		}
	}
	free(hash_table->table);
	hash_table->table = NULL;
	hash_table->item_size = 0;
	hash_table->count = 0;
	hash_table->destroy = NULL;
}

void AL_hash_table_insert(AL_HashTable *hash_table, char *key, void *data)
{
	size_t k = hash_key(key, hash_table->count);
	AL_HashItem *item = malloc(sizeof(AL_HashItem));
	item->key = (char*)strdup(key);
	item->data = malloc(hash_table->item_size);
	item->prev = NULL;
	item->next = NULL;
	memcpy(item->data, data, hash_table->item_size);
	AL_HashItem *iitem = hash_table->table[k];
	AL_HashItem *tmp = NULL;
	AL_HashItem *prev = iitem;
	while(iitem != NULL) {
		if(iitem->next == NULL)
			prev = iitem;
		tmp = iitem;
		iitem = iitem->next;
		if(strcmp(tmp->key, item->key) == 0) {
			free(tmp->key);
			if(hash_table->destroy != NULL)
				hash_table->destroy(tmp->data);
			free(tmp->data);
			if(tmp->prev != NULL)
				tmp->prev->next = tmp->next;
			if(tmp->next != NULL)
				tmp->next->prev = tmp->prev;
			free(tmp);
			tmp = NULL;
		}
	}
	if(prev != NULL) {
		prev->next = item;
		item->prev = prev;
	} else
		hash_table->table[k] = item;
}

void AL_hash_table_remove(AL_HashTable *hash_table, char *key, void *data)
{
	size_t k = hash_key(key, hash_table->count);
	AL_HashItem *item = hash_table->table[k];
	while(item != NULL) {
		if(strcmp(item->key, key) == 0)
			break;
		item = item->next;
	}
	if(item == NULL)
		return;
	if(data != NULL)
		memcpy(data, item->data, hash_table->item_size);
	free(item->key);
	if(hash_table->destroy != NULL)
		hash_table->destroy(item->data);
	free(item->data);
	if(item->prev != NULL)
		item->prev->next = item->next;
	else
		hash_table->table[k] = item->next;
	if(item->next != NULL)
		item->next->prev = item->prev;
	free(item);
}

int AL_hash_table_search(AL_HashTable *hash_table, char *key, void **data)
{
	size_t k = hash_key(key, hash_table->count);
	AL_HashItem *item = hash_table->table[k];
	while(item != NULL) {
		if(strcmp(item->key, key) == 0)
			break;
		item = item->next;
	}
	if(item == NULL)
		return 0;
	if(data != NULL)
		*data = item->data;
	return 1;
}
