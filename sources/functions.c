#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/functions.h"

int rotate1I(Node ***pt, int h) {
    Node *ptu = (**pt)->left;

    if(ptu->bal == -1) {
        (**pt)->left = ptu->right;
        ptu->right = (**pt);
        (**pt) = ptu;
        ptu->right->bal = 0;
    }
    else {
        Node *ptv = ptu->right;
        ptu->right = ptv->left;
        ptv->left = ptu;
        (**pt)->left = ptv->right;
        ptv->right = (**pt);
        if(ptv->bal == 1) {
            (**pt)->bal = 0;
            ptu->bal = -1;
        }
        else {
            (**pt)->bal = 1;
            ptu->bal = 0;
        }
        (**pt) = ptv;
    }
    (**pt)->bal = 0; h = 0;
    return h;
}

//implementar de forma análoga ao rotate1
int rotate2I(Node ***pt, int *h) {
    

    return h;
}



void removeAVL(int x, Node **pt, int *h) {
    if((*pt) == NULL){
        puts("element does not exist!");
        *h = 0;
    }
    else {
        if(x < (*pt)->key) {
            removeAVL(x, (*pt)->left, &h);
            balance((*pt), "L", &h);
        }
        else {
            if(x > (*pt)->key) {
                removeAVL(x, (*pt)->right, &h);
                balance((*pt), "R", &h);
            }
            else {
                Node *aux = (*pt);
                
                if((*pt)->left == NULL) {
                    (*pt) = (*pt)->right;
                    h = 1;
                }
                else {
                    if((*pt)->right == NULL) {
                        (*pt) = (*pt)->left;
                        h = 1;
                    }
                    else {
                        Node *s = (*pt)->right;

                        if(s->left == NULL) {
                            s->left = (*pt)->left;
                            s->bal = (*pt)->bal;
                            (*pt) = s;
                            h = 1;
                        }
                        else {
                            Node *dadS;
                            while(s->left != NULL) {
                                dadS = s;
                                s = s->left;
                            }
                            aux = dadS;
                            dadS = (*pt);
                            (*pt) = aux;
                            removeAVL(x, (*pt)->right, &h);
                        }
                        balance((*pt), "R", &h);
                    }
                }
            }
        }
    }
}

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
                        h = rotate1I(&pt, h);
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
                        h = rotate2I(&pt, h);
                        break;
                }
            }
        }
    }
    return h;
}

