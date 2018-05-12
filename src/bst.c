#include "common.h"
#include <string.h>

#include "bst.h"

#include "stack.h"

void AL_bst_create(AL_BST *tree, size_t item_size, void (*destroy)(void *data))
{
    tree->item_size = item_size;
    tree->destroy = destroy;
    tree->root = NULL;
    tree->count = 0;
}

void AL_bst_destroy(AL_BST *tree)
{
    if (tree->count != 0 && tree->root != NULL) {
        AL_Stack *stack;
        AL_stack_create(stack, sizeof(AL_BST_Node*), ((tree->count) / 2) + 1, NULL);
        AL_BST_Node *node = tree->root;
        while (node != NULL) {
            if (node->left != NULL)
                AL_stack_push(stack, node->left);
            if (node->right != NULL)
                AL_stack_push(stack, node->right);
            if (tree->destroy != NULL)
                tree->destroy(node->data);
            free(node);
            node = NULL;
            AL_stack_pop(stack, node);
        }
    }
    tree->destroy = NULL;
    tree->root = NULL;
    tree->item_size = 0;
    tree->count = 0;
}

void AL_bst_insert(AL_BST *tree, int key, void *data)
{
    AL_BST_Node *node = malloc(sizeof(AL_BST_Node));
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->key = key;
    node->data = malloc(tree->item_size);
    memcpy(node->data, data, tree->item_size);

    AL_BST_Node *p = tree->root;
    AL_BST_Node *pn = p;

    if (p == NULL) { // case where tree is empty
        tree->root = node;
        return;
    }

    // otherwise traverse the tree to find the right place
    // for the node
    while (pn != NULL) {
        if (node->key > p->key) {
            pn = p->right;
            if (pn == NULL)
                p->right = node;
        } else {
            pn = p->left;
            if (pn == NULL)
                p->left = node;
        }
        p = pn;
    }
}

// void AL_bst_remove(AL_BST *tree, int key, void *data);
// void AL_bst_search(AL_BST *tree, int key, void **data);