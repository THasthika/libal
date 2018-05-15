#ifndef AL_RBT_H
#define AL_RBT_H 1

#include "common.h"

#define AL_RBT_COLOR_RED 0x01
#define AL_RBT_COLOR_BLACK 0x03
#define AL_RBT_COLOR_DOUBLE_BLACK 0x04

typedef struct _AL_RBT_Node {
    struct _AL_RBT_Node *parent;
    struct _AL_RBT_Node *left;
    struct _AL_RBT_Node *right;
    char color;
    int key;
    void *data;
} AL_RBT_Node;

typedef struct {
    size_t item_size;
    size_t count;
    void (*destroy)(void *data);
    AL_RBT_Node *root;
} AL_RBT;

void AL_rbt_create(AL_RBT *tree, size_t item_size, void (*destroy)(void *data));
void AL_rbt_destroy(AL_RBT *tree);

void AL_rbt_insert(AL_RBT *tree, int key, void *data);
void AL_rbt_remove(AL_RBT *tree, int key, void *data);
int AL_rbt_search(AL_RBT *tree, int key, void **data);

#endif // AL_RBT_H