#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct node {
    int key;
    int bal;
    struct node *right;
    struct node *left;
};
typedef struct node Node;

int insertAVL(int inKey, Node **pt, int h);


#endif