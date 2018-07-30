#include "common.h"
#include <string.h>

#include "rbt.h"

#include "stack.h"

#define AL_RBT_STACK_INC_SIZE 10

#define rbt_is_double_black(node) (node->color == AL_RBT_COLOR_DOUBLE_BLACK)
#define rbt_is_black(node) (node == NULL || rbt_is_double_black(node) || node->color == AL_RBT_COLOR_BLACK)
#define rbt_is_red(node) (!rbt_is_black(node))

// transplant v in the place of u
void rbt_transplant(AL_RBT *tree, AL_RBT_Node *u, AL_RBT_Node *v)
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

void rbt_minimum(AL_RBT_Node *node, AL_RBT_Node **min)
{
    *min = node;
    while ((*min)->left != NULL) {
        *min = (*min)->left;
    }
}

void rbt_maximum(AL_RBT_Node *node, AL_RBT_Node **max)
{
    *max = node;
    while ((*max)->right != NULL) {
        *max = (*max)->right;
    }
}

void rbt_left_rotate(AL_RBT *tree, AL_RBT_Node *node)
{
    if (node == NULL) return;
    AL_RBT_Node *y = node->right;
    node->right = y->left;
    if (y->left != NULL) {
        y->left->parent = node;
    }
    y->parent = node->parent;
    if (node->parent == NULL) {
        tree->root = y;
    } else if (node == node->parent->left) {
        node->parent->left = y;
    } else {
        node->parent->right = y;
    }
    y->left = node;
    node->parent = y;
}

void rbt_right_rotate(AL_RBT *tree, AL_RBT_Node *node)
{
    if (node == NULL) return;
    AL_RBT_Node *y = node->left;
    node->left = y->right;
    if (y->right != NULL) {
        y->right->parent = node;
    }
    y->parent = node->parent;
    if (node->parent == NULL) {
        tree->root = y;
    } else if (node == node->parent->left) {
        node->parent->left = y;
    } else {
        node->parent->right = y;
    }
    y->right = node;
    node->parent = y;
}

void rbt_insert_fixup(AL_RBT *tree, AL_RBT_Node *node)
{
    AL_RBT_Node *u = NULL;

    while (node != NULL && node != tree->root && rbt_is_red(node->parent))
    {
        u = NULL;
        // parent is left child of grand parent
        if (node->parent->parent != NULL && node->parent == node->parent->parent->left)
        {
            u = node->parent->parent->right;
            if (rbt_is_red(u))
            {
                node->parent->parent->color = AL_RBT_COLOR_RED;
                node->parent->color = AL_RBT_COLOR_BLACK;
                u->color = AL_RBT_COLOR_BLACK;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rbt_left_rotate(tree, node);
                }
                node->parent->color = AL_RBT_COLOR_BLACK;
                node->parent->parent->color = AL_RBT_COLOR_RED;
                rbt_right_rotate(tree, node->parent->parent);
            }
        } else {
            if (node->parent->parent != NULL) u = node->parent->parent->left;
            if (rbt_is_red(u))
            {
                node->parent->parent->color = AL_RBT_COLOR_RED;
                node->parent->color = AL_RBT_COLOR_BLACK;
                u->color = AL_RBT_COLOR_BLACK;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rbt_right_rotate(tree, node);
                }
                node->parent->color = AL_RBT_COLOR_BLACK;
                node->parent->parent->color = AL_RBT_COLOR_RED;
                rbt_left_rotate(tree, node->parent->parent);
            }
        }
    }
    tree->root->color = AL_RBT_COLOR_BLACK;
}

void rbt_delete_fixup(AL_RBT *tree, AL_RBT_Node *node)
{
    AL_RBT_Node *w;
    while (node != tree->root && rbt_is_black(node))
    {
        w = NULL;
        if (node == node->parent->left) {
            w = node->parent->right;
            if (rbt_is_red(w)) {
                w->color = AL_RBT_COLOR_BLACK;
                w->parent->color = AL_RBT_COLOR_RED;
                rbt_left_rotate(tree, node->parent);
                w = node->parent->right;
            }
            if (w != NULL && rbt_is_black(w->left) && rbt_is_black(w->right)) {
                w->color = AL_RBT_COLOR_RED;
                node = node->parent;
            } else if (w != NULL) {
                if (rbt_is_black(w->right)) {
                    if (w->left != NULL) w->left->color = AL_RBT_COLOR_BLACK;
                    w->color = AL_RBT_COLOR_RED;
                    rbt_right_rotate(tree, w);
                    w = node->parent->right;
                }
                w->color = node->parent->color;
                node->parent->color = AL_RBT_COLOR_BLACK;
                if (w->right != NULL) w->right->color = AL_RBT_COLOR_BLACK;
                rbt_left_rotate(tree, node->parent);
                node = tree->root;
            }
        } else {
            w = node->parent->left;
            if (rbt_is_red(w)) {
                w->color = AL_RBT_COLOR_BLACK;
                w->parent->color = AL_RBT_COLOR_RED;
                rbt_right_rotate(tree, node->parent);
                w = node->parent->left;
            }
            if (w != NULL && rbt_is_black(w->left) && rbt_is_black(w->right)) {
                w->color = AL_RBT_COLOR_RED;
                node = node->parent;
            } else if (w != NULL) {
                if (rbt_is_black(w->left)) {
                    if (w->right != NULL) w->right->color = AL_RBT_COLOR_BLACK;
                    w->color = AL_RBT_COLOR_RED;
                    rbt_left_rotate(tree, w);
                    w = node->parent->left;
                }
                w->color = node->parent->color;
                node->parent->color = AL_RBT_COLOR_BLACK;
                if (w->left != NULL) w->left->color = AL_RBT_COLOR_BLACK;
                rbt_right_rotate(tree, node->parent);
                node = tree->root;
            }
        }
    }
    node->color = AL_RBT_COLOR_BLACK;
}

void rbt_remove_node(AL_RBT *tree, AL_RBT_Node *node)
{
    AL_RBT_Node *y = node;
    AL_RBT_Node *x;
    AL_RBT_Node *y_org_parent;
    char y_org_color = y->color;

    if (node->left == NULL && node->right != NULL) {
        x = node->right;
        rbt_transplant(tree, node, node->right);
    } else if (node->left != NULL && node->right == NULL) {
        x = node->left;
        rbt_transplant(tree, node, node->left);
    } else if (node->left != NULL && node->right != NULL) {
        rbt_minimum(node->right, &y);
        y_org_color = y->color;
        y_org_parent = y->parent;
        x = y->right;
        if (y->parent == node) {
            if (x != NULL) x->parent = y;
            y_org_parent = y;
        } else {
            rbt_transplant(tree, y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        rbt_transplant(tree, node, y);
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
        if (x == NULL) {
            x = node;
            x->parent = y_org_parent;
            x->color = AL_RBT_COLOR_DOUBLE_BLACK;
            if (x->parent == y) {
                x->parent->right = x;
            } else {
                x->parent->left = x;
            }
        }
    } else {
        if (!rbt_is_red(x)) {
            x = node;
            x->color = AL_RBT_COLOR_DOUBLE_BLACK;
        }
    }

    if (tree->destroy != NULL)
        tree->destroy(node->data);
    free(node->data);
    node->data = NULL;

    if (y_org_color == AL_RBT_COLOR_BLACK)
        rbt_delete_fixup(tree, x);

    if (node->parent != NULL) {
        if (node == node->parent->left) {
            node->parent->left = NULL;
        } else if (node == node->parent->right) {
            node->parent->right = NULL;
        }
    }

    node->parent = node->left = node->right = NULL;
    free(node);
}

void AL_rbt_create(AL_RBT *tree, size_t item_size, void (*destroy)(void *data))
{
    tree->item_size = item_size;
    tree->destroy = destroy;
    tree->root = NULL;
    tree->count = 0;
}

void AL_rbt_destroy(AL_RBT *tree)
{
    AL_Stack stack;
    AL_RBT_Node *node;
    if (tree->count != 0 && tree->root != NULL) {
        AL_stack_create(&stack, sizeof(AL_RBT_Node*), AL_RBT_STACK_INC_SIZE, NULL);
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

void AL_rbt_insert(AL_RBT *tree, int key, void *data)
{
    AL_RBT_Node *node = malloc(sizeof(AL_RBT_Node));
    node->parent = node->left = node->right = NULL;
    node->key = key;
    node->color = AL_RBT_COLOR_RED;
    node->data = malloc(tree->item_size);
    memcpy(node->data, data, tree->item_size);

    tree->count++; // increment tree node count

    AL_RBT_Node *p = tree->root;

    if (p == NULL) { // case where tree is empty
        tree->root = node;
    } else {
        // otherwise traverse the tree to find the right place
        // for the node
        while (p != NULL) {
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

    // fixing the tree to keep the Red Black Property
    rbt_insert_fixup(tree, node);
}

void AL_rbt_remove(AL_RBT *tree, int key, void *data)
{
    AL_RBT_Node *n;
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

    rbt_remove_node(tree, n);

    tree->count--;
}

int AL_rbt_search(AL_RBT *tree, int key, void **data)
{
    AL_RBT_Node *n = tree->root;
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

int rbt_max_height_aux(AL_RBT_Node *node)
{
    if (node == NULL) return 0;
    int h = 1;
    int lh = rbt_max_height_aux(node->left);
    int rh = rbt_max_height_aux(node->right);
    if (lh > rh) {
        h += lh;
    } else {
        h += rh;
    }
    return h;
}

int AL_rbt_max_height(AL_RBT *tree)
{
    return rbt_max_height_aux(tree->root);
}