#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "list.h"

int main(int argc, char **argv)
{
	int a, b, c;
	a = 1;
	b = 2;
	c = 3;

	THB_List *list = (THB_List*) malloc(sizeof(THB_List));
	THB_list_create(list, sizeof(int), NULL);

	THB_list_insert_after(list, NULL, &a);
	THB_ListItem *item = THB_list_head(list);

	THB_list_insert_before(list, NULL, &b);
	THB_list_insert_before(list, NULL, &c);

	a = 10;
	THB_list_insert_before(list, NULL, &a);

	assert(1 == *(int *)item->data);
	item = item->next;
	assert(2 == *(int *)item->data);
	item = item->next;
	assert(3 == *(int *)item->data);
	item = item->next;
	assert(10 == *(int *)item->data);
	item = item->next;

	int d;
	THB_list_remove(list, THB_list_head(list), &d);

	assert(d == 1);

	THB_list_destroy(list);

	free(list);

	return 0;
}
