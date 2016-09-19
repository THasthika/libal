#include <THB/list.h>

#include <stdlib.h>
#include <string.h>

void list_create(List *list, size_t item_size, void (*destroy)(void *data)) {
	list->item_size = item_size;
	list->head = NULL;
	list->tail = NULL;
	list->destroy = destroy;
	list->count = 0;
}

void list_destroy(List *list) {
	ListItem *item;
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

void list_insert_after(List *list, ListItem *item, void *data) {
	ListItem *new_item = (ListItem*)malloc(sizeof(ListItem));
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

void list_insert_before(List *list, ListItem *item, void *data) {
	ListItem *new_item = (ListItem*)malloc(sizeof(ListItem));
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

void list_remove(List *list, ListItem *item, void *data) {
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
