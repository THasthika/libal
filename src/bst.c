#include <stdlib.h>
#include <string.h>

#include <assert.h>

#include "stack.h"

#include "bst.h"

#define STACK_INC_SIZE 100

// replace the node a with b and its sub-tree
void bst_transplant(THB_BST *tree, THB_BSTNode *a, THB_BSTNode *b)
{
	if(a->parent == NULL)
		tree->root = b;
	else if(a->parent->left == a)
		a->parent->left = b;
	else
		a->parent->right = b;
	if(b != NULL)
		b->parent = a->parent;

	a->parent = NULL;
}

// replace the node a with b (only the nodes)
void bst_swap(THB_BST *tree, THB_BSTNode *a, THB_BSTNode *b)
{
	if(a == NULL || b == NULL) return;
	unsigned int tk = a->key;
	void *td = malloc(tree->item_size);
	memcpy(td, a->data, tree->item_size);

	a->key = b->key;
	memcpy(a->data, b->data, tree->item_size);

	b->key = tk;
	memcpy(b->data, td, tree->item_size);

	free(td);
}

void bst_remove(THB_BST *tree, THB_BSTNode *node)
{
	if(node->left != NULL && node->right != NULL) {
		THB_BSTNode *succ = THB_bst_successor(node);
		bst_swap(tree, node, succ);
		bst_remove(tree, succ);
		return;
	}

	if(node->right != NULL) {
		bst_transplant(tree, node, node->right);
	} else if(node->left != NULL) {
		bst_transplant(tree, node, node->left);
	}
	
	if(node->parent != NULL)
		if(node->parent->left == node)
			node->parent->left = NULL;
		else
			node->parent->right = NULL;

	node->parent = 0;
	if(tree->destroy)
		tree->destroy(node->data);
	free(node->data);
	free(node);
}

void THB_bst_create(THB_BST *tree, size_t item_size, void (*destroy)(void *data))
{
	tree->item_size = item_size;
	tree->destroy = destroy;
	tree->root = NULL;
}

void THB_bst_destroy(THB_BST *tree)
{
	THB_Stack *stack = malloc(sizeof(THB_Stack));
	THB_stack_create(stack, sizeof(THB_BSTNode*), STACK_INC_SIZE, NULL);

	THB_BSTNode *a;
	THB_BSTNode *b;

	a = tree->root;

	while(a != NULL || THB_stack_size(stack) > 0) {
		while(a != NULL) {
			THB_stack_push(stack, &a);
			a = a->left;
		}

		if(THB_stack_size(stack) <= 0)
			break;

		THB_stack_pop(stack, &b);
		a = b->right;
		if(tree->destroy)
			tree->destroy(b->data);
		free(b->data);
		free(b);
	}

	THB_stack_destroy(stack);
	free(stack);

	tree->destroy = NULL;
	tree->item_size = 0;
	tree->root = 0;
}

void THB_bst_insert(THB_BST *tree, unsigned int key, void *data)
{
	THB_BSTNode *node = tree->root;
	THB_BSTNode *n = node;
	
	THB_BSTNode *new = malloc(sizeof(THB_BSTNode));
	new->key = key;
	new->data = malloc(tree->item_size);
	memcpy(new->data, data, tree->item_size);
	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;

	while(n != NULL) {
		node = n;
		if(node->key > key)
			n = node->left;
		else
			n = node->right;
	}

	if(node == NULL) { // root item case
		tree->root = new;
		return;
	}

	if(key > node->key)
		node->right = new;
	else
		node->left = new;

	new->parent = node;
}

void THB_bst_remove(THB_BST *tree, unsigned int key, void *data)
{
	THB_BSTNode *node = tree->root;
	while(node != NULL && node->key != key)
		if(key > node->key)
			node = node->right;
		else
			node = node->left;
	if(node == NULL) return;

	if(data != NULL)
		memcpy(data, node->data, tree->item_size);

	bst_remove(tree, node);
}

int THB_bst_search(THB_BST *tree, unsigned int key, void *data)
{
	THB_BSTNode *node = tree->root;
	while(node != NULL && node->key != key) {
		if(key > node->key)
			node = node->right;
		else
			node = node->left;
	}
	if(node == NULL) return 0;
	memcpy(data, node->data, tree->item_size);
	return 1;
}

void THB_bst_walk(THB_BST *tree, void (*fn)(void *data))
{
	THB_Stack *stack = malloc(sizeof(THB_Stack));
	THB_stack_create(stack, sizeof(THB_BSTNode*), STACK_INC_SIZE, NULL);

	THB_BSTNode *a;
	THB_BSTNode *b;

	a = tree->root;

	while(a != NULL || THB_stack_size(stack) > 0) {
		while(a != NULL) {
			THB_stack_push(stack, &a);
			a = a->left;
		}

		if(THB_stack_size(stack) <= 0)
			break;

		THB_stack_pop(stack, &b);
		a = b->right;
		if(fn != NULL)
			fn(b);
	}

	THB_stack_destroy(stack);
	free(stack);
}

THB_BSTNode* THB_bst_successor(THB_BSTNode *node)
{
	THB_BSTNode *succ = NULL;
	succ = THB_bst_min(node->right);
	if(succ == NULL && node->parent != NULL && node->parent->left == node)
		succ = node->parent;
	return succ;
}

THB_BSTNode* THB_bst_predecessor(THB_BSTNode *node)
{
	THB_BSTNode *pred = NULL;
	pred = THB_bst_max(node->left);
	if(pred == NULL && node->parent != NULL && node->parent->right == node)
		pred = node->parent;
	return pred;
}

THB_BSTNode* THB_bst_min(THB_BSTNode *tree)
{
	THB_BSTNode *min = tree;
	if(min == NULL) return min;
	while(min->left != NULL)
		min = min->left;
	return min;
}

THB_BSTNode* THB_bst_max(THB_BSTNode *tree)
{
	THB_BSTNode *max = tree;
	if(max == NULL) return max;
	while(max->right != NULL)
		max = max->right;
	return max;
}
