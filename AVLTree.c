#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVLTree.h"


AVLNode *avl_createNode(int value) {
    AVLNode *node = malloc(sizeof(AVLNode));
    node->value = value;
    node->count = 1;
    node->height = 0;
    node->left = node->right = node->parent = NULL;

    return node;
}

int avl_getHeight(AVLNode *node) {
    return (node == NULL) ? -1 : node->height;
}

int avl_getBalance(AVLNode *node) {
    return avl_getHeight(node->left) - avl_getHeight(node->right);
}

void avl_rotateLeft(AVLNode **root, AVLNode *x) {
    
    AVLNode *y = x->right;
    if (y) {
        x->right = y->left;
        if (y->left) { y->left->parent = x; }
        y->parent = x->parent;
    }
    if (!x->parent) { *root = y; }
    else if (x == x->parent->left) { x->parent->left = y; }
    else { x->parent->right = y; }
    if (y) { y->left = x; }

    x->parent = y;
    x->height = max(avl_getHeight(x->left), avl_getHeight(x->right)) + 1;
    if (y) { y->height = max(avl_getHeight(y->left), avl_getHeight(y->right)) + 1; }
}

void avl_rotateRight(AVLNode **root, AVLNode *x) {
    
    AVLNode *y = x->left;
    if (y) {
        x->left = y->right;
        if (y->right) { y->right->parent = x; }
        y->parent = x->parent;
    }
    if (!x->parent) { *root = y; }
    else if (x == x->parent->left) { x->parent->left = y; }
    else { x->parent->right = y; }
    if (y) { y->right = x; }

    x->parent = y;
    x->height = max(avl_getHeight(x->left), avl_getHeight(x->right)) + 1;
    if (y) { y->height = max(avl_getHeight(y->left), avl_getHeight(y->right)) + 1; }
}

void avl_balance(AVLNode **root, AVLNode *x) {

    while (x) {

        x->height = max(avl_getHeight(x->left), avl_getHeight(x->right)) + 1;
        int balanceFactor = avl_getBalance(x);

        if (balanceFactor > 1) {
            if (avl_getHeight(x->left->left) >= avl_getHeight(x->left->right)) {
                avl_rotateRight(root, x);
            } else {
                avl_rotateLeft(root, x->left);
                avl_rotateRight(root, x);
            }
        }

        if (balanceFactor < -1) {
            if (avl_getHeight(x->right->right) >= avl_getHeight(x->right->left)) {
                avl_rotateLeft(root, x);
            } else {
                avl_rotateRight(root, x->right);
                avl_rotateLeft(root, x);
            }
        }

        x = x->parent;
    }
}

void avl_insert(AVLNode **root, int value) {
    AVLNode *x = *root;
    AVLNode *p = NULL;
    while (x) {
        p = x;
        if (value > x->value) { x = x->right; }
        else if (value < x->value) { x = x->left; }
        else { x->count++; return; }
    }
    x = avl_createNode(value);
    if (!p) { *root = x; }
    else if (value > p->value) { p->right = x; }
    else { p->left = x; }
    x->parent = p;
    avl_balance(root, x);
}

AVLNode *avl_search(AVLNode *root, int value) {
    
    AVLNode *current = root;

    while (current != NULL) {
        if (value == current->value) {
            return current;
        } else if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return NULL;
}

void avl_deleteNode(AVLNode *root, int value) {

    AVLNode *x = avl_search(root, value);
    if (!x) { return; }

    if (!x->left && !x->right) {

        if (x == root) { root = NULL; }

        if (x == x->parent->left) {
            x->parent->left = NULL;
        } else {
            x->parent->right = NULL;
        }

    } else if (!x->left) {

        AVLNode *child = x->right;
        if (x == root) {
            root = child;
        } else if (x == x->parent->left) {
            x->parent->left = child;
        } else {
            x->parent->right = child;
        }
        child->parent = x->parent;

    } else if (!x->right) {
        
        AVLNode *child = x->left;
        if (x == root) {
            root = child;
        } else if (x == x->parent->left) {
            x->parent->left = child;
        } else {
            x->parent->right = child;
        }
        child->parent = x->parent;

    } else {

        // find inorder predecessor
        AVLNode *pred = x->left;
        while (pred->right) { pred = pred->right; }

        x->value = pred->value;
        x->count = pred->count;

        if (pred->left) {
            if (pred == pred->parent->left) { pred->parent->left = pred->left; }
            else { pred->parent->right = pred->right; }
            pred->left->parent = pred->parent;
        } else {
            if (pred == pred->parent->left) { pred->parent->left = NULL; }
            else { pred->parent->right = NULL; }
        }
        x = pred->parent;
    }

    avl_balance(&root, x);
}

void avl_inorderTraversal(AVLNode *root, void (*task)()) {

    if (root == NULL) { return; }

    AVLNode *curr, *pre;

    curr = root;
    while (curr != NULL) {

        if (curr->left == NULL) {
            task(curr);
            curr = curr->right;
        } else {

            AVLNode *prev = curr->left;
            while (prev->right != NULL && prev->right != curr) {
                prev = prev->right;
            }

            if (prev->right == NULL) {
                prev->right = curr;
                curr = curr->left;
            } else {
                prev->right = NULL;
                task(curr);
                curr = curr->right;
            }
        }
    }
    printf("\n");
}

void avl_displayTree(AVLNode *root, int space) {

    if (root == NULL) return;

    space += 6;

    avl_displayTree(root->right, space);

    printf("\n");
    for (int i = 0; i < space - 3; i++) {
        printf("  ");
    }
    printf("%d (%d)\n", root->value, root->count);

    avl_displayTree(root->left, space);
}