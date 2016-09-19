#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <THB/list.h>

int main(int argc, char **argv) {

	int a, b, c;
	a = 1;
	b = 2;
	c = 3;

	List *list = (List*) malloc(sizeof(List));
	list_create(list, sizeof(int), NULL);

	list_insert_after(list, NULL, &a);
	ListItem *item = list_head(list);

	list_insert_before(list, NULL, &b);
	list_insert_before(list, NULL, &c);

	a = 10;
	list_insert_before(list, NULL, &a);

	assert(1 == *(int *)item->data);
	item = item->next;
	assert(2 == *(int *)item->data);
	item = item->next;
	assert(3 == *(int *)item->data);
	item = item->next;
	assert(10 == *(int *)item->data);
	item = item->next;

	list_destroy(list);

	free(list);

	return 0;
}
