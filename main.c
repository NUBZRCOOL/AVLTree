#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVLTree.h"



void doPrint(AVLNode *node) {
    for (int i = 1; i <= node->count; i++) {
        printf("%d ", node->value);
    }
}

int main() {

    int num = 80;
    
    int upper = 100;
    int lower = 0;
    int total = 50;
    AVLNode *val;
    time_t t;

    srand((unsigned int) time(&t));

    AVLTree tree = {NULL};

    for (int i = 0; i < total; i++) {

        int beruh = (rand() % ( upper - lower + 1) + lower);
        avl_insert(&tree, beruh);
    }

    avl_displayTree(tree.root, 0);

    // avl_deleteNode(&tree, 5);
    printf("-----------------------------------------------------------------------------\n");

    // avl_displayTree(tree.root, 0);

    printf("Nodes in order: ");
    avl_inorderTraversal(tree, doPrint);
    printf("Tree depth: %d \n", tree.root->height + 1);

    val = avl_search(tree, num);
    val != NULL ? printf("%d was found %d times\n", num, val->count) : printf("%d was not found\n", num);

    return 0;
}