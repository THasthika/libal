#include <stdlib.h>
#include <stdio.h>

#include <THB/list.h>

int main(int argc, char **argv) {

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

	printf("%d", *(int *)item->data);
	item = item->next;
	printf("%d", *(int *)item->data);
	item = item->next;
	printf("%d", *(int *)item->data);
	item = item->next;
	printf("%d", *(int *)item->data);
	item = item->next;

	THB_list_destroy(list);

	free(list);

	return 0;
}
