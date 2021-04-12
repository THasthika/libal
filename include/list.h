#ifndef AL_LIST_H
#define AL_LIST_H 1

#include "common.h"

typedef struct _AL_ListItem {
	struct _AL_ListItem *prev;
	struct _AL_ListItem *next;
	void *data;
} AL_ListItem;

typedef struct _AL_List {
	AL_ListItem *head;
	AL_ListItem *tail;
	size_t item_size;
	unsigned int count;
	void (*destroy)(void *data);
} AL_List;

void AL_list_create(AL_List *list, size_t item_size, void (*destroy)(void *data));
void AL_list_destroy(AL_List *list);

void AL_list_insert_after(AL_List *list, AL_ListItem *item, void *data);
void AL_list_insert_before(AL_List *list, AL_ListItem *item, void *data);

void AL_list_remove(AL_List *list, AL_ListItem *item, void *data);

#define AL_list_head(list) (list->head)
#define AL_list_tail(list) (list->tail)
#define AL_list_count(list) (list->count)
#define AL_list_next(item) (list->next)
#define AL_list_prev(item) (list->prev)

#endif // AL_LIST_H
