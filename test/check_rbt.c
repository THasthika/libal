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
        if(node->color == AL_RBT_COLOR_BLACK)
            printf("b:");
        else
            printf("r:");
        printf("%2d <- ", node->key);
        if (node->parent != NULL)
            printf("%2d", node->parent->key);
        else
            printf("root");
        printf("    ");
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

    a = 1;
    AL_rbt_insert(ptree, a, &a);
    print_rbt(ptree);

    a = 2;
    AL_rbt_insert(ptree, a, &a);
    print_rbt(ptree);

    a = 3;
    AL_rbt_insert(ptree, a, &a);
    print_rbt(ptree);

    a = 100;
    AL_rbt_insert(ptree, a, &a);
    print_rbt(ptree);

    a = 99;
    AL_rbt_insert(ptree, a, &a);
    print_rbt(ptree);

    a = 98;
    AL_rbt_insert(ptree, a, &a);
    print_rbt(ptree);

    a = 4;
    AL_rbt_insert(ptree, a, &a);
    print_rbt(ptree);

    a = 5;
    AL_rbt_insert(ptree, a, &a);
    print_rbt(ptree);

    a = 10;
    AL_rbt_insert(ptree, a, &a);
    print_rbt(ptree);

    a = 20;
    AL_rbt_insert(ptree, a, &a);
    print_rbt(ptree);

    a = 30;
    AL_rbt_insert(ptree, a, &a);
    print_rbt(ptree);

    a = 7;
    AL_rbt_insert(ptree, a, &a);
    print_rbt(ptree);

    
    a = 0;

    AL_rbt_remove(ptree, 5, &a);
    print_rbt(ptree);

    AL_rbt_remove(ptree, 7, &a);
    print_rbt(ptree);

    a = 97;
    AL_rbt_insert(ptree, a, &a);
    print_rbt(ptree);

    AL_rbt_remove(ptree, 30, &a);
    print_rbt(ptree);

    AL_rbt_remove(ptree, 97, &a);
    print_rbt(ptree);

    AL_rbt_destroy(ptree);

    return 0;
}