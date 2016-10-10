#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bst.h"

void fn(void *data)
{
	int a = *(int*)data;
	printf("%d\n", a);
}

int main(int argc, char **argv)
{
	THB_BST *bst = malloc(sizeof(THB_BST));

	THB_bst_create(bst, sizeof(int), NULL);

	int x;

       	x = 4;
	THB_bst_insert(bst, x, &x);

       	x = 3;
	THB_bst_insert(bst, x, &x);

       	x = 6;
	THB_bst_insert(bst, x, &x);

	x = 5;
	THB_bst_insert(bst, x, &x);

	x = 7;
	THB_bst_insert(bst, x, &x);

       	x = 2;
	THB_bst_insert(bst, x, &x);

	/*THB_bst_walk(bst, fn);*/

	THB_BSTNode *node = bst->root;
	node = THB_bst_min(node);

	assert(node != NULL);
	assert(*(int*)node->data == 2);

	node = bst->root;
	node = THB_bst_predecessor(node);

	assert(node != NULL);
	assert(*(int*)node->data == 3);

	node = THB_bst_successor(node);
	node = THB_bst_successor(node);

	assert(node != NULL);
	assert(*(int*)node->data == 5);

	THB_bst_remove(bst, 4, NULL);

	THB_bst_walk(bst, fn);

	THB_bst_destroy(bst);
	free(bst);

	return 0;
}
