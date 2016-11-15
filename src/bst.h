#ifndef THB_BST_H
#define THB_BST_H 1

#include <stdlib.h>

typedef struct _BSTNode {
	unsigned int key;
	struct _BSTNode *parent;
	struct _BSTNode *left;
	struct _BSTNode *right;
	void *data;
} THB_BSTNode;

typedef struct {
	size_t item_size;
	void (*destroy)(void *data);
	THB_BSTNode *root;
} THB_BST;

void THB_bst_create(THB_BST *tree, size_t item_size, void (*destroy)(void *data));
void THB_bst_destroy(THB_BST *tree);

void THB_bst_insert(THB_BST *tree, unsigned int key, void *data);
void THB_bst_remove(THB_BST *tree, unsigned int key, void *data);
int THB_bst_search(THB_BST *tree, unsigned int key, void **data);

void THB_bst_walk(THB_BST *tree, void (*fn)(void *data));

THB_BSTNode* THB_bst_successor(THB_BSTNode *node);
THB_BSTNode* THB_bst_predecessor(THB_BSTNode *node);

THB_BSTNode* THB_bst_min(THB_BSTNode *tree);
THB_BSTNode* THB_bst_max(THB_BSTNode *tree);

#endif // THB_BST_H
