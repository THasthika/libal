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

	AL_List *list = (AL_List*) malloc(sizeof(AL_List));
	AL_list_create(list, sizeof(int), NULL);

	AL_list_insert_after(list, NULL, &a);
	AL_ListItem *item = AL_list_head(list);

	AL_list_insert_before(list, NULL, &b);
	AL_list_insert_before(list, NULL, &c);

	a = 10;
	AL_list_insert_before(list, NULL, &a);

	assert(1 == *(int *)item->data);
	item = item->next;
	assert(2 == *(int *)item->data);
	item = item->next;
	assert(3 == *(int *)item->data);
	item = item->next;
	assert(10 == *(int *)item->data);
	item = item->next;

	int d;
	AL_list_remove(list, AL_list_head(list), &d);

	assert(d == 1);

	AL_list_destroy(list);

	free(list);

	return 0;
}
