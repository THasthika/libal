#include "rbt.h"

#include <string.h>
#include <stdlib.h>

void THB_rbt_create(THB_RBT *tree, size_t item_size, void (*destroy)(void *data))
{
}

void THB_rbt_destroy(THB_RBT *tree)
{
}

void THB_rbt_insert(THB_RBT *tree, unsigned int key, void *data)
{
}

void THB_rbt_remove(THB_RBT *tree, unsigned int key, void *data)
{
}

int THB_rbt_search(THB_RBT *tree, unsigned int key, void **data)
{
}

void THB_rbt_walk(THB_RBT *tree, void (*fn)(void *data))
{
}

THB_RBTNode* THB_rbt_successor(THB_RBTNode *node)
{
}

THB_RBTNode* THB_rbt_predecessor(THB_RBTNode *node)
{
}

THB_RBTNode* THB_rbt_min(THB_RBTNode *tree)
{
}

THB_RBTNode* THB_rbt_max(THB_RBTNode *tree)
{
}
