#ifndef AVLTREE_H
#define AVLTREE_H


typedef struct AVLNode {

    int value;
    int count;
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

void avl_insert(AVLNode **root, int value);

AVLNode *avl_search(AVLNode *root, int value);

void avl_deleteNode(AVLNode *root, int value);

void avl_inorderTraversal(AVLNode *root, void (*task)());

void avl_displayTree(AVLNode *root, int space);


#endif