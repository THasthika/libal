#ifndef THB_LIST_H
#define THB_LIST_H 1

#include <stdlib.h>

typedef struct _THB_ListItem {
	struct _THB_ListItem *prev;
	struct _THB_ListItem *next;
	void *data;
} THB_ListItem;

typedef struct _THB_List {
	THB_ListItem *head;
	THB_ListItem *tail;
	size_t item_size;
	unsigned int count;
	void (*destroy)(void *data);
} THB_List;

void THB_list_create(THB_List *list, size_t item_size, void (*destroy)(void *data));
void THB_list_destroy(THB_List *list);

void THB_list_insert_after(THB_List *list, THB_ListItem *item, void *data);
void THB_list_insert_before(THB_List *list, THB_ListItem *item, void *data);

void THB_list_remove(THB_List *list, THB_ListItem *item, void *data);

#define THB_list_head(list) (list->head)
#define THB_list_tail(list) (list->tail)
#define THB_list_count(list) (list->count)
#define THB_list_next(item) (list->next)
#define THB_list_prev(item) (list->prev)

#endif // THB_LIST_H
