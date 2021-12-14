#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/functions.h"

int insertAVL(int inKey, Node **pt, int h) {

    if(*pt == NULL) {
        Node *new = (Node*)malloc(sizeof(Node));
        new->key = inKey;
        new->bal = 0;
        new->left = NULL;
        new->right = NULL;
        *pt = new;
        h = 1;
    }
    else {
        if((*pt)->key == inKey) {
            puts("Found element!");
            exit(1);
        }
        else if(inKey < (*pt)->key) {
            h = insertAVL(inKey,(*pt)->left, h);
            if(h == 1) {
                switch ((*pt)->bal) {
                    case 1: 
                        (*pt)->bal = 0;
                        h = 0;
                        break;
                    case 0: 
                        (*pt)->bal = -1;
                        break;
                    case -1:
                        h = rotate1(&pt, h);
                        break;
                }
            }
        }
        else {
            h = insertAVL(inKey,(*pt)->right, h);
            if(h == 1) {
                switch ((*pt)->bal) {
                    case 1: 
                        (*pt)->bal = 0;
                        h = 0;
                        break;
                    case 0: 
                        (*pt)->bal = 1;
                        break;
                    case -1:
                        h = rotate2(&pt, h);
                        break;
                }
            }
        }
    }
    return h;
}

