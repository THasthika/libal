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

void THB_hash_table_create(THB_HashTable *hash_table, size_t item_size, unsigned int count, void (*destroy)(void *data)) {
	hash_table->item_size = item_size;
	hash_table->count = count;
	hash_table->destroy = destroy;
	hash_table->data = (THB_List*) malloc(sizeof(THB_List));
	hash_table->table = (THB_List*) malloc(sizeof(THB_List) * count);
	THB_list_create(hash_table->data, hash_table->item_size, destroy);
	for(int i = 0; i < hash_table->count; i++) {
		THB_list_create(hash_table->table + i, sizeof(THB_HashItem), NULL);
	}
}

void THB_hash_table_destroy(THB_HashTable *hash_table) {
	for(int i = 0; i < hash_table->count; i++) {
		THB_list_destroy(hash_table->table + i);
	}
	THB_list_destroy(hash_table->data);
	hash_table->item_size = 0;
	hash_table->count = 0;
	hash_table->destroy = NULL;
	free(hash_table->data);
	free(hash_table->table);
}

void THB_hash_table_insert(THB_HashTable *hash_table, char *key, void *data) {

	THB_hash_table_remove(hash_table, key, NULL);

	unsigned int k = hash_key(key, hash_table->count);
	THB_List *list = hash_table->table + k;

	THB_list_insert_before(hash_table->data, NULL, data);
	THB_ListItem *item = THB_list_tail(hash_table->data);

	THB_HashItem hash_item = {
		key,
		item
	};

	THB_list_insert_before(list, NULL, &hash_item);
}

void THB_hash_table_remove(THB_HashTable *hash_table, char *key, void *data) {
	unsigned int k = hash_key(key, hash_table->count);
	THB_List *list = hash_table->table + k;
	THB_ListItem *list_item;
	THB_HashItem *item;
	list_item = THB_list_head(list);
	while(list_item != NULL) {
		item = (THB_HashItem*)list_item->data;
		if(strcmp(item->key, key) == 0)
			break;
		list_item = list_item->next;
	}
	if(list_item != NULL) {
		THB_HashItem hash_item;
		THB_list_remove(list, list_item, &hash_item);
		list_item = hash_item.item;
		if(list_item != NULL)
			THB_list_remove(hash_table->data, list_item, data);
	}
}

short THB_hash_table_search(THB_HashTable *hash_table, char *key, void *data) {
	unsigned int k = hash_key(key, hash_table->count);
	THB_List *list = hash_table->table + k;
	THB_ListItem *list_item;
	THB_HashItem *item;
	list_item = THB_list_head(list);
	while(list_item != NULL) {
		item = (THB_HashItem*)list_item->data;
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

short THB_hash_table_exists(THB_HashTable *hash_table, char *key) {	
	unsigned int k = hash_key(key, hash_table->count);
	THB_List *list = hash_table->table + k;
	THB_ListItem *list_item;
	THB_HashItem *item;
	list_item = THB_list_head(list);
	while(list_item != NULL) {
		item = (THB_HashItem*)list_item->data;
		if(strcmp(item->key, key) == 0)
			break;
		list_item = list_item->next;
	}
	if(list_item != NULL) {
		return 1;
	}
	return 0;
}
