#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/functions.h"

void rotate1I(Node **pt, int *h) {
    Node *ptu = (*pt)->left;

    if(ptu->bal == -1) {
        (*pt)->left = ptu->right;
        ptu->right = (*pt);
        (*pt) = ptu;
        ptu->right->bal = 0;
    }
    else {
        Node *ptv = ptu->right;
        ptu->right = ptv->left;
        ptv->left = ptu;
        (*pt)->left = ptv->right;
        ptv->right = (*pt);

        if(ptv->bal == 1)
            ptu->bal = -1;
        else if(ptv->bal == -1) {
            (*pt)->bal = 1;
            ptu->bal = 0;
        }
        else
            ptu->bal = 0;
        (*pt)->bal = 0;
        (*pt) = ptv;
    }
    (*pt)->bal = 0; *h = 0;
}

void rotate2I(Node **pt, int *h) {
    Node *ptu = (*pt)->right;

    if(ptu->bal == 1) {
        (*pt)->right = ptu->left;
        ptu->left = (*pt);
        (*pt) = ptu;
        ptu->left->bal = 0;
    }
    else {
        Node *ptv = ptu->left;

        ptu->left = ptv->right;
        ptv->right = ptu;
        (*pt)->right = ptv->left;
        ptv->left = (*pt);

        if(ptv->bal == 1) {
            (*pt)->bal = -1;
            ptu->bal = 0;
        }
        else if(ptv->bal == -1) {
            ptu->bal = 1;
        }
        else {
            ptu->bal = 0;
        }
        (*pt)->bal = 0;
        (*pt) = ptv;
    }
    (*pt)->bal = 0; *h = 0;
}


void insertAVL(int inKey, Node **pt, int *h) {
    
    if(*pt == NULL) {
        Node *new = (Node*)malloc(sizeof(Node));
        new->key = inKey;
        new->bal = 0;
        new->left = NULL;
        new->right = NULL;
        (*pt) = new;
        *h = 1;
    }
    else {
        if((*pt)->key == inKey) {
            puts("Found element!");
            return;
        }
        else if(inKey < (*pt)->key) {
            insertAVL(inKey, &(*pt)->left, h);
            if(*h) {
                switch ((*pt)->bal) {
                    case 1: (*pt)->bal = 0; *h = 0;
                        break;
                    case 0: (*pt)->bal = -1;
                        break;
                    case -1: rotate1I(pt, h);
                        break;
                }
            }
        }
        else {
            insertAVL(inKey, &(*pt)->right, h);
            if(*h) {
                switch ((*pt)->bal) {
                    case -1: (*pt)->bal = 0; *h = 0;
                        break;
                    case 0: (*pt)->bal = 1;
                        break;
                    case 1: rotate2I(pt, h);
                        break;
                }
            }
        }
    }
}

void rotate1R(Node **pt, int *h) {
    Node *ptu = (*pt)->left;

    if(ptu->bal <= 0) {
        (*pt)->left = ptu->right;
        ptu->right = (*pt);
        (*pt) = ptu;
        if(ptu->bal == -1) {
            ptu->bal = (*pt)->right->bal = 0;
            *h = 1;
        }
        else {
            ptu->bal = 1;
            (*pt)->right->bal = -1;
            *h = 0;
        }
    }
    else {
        Node * ptv = ptu->right;

        ptu->right = ptv->left;
        ptv->left = ptu;
        (*pt)->left = ptv->right;
        ptv->right = (*pt);
        (*pt) = ptv;
        switch(ptv->bal) {
            case -1: ptu->bal = 0; (*pt)->right->bal = 1;
                break;
            case 0: ptu->bal = 0; (*pt)->right->bal = 0;
                break;
            case 1: ptu->bal = -1; (*pt)->right->bal = 0;
                break;
        }
        (*pt)->bal = 0; *h = 1;
    }
}

void rotate2R(Node **pt, int *h) {
    Node *ptu = (*pt)->right;

    if(ptu->bal >= 0) {
        (*pt)->right = ptu->left;
        ptu->left = (*pt);
        (*pt) = ptu;
        if(ptu->bal == 1) {
            ptu->bal = (*pt)->left->bal = 0;
            *h = 1;
        }
        else {
            ptu->bal = -1;
            (*pt)->left->bal = 1;
            *h = 0;
        }
    }
    else {
        Node * ptv = ptu->left;

        ptu->left = ptv->right;
        ptv->right = ptu;
        (*pt)->right = ptv->left;
        ptv->left = (*pt);
        (*pt) = ptv;

        switch(ptv->bal) {
            case -1:
                ptu->bal = 0; (*pt)->left->bal = -1;
                break;
            case 0:
                ptu->bal = 0; (*pt)->left->bal = 0;
                break;
            case 1:
                ptu->bal = 1; (*pt)->left->bal = 0;
                break;
        }
        (*pt)->bal = 0; *h = 1;
    }
}

 void swap(Node **pt, Node **dadS) {
    Node *temp;

    temp = (*pt);
    (*pt) = (*dadS);
    (*dadS) = temp;

    temp->bal = (*pt)->bal;
    temp->key = (*pt)->key;
    temp->left = (*pt)->left;
    temp->right = (*pt)->right;

    //swap
    (*pt)->bal = (*dadS)->bal;
    (*pt)->key = (*dadS)->key;
    (*pt)->left = (*dadS)->left;
    (*pt)->right = (*dadS)->right;

    (*dadS)->bal = temp->bal;
    (*dadS)->key = temp->key;
    (*dadS)->left = temp->left;
    (*dadS)->right = temp->right;

}

void balance(Node **pt, char where, int *h) {
    if(*h) {
        if(where == 'R') {
            switch((*pt)->bal) {
                case 1: (*pt)->bal = 0;
                    break;
                case 0: (*pt)->bal = -1; (*h) = 0;
                    break;
                case -1: rotate1R(pt, h);
                    break;
            }
        }
        else {
            switch((*pt)->bal) {
                case -1: (*pt)->bal = 0;
                    break;
                case 0: (*pt)->bal = 1; (*h) = 0;
                    break;
                case 1: rotate2R(pt, h);
                    break;
            }
        }
    }
}

void removeAVL(int x, Node **pt, int *h) {
    if((*pt) == NULL){
        puts("element does not exist!");
        *h = 0;
    }
    else {
        if(x < (*pt)->key) {
            removeAVL(x, &(*pt)->left, h);
            balance(pt, 'L', h);
        }
        else {
            if(x > (*pt)->key) {
                removeAVL(x, &(*pt)->right, h);
                balance(pt, 'R', h);
            }
            else {
                Node *aux = (*pt);
                
                if((*pt)->left == NULL) {
                    (*pt) = (*pt)->right;
                    *h = 1;
                }
                else {
                    if((*pt)->right == NULL) {
                        (*pt) = (*pt)->left;
                        *h = 1;
                    }
                    else {
                        Node *s = (*pt)->right;

                        if(s->left == NULL) {
                            s->left = (*pt)->left;
                            s->bal = (*pt)->bal;
                            (*pt) = s;
                            *h = 1;
                        }
                        else {
                            Node *dadS;
                            while(s->left != NULL) {
                                dadS = s;
                                s = s->left;
                            }
                            swap(pt, &dadS->left);
                            removeAVL(x, &(*pt)->right, h);
                        }
                        balance(pt, 'R', h);
                    }
                    free(aux);
                }
            }
        }
    }
}

int height(Node *pt) {
    int hl, hr, diff;
    if(pt == NULL) {
        return 0;
    }
    else {
        hl = height(pt->left);
        hr = height(pt->right);
        if (hl > hr) return hl+1;
        else return hr+1;
    }
}

int checkAVL(Node *pt) {
    int hl, hr, diff, flag;
    if(pt->left != NULL) {
        flag = checkAVL(pt->left);
    }
    if(pt->right != NULL) {
        flag = checkAVL(pt->right);
    }
    hl = height(pt->left);
    hr = height(pt->right);

    diff = hr - hl;

    if(diff >= -1 && diff <= 1) flag = 1;
    else flag = 0;

    return flag;
}

void countNodes(Node *pt, int *sum) {
    if(pt->left != NULL)
        countNodes(pt->left, sum);
    if(pt->right != NULL)   
        countNodes(pt->right, sum);
    *sum += 1;
}

void outputAVL(Node *pt) {
    printf("%d (%d);\n", pt->key, pt->bal);
    if(pt->left != NULL)
        outputAVL(pt->left);
    //printf("%d (%d);\n", pt->key, pt->bal);
    if(pt->right != NULL)   
        outputAVL(pt->right);
    /* printf("%d (%d);\n", pt->key, pt->bal); */
}

void freeAVL(Node **pt) {
    if((*pt)->left != NULL)
        freeAVL(&(*pt)->left);
    if((*pt)->right != NULL)
        freeAVL(&(*pt)->right);

    free(*pt);
}

void paInVec(int *vec, int seed) {
    int i, j;
    for(i = 0, j = 0; i < _10K; i++, j+=seed) {
        vec[i] = j;
    }
}

void tests(Node **pt, int *vec, int *sum, int *h) {
    int i;

    countNodes(*pt, sum);
    printf("\tNumber of Nodes: %d\n",*sum);
    if(checkAVL(*pt)) puts("\tIt's AVL!");
    else puts("\tIt's not AVL!");

    puts("\t1000 nodes removed.");
    for(i = 0; i < K; i++) {
        removeAVL(vec[i], &(*pt), h);
    }
    *sum = 0;
    countNodes(*pt, sum);
    printf("\tNumber of Nodes: %d\n",*sum);
    if(checkAVL(*pt)) printf("\tIt's AVL!\n");
    else printf("\tIt's not AVL!");

}
