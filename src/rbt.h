#ifndef THB_RBT_H
#define THB_RBT_H 1

#include <stdlib.h>

typedef struct _THB_RBTNode {
	struct _THB_RBTNode *parent;
	struct _THB_RBTNode *left;
	struct _THB_RBTNode *right;
	unsigned int key;
	enum {red, black} color;
	void *data;
} THB_RBTNode;

typedef struct {
	size_t item_size;
	void (*destroy)(void *data);
	THB_RBTNode *root;
} THB_RBT;

void THB_rbt_create(THB_RBT *tree, size_t item_size, void (*destroy)(void *data));
void THB_rbt_destroy(THB_RBT *tree);

void THB_rbt_insert(THB_RBT *tree, unsigned int key, void *data);
void THB_rbt_remove(THB_RBT *tree, unsigned int key, void *data);
int THB_rbt_search(THB_RBT *tree, unsigned int key, void **data);

void THB_rbt_walk(THB_RBT *tree, void (*fn)(void *data));

THB_RBTNode* THB_rbt_successor(THB_RBTNode *node);
THB_RBTNode* THB_rbt_predecessor(THB_RBTNode *node);

THB_RBTNode* THB_rbt_min(THB_RBTNode *tree);
THB_RBTNode* THB_rbt_max(THB_RBTNode *tree);

#endif // THB_RBT_H
