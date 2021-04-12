#ifndef AL_BST_H
#define AL_BST_H 1

#include "common.h"

typedef struct _AL_BST_Node {
    struct _AL_BST_Node *parent;
    struct _AL_BST_Node *left;
    struct _AL_BST_Node *right;
    int key;
    void *data;
} AL_BST_Node;

typedef struct {
    size_t item_size;
    size_t count;
    void (*destroy)(void *data);
    AL_BST_Node *root;
} AL_BST;

void AL_bst_create(AL_BST *tree, size_t item_size, void (*destroy)(void *data));
void AL_bst_destroy(AL_BST *tree);

void AL_bst_insert(AL_BST *tree, int key, void *data);
void AL_bst_remove(AL_BST *tree, int key, void *data);
int AL_bst_search(AL_BST *tree, int key, void **data);

int AL_bst_max_height(AL_BST *tree);

#endif // AL_BST_H