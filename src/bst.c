#include "common.h"
#include <string.h>

#include "bst.h"

#include "stack.h"

#define AL_BST_STACK_INC_SIZE 10

void bst_swap_node(AL_BST_Node *a, AL_BST_Node *b)
{
    if (a == NULL || b == NULL)
        return;
    void *tmp_data;
    int tmp_key;
    tmp_data = a->data;
    tmp_key = a->key;
    a->data = b->data;
    a->key = b->key;
    b->data = tmp_data;
    b->key = tmp_key;
}

void bst_get_predecessor(AL_BST_Node *node, AL_BST_Node **predecessor)
{
    *predecessor = NULL;
    if (node == NULL) return;
    if (node->left == NULL) {
        if (node->parent == NULL) return;
        *predecessor = node->parent;
        while (*predecessor != NULL && node == (*predecessor)->left) {
            node = *predecessor;
            *predecessor = node->parent;
        }
    } else {
        *predecessor = node->left;
        while ((*predecessor)->right != NULL) {
            *predecessor = (*predecessor)->right;
        }
    }
}

void bst_get_successor(AL_BST_Node *node, AL_BST_Node **successor)
{
    *successor = NULL;
    if (node == NULL) return;
    if (node->right == NULL) {
        if (node->parent == NULL) return;
        *successor = node->parent;
        while (*successor != NULL && node == (*successor)->right) {
            node = *successor;
            *successor = node->parent;
        }
    } else {
        *successor = node->right;
        while ((*successor)->left != NULL) {
            *successor = (*successor)->left;
        }
    }
}

void bst_remove_node(AL_BST *tree, AL_BST_Node *node)
{
    AL_BST_Node *c;
    if (node == NULL) return;
    if (node->right != NULL) {
        bst_get_successor(node, &c);
        bst_swap_node(node, c);
        bst_remove_node(tree, c);
        return;
    }
    if (node->left != NULL) {
        bst_get_predecessor(node, &c);
        bst_swap_node(node, c);
        bst_remove_node(tree, c);
        return;
    }
    if (node->parent != NULL) {
        if (node->parent->left == node) {
            node->parent->left = NULL;
        } else {
            node->parent->right = NULL;
        }
    }
    if (node == tree->root) {
        tree->root = NULL;
    }
    if (tree->destroy != NULL) // destroy function if exist
        tree->destroy(node->data);
    node->parent = node->left = node->right = NULL;
    free(node->data);
    node->data = NULL;
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