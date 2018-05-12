#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "bst.h"
#include "queue.h"

int get_bst_level(AL_BST *tree, AL_BST_Node *node) {
    if (node == NULL) return 0;
    int c = 0;
    while (node != tree->root) {
        c++;
        node = node->parent;
    }
    return c;
}

void print_bst(AL_BST *tree)
{
    AL_Queue queue;
    AL_Queue *pq = &queue;

    AL_queue_create(pq, sizeof(AL_BST_Node*), NULL);

    AL_BST_Node *node = tree->root;

    int plevel = -1, level = 0;
    int val;

    while (node != NULL) {
        level = get_bst_level(tree, node);
        if (plevel != level) {
            printf("\nlevel %2d:", level);
        }
        memcpy(&val, node->data, sizeof(int));
        printf("%d    ", val);
        if (node->left != NULL)
            AL_queue_enqueue(pq, &node->left);
        if (node->right != NULL)
            AL_queue_enqueue(pq, &node->right);

        node = NULL;
        AL_queue_dequeue(pq, &node);
        plevel = level;
    }

    AL_queue_destroy(pq);
}

int main(int argc, char **argv)
{
    AL_BST tree;

    AL_BST *ptree = &tree;

    AL_bst_create(ptree, sizeof(int), NULL);

    int a = 5;
    AL_bst_insert(ptree, a, &a);

    a = 7;
    AL_bst_insert(ptree, a, &a);

    a = 10;
    AL_bst_insert(ptree, a, &a);

    a = 8;
    AL_bst_insert(ptree, a, &a);

    a = 9;
    AL_bst_insert(ptree, a, &a);

    a = 6;
    AL_bst_insert(ptree, a, &a);

    a = 2;
    AL_bst_insert(ptree, a, &a);

    a = 4;
    AL_bst_insert(ptree, a, &a);

    a = 1;
    AL_bst_insert(ptree, a, &a);

    assert(ptree->count == 9);

    a = 0;

    AL_bst_remove(ptree, 1, &a);

    assert(ptree->count == 8);

    assert(a == 1);

    AL_bst_remove(ptree, 2, &a);

    assert(a == 2);

    assert(ptree->count == 7);

    AL_bst_remove(ptree, 7, &a);

    assert(a == 7);

    assert(ptree->count = 6);

    print_bst(ptree);

    int *b = NULL;

    AL_bst_search(ptree, 6, (void**)&b);

    assert(*b == 6);

    AL_bst_destroy(ptree);

	return 0;
}
