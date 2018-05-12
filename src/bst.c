#include "common.h"
#include <string.h>

#include "bst.h"

#include "stack.h"

#define AL_BST_STACK_INC_SIZE 10

// transplant v in the place of u
void bst_transplant(AL_BST *tree, AL_BST_Node *u, AL_BST_Node *v)
{
    if (u->parent == NULL)
        tree->root = v;
    else if (u->parent->left == u)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != NULL)
        v->parent = u->parent;
}

void bst_minimum(AL_BST_Node *node, AL_BST_Node **min)
{
    *min = node;
    while ((*min)->left != NULL) {
        *min = (*min)->left;
    }
}

void bst_maximum(AL_BST_Node *node, AL_BST_Node **max)
{
    *max = node;
    while ((*max)->right != NULL) {
        *max = (*max)->right;
    }
}

void bst_get_predecessor(AL_BST_Node *node, AL_BST_Node **predecessor)
{
    *predecessor = NULL;
    if (node == NULL) return;
    if (node->left == NULL) {
        if (node->parent == NULL) return;
        *predecessor = node;
        node = node->parent;
        while (node != NULL && *predecessor == node->left) {
            *predecessor = node;
            node = node->parent;
        }
    } else {
        bst_maximum(node->left, predecessor);
    }
}

void bst_get_successor(AL_BST_Node *node, AL_BST_Node **successor)
{
    *successor = NULL;
    if (node == NULL) return;
    if (node->right == NULL) {
        if (node->parent == NULL) return;
        *successor = node;
        node = node->parent;
        while (node != NULL && *successor == node->right) {
            *successor = node;
            node = node->parent;
        }
    } else {
        bst_minimum(node->right, successor);
    }
}

void bst_remove_node(AL_BST *tree, AL_BST_Node *node)
{
    AL_BST_Node *y = NULL;
    if (node->left == NULL && node->right != NULL) {
        bst_transplant(tree, node, node->right);
    } else if (node->left != NULL && node->right == NULL) {
        bst_transplant(tree, node, node->left);
    } else if (node->left != NULL && node->right != NULL) {
        bst_minimum(node->right, &y);
        if (y != NULL && y->parent != node) {
            bst_transplant(tree, y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        bst_transplant(tree, node, y);
        y->left = node->left;
        y->left->parent = y;
    } else {
        if (node->parent != NULL) {
            if (node->parent->left == node)
                node->parent->left = NULL;
            else
                node->parent->right = NULL;
        }
    }
    if (tree->destroy != NULL)
        tree->destroy(node->data);
    free(node->data);
    node->data = NULL;
    node->parent = node->left = node->right = NULL;
    free(node);
}

void AL_bst_create(AL_BST *tree, size_t item_size, void (*destroy)(void *data))
{
    tree->item_size = item_size;
    tree->destroy = destroy;
    tree->root = NULL;
    tree->count = 0;
}

void AL_bst_destroy(AL_BST *tree)
{
    AL_Stack stack;
    AL_BST_Node *node;
    if (tree->count != 0 && tree->root != NULL) {
        AL_stack_create(&stack, sizeof(AL_BST_Node*), AL_BST_STACK_INC_SIZE, NULL);
        node = tree->root;
        while (node != NULL) {
            if (node->left != NULL)
                AL_stack_push(&stack, &node->left);
            if (node->right != NULL)
                AL_stack_push(&stack, &node->right);
            if (tree->destroy != NULL)
                tree->destroy(node->data);
            free(node->data);
            free(node);
            node = NULL;
            AL_stack_pop(&stack, &node);
        }
        AL_stack_destroy(&stack);
    }
    tree->destroy = NULL;
    tree->root = NULL;
    tree->item_size = 0;
    tree->count = 0;
}

void AL_bst_insert(AL_BST *tree, int key, void *data)
{
    AL_BST_Node *node = malloc(sizeof(AL_BST_Node));
    node->parent = node->left = node->right = NULL;
    node->key = key;
    node->data = malloc(tree->item_size);
    memcpy(node->data, data, tree->item_size);

    tree->count++; // increment tree node count

    AL_BST_Node *p = tree->root;

    if (p == NULL) { // case where tree is empty
        tree->root = node;
        return;
    }

    // otherwise traverse the tree to find the right place
    // for the node
    while (1) {
        if (node->key > p->key) {
            if (p->right == NULL) {
                node->parent = p;
                p->right = node;
                break;
            }
            p = p->right;
        } else {
            if (p->left == NULL) {
                node->parent = p;
                p->left = node;
                break;
            }
            p = p->left;
        }
    }
}

void AL_bst_remove(AL_BST *tree, int key, void *data)
{
    AL_BST_Node *n;
    n = tree->root;

    while (n != NULL && n->key != key) {
        if (key > n->key) {
            n = n->right;
        } else {
            n = n->left;
        }
    }

    if (n == NULL) return;

    if (data != NULL)
        memcpy(data, n->data, tree->item_size);

    bst_remove_node(tree, n);

    tree->count--;
}

int AL_bst_search(AL_BST *tree, int key, void **data)
{
    AL_BST_Node *n = tree->root;
    while (n != NULL && n->key != key) {
        if (key > n->key) {
            n = n->right;
        } else {
            n = n->left;
        }
    }
    if (n == NULL) return 0;
    *data = n->data;
    return  1;
}