#ifndef LIST_H
#define LIST_H 1

#include <stdlib.h>

typedef struct _ListItem {
	struct _ListItem *prev;
	struct _ListItem *next;
	void *data;
} ListItem;

typedef struct _List {
	ListItem *head;
	ListItem *tail;
	size_t item_size;
	unsigned int count;
	void (*destroy)(void *data);
} List;

void list_create(List *list, size_t item_size, void (*destroy)(void *data));
void list_destroy(List *list);

void list_insert_after(List *list, ListItem *item, void *data);
void list_insert_before(List *list, ListItem *item, void *data);

void list_remove(List *list, ListItem *item, void *data);

#define list_head(list) (list->head)
#define list_tail(list) (list->tail)
#define list_count(list) (list->count)
#define list_next(item) (list->next)
#define list_prev(item) (list->prev)

#endif // LIST_H
