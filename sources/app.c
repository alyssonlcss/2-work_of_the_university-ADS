#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../headers/functions.h"

int main() {
    int i, j;
    srand(time(NULL));
    for (i = 0; i < 10; i++) {
        Node *root = NULL;
        int h, sum = 0, *vec = (int*)malloc(sizeof(int)*_10K);
        paInVec(vec, (rand() % 100)+1);
        for(j = 0; j < _10K; j++) {
            insertAVL(vec[j], &root, &h);
        }
        printf("%d. AVL Tree\n", i);
        tests(&root, vec, &sum, &h);
        freeAVL(&root);
        free(vec);
    }
    

    /* if(root != NULL) {
        outputAVL(root);
        printf("CheckAVL: %d\n", checkAVL(root));
        printf("HeightAVL: %d\n", height(root));
        countNodes(root, &sum);
        printf("CountNodes: %d\n", sum);
    }
    else {
        puts("Non-existent tree!");
    } */




    return 0;
}