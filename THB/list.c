#include <THB/list.h>

#include <stdlib.h>
#include <string.h>

void THB_list_create(THB_List *list, size_t item_size, void (*destroy)(void *data)) {
	list->item_size = item_size;
	list->head = NULL;
	list->tail = NULL;
	list->destroy = destroy;
	list->count = 0;
}

void THB_list_destroy(THB_List *list) {
	THB_ListItem *item;
	item = list->head;
	while(item != NULL) {
		if(list->destroy != NULL)
			list->destroy(item);
		free(item->data);
		if(item->next == NULL) {
			free(item);
			break;
		}
		item = item->next;
		free(item->prev);
	}
	list->head = NULL;
	list->tail = NULL;
	list->destroy = NULL;
	list->count = 0;
	list->item_size = 0;
}

void THB_list_insert_after(THB_List *list, THB_ListItem *item, void *data) {
	THB_ListItem *new_item = (THB_ListItem*)malloc(sizeof(THB_ListItem));
	new_item->next = NULL;
	new_item->prev = NULL;
	if(item == NULL) {
		if(list->head != NULL) {
			new_item->next = list->head;
			list->head->prev = new_item;
		} else {
			list->tail = new_item;
		}
		list->head = new_item;
	} else {
		new_item->next = item->next;
		if(item->next != NULL)
			item->next->prev = new_item;
		new_item->prev = item;
		item->next = new_item;
	}
	new_item->data = malloc(list->item_size);
	memcpy(new_item->data, data, list->item_size);
	list->count++;
}

void THB_list_insert_before(THB_List *list, THB_ListItem *item, void *data) {
	THB_ListItem *new_item = (THB_ListItem*)malloc(sizeof(THB_ListItem));
	new_item->next = NULL;
	new_item->prev = NULL;
	if(item == NULL) {
		if(list->tail != NULL) {
			new_item->prev = list->tail;
			list->tail->next = new_item;
		} else {
			list->head = new_item;
		}
		list->tail = new_item;
	} else {
		new_item->prev = item->prev;
		if(item->prev != NULL)
			item->prev->next = new_item;
		new_item->next = item;
		item->prev = new_item;
	}
	new_item->data = malloc(list->item_size);
	memcpy(new_item->data, data, list->item_size);
	list->count++;
}

void THB_list_remove(THB_List *list, THB_ListItem *item, void *data) {
	if(item == NULL) return;
	if(item->next != NULL)
		item->next->prev = item->prev;
	if(item->prev != NULL)
		item->prev->next = item->next;
	if(list->head == item)
		list->head = item->next;
	if(list->tail == item)
		list->tail = item->prev;
	if(data != NULL)
		memcpy(data, item->data, list->item_size);
	if(list->destroy != NULL)
		list->destroy(item->data);
	free(item->data);
	free(item);
	item = NULL;
	list->count--;
}
