#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "bst.h"

int main(int argc, char **argv)
{
    AL_BST tree;

    AL_BST *ptree = &tree;

    AL_bst_create(ptree, sizeof(int), NULL);

    int a = 5;
    AL_bst_insert(ptree, a, &a);

    a = 7;
    AL_bst_insert(ptree, a, &a);

    a = 8;
    AL_bst_insert(ptree, a, &a);

    a = 6;
    AL_bst_insert(ptree, a, &a);

    a = 2;
    AL_bst_insert(ptree, a, &a);

    a = 4;
    AL_bst_insert(ptree, a, &a);

    a = 1;
    AL_bst_insert(ptree, a, &a);

    assert(ptree->count == 7);

    a = 0;

    AL_bst_remove(ptree, 7, &a);

    assert(ptree->count == 6);

    assert(a == 7);

    AL_bst_remove(ptree, 5, &a);

    assert(a == 5);

    assert(ptree->count == 5);

    int *b = NULL;

    AL_bst_search(ptree, 6, (void**)&b);

    assert(*b == 6);

    AL_bst_destroy(ptree);

	return 0;
}
