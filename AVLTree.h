#ifndef AVLTREE_H
#define AVLTREE_H


typedef struct AVLNode {

    int value;
    unsigned int count;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
    struct AVLNode *parent;
} AVLNode;

typedef struct AVLTree {

    AVLNode *root;
} AVLTree;

AVLNode *avl_createNode(int value);


#define max(a,b) (((a) > (b)) ? (a) : (b))

int avl_getHeight(AVLNode *node);

int avl_getBalance(AVLNode *node);

void avl_rotateLeft(AVLNode **root, AVLNode *x);

void avl_rotateRight(AVLNode **root, AVLNode *x);

void avl_balance(AVLNode **root, AVLNode *x);

void avl_insert(AVLTree *tree, int value);

AVLNode *avl_search(AVLTree tree, int value);

void avl_deleteNode(AVLTree *tree, int value);

void avl_inorderTraversal(AVLTree tree, void (*task)());

void avl_displayTree(AVLNode *root, int space);


#endif