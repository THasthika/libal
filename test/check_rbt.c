#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "rbt.h"
#include "queue.h"

int get_rbt_level(AL_RBT *tree, AL_RBT_Node *node) {
    if (node == NULL) return 0;
    int c = 0;
    while (node != tree->root) {
        c++;
        node = node->parent;
    }
    return c;
}

void print_rbt(AL_RBT *tree)
{
    AL_Queue queue;
    AL_Queue *pq = &queue;

    AL_queue_create(pq, sizeof(AL_RBT_Node*), NULL);

    AL_RBT_Node *node = tree->root;

    int plevel = -1, level = 0;
    int val;

    while (node != NULL) {
        level = get_rbt_level(tree, node);
        if (plevel != level) {
            printf("\nlevel %2d:", level);
        }
        memcpy(&val, node->data, sizeof(int));
        if(node->color == AL_RBT_COLOR_BLACK)
            printf("b:");
        else
            printf("r:");
        printf("%d    ", val);
        if (node->left != NULL)
            AL_queue_enqueue(pq, &node->left);
        if (node->right != NULL)
            AL_queue_enqueue(pq, &node->right);

        node = NULL;
        AL_queue_dequeue(pq, &node);
        plevel = level;
    }

    printf("\n");

    AL_queue_destroy(pq);
}

int main(int argc, char **argv)
{

    AL_RBT tree;

    AL_RBT *ptree = &tree;

    AL_rbt_create(ptree, sizeof(int), NULL);

    int a, *b;

    a = 50;
    AL_rbt_insert(ptree, a, &a);

    a = 25;
    AL_rbt_insert(ptree, a, &a);

    a = 75;
    AL_rbt_insert(ptree, a, &a);

    a = 27;
    AL_rbt_insert(ptree, a, &a);

    a = 20;
    AL_rbt_insert(ptree, a, &a);
    print_rbt(ptree);

    a = 100;
    AL_rbt_insert(ptree, a, &a);
    print_rbt(ptree);

    a = 65;
    AL_rbt_insert(ptree, a, &a);
    print_rbt(ptree);

    a = 120;
    AL_rbt_insert(ptree, a, &a);
    print_rbt(ptree);

    a = 99;
    AL_rbt_insert(ptree, a, &a);
    print_rbt(ptree);

    AL_rbt_remove(ptree, 100, &a);
    print_rbt(ptree);

    AL_rbt_remove(ptree, 120, &a);
    print_rbt(ptree);

    // assert(ptree->root->color == AL_RBT_COLOR_BLACK);
    // assert(ptree->root->left->color == AL_RBT_COLOR_RED);
    
    AL_rbt_destroy(ptree);

    return 0;
}