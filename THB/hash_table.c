#include <stdlib.h>
#include <string.h>

#include <THB/list.h>
#include <THB/hash_table.h>

unsigned int hash_key(char *key, unsigned int count) {
	unsigned int k = 0;
	char *ptr = key;
	while(*ptr != '\0')
		k += (int)*(ptr++);
	return k % count;
}

void hash_table_create(HashTable *hash_table, size_t item_size, unsigned int count, void (*destroy)(void *data)) {
	hash_table->item_size = item_size;
	hash_table->count = count;
	hash_table->destroy = destroy;
	hash_table->data = (List*) malloc(sizeof(List));
	hash_table->table = (List*) malloc(sizeof(List) * count);
	list_create(hash_table->data, hash_table->item_size, destroy);
	for(int i = 0; i < hash_table->count; i++) {
		list_create(hash_table->table + i, sizeof(HashItem), NULL);
	}
}

void hash_table_destroy(HashTable *hash_table) {
	for(int i = 0; i < hash_table->count; i++) {
		list_destroy(hash_table->table + i);
	}
	list_destroy(hash_table->data);
	hash_table->item_size = 0;
	hash_table->count = 0;
	hash_table->destroy = NULL;
	free(hash_table->data);
	free(hash_table->table);
}

void hash_table_insert(HashTable *hash_table, char *key, void *data) {

	hash_table_remove(hash_table, key, NULL);

	unsigned int k = hash_key(key, hash_table->count);
	List *list = hash_table->table + k;
	list_insert_before(hash_table->data, NULL, data);
	ListItem *item = list_tail(hash_table->data);

	HashItem hash_item = {
		key,
		item
	};

	list_insert_before(list, NULL, &hash_item);
}

void hash_table_remove(HashTable *hash_table, char *key, void *data) {
	unsigned int k = hash_key(key, hash_table->count);
	List *list = hash_table->table + k;
	ListItem *list_item;
	HashItem *item;
	list_item = list_head(list);
	while(list_item != NULL) {
		item = (HashItem*)list_item->data;
		if(strcmp(item->key, key) == 0)
			break;
		list_item = list_item->next;
	}
	if(list_item != NULL) {
		HashItem hash_item;
		list_remove(list, list_item, &hash_item);
		list_item = hash_item.item;
		if(list_item != NULL)
			list_remove(hash_table->data, list_item, data);
	}
}

short hash_table_search(HashTable *hash_table, char *key, void *data) {
	unsigned int k = hash_key(key, hash_table->count);
	List *list = hash_table->table + k;
	ListItem *list_item;
	HashItem *item;
	list_item = list_head(list);
	while(list_item != NULL) {
		item = (HashItem*)list_item->data;
		if(strcmp(item->key, key) == 0)
			break;
		list_item = list_item->next;
	}
	if(list_item != NULL) {
		list_item = item->item;
		if(list_item != NULL && data != NULL)
			memcpy(data, list_item->data, hash_table->item_size);
		return 1;
	}
	return 0;
}

short hash_table_exists(HashTable *hash_table, char *key) {	
	unsigned int k = hash_key(key, hash_table->count);
	List *list = hash_table->table + k;
	ListItem *list_item;
	HashItem *item;
	list_item = list_head(list);
	while(list_item != NULL) {
		item = (HashItem*)list_item->data;
		if(strcmp(item->key, key) == 0)
			break;
		list_item = list_item->next;
	}
	if(list_item != NULL) {
		return 1;
	}
	return 0;
}
