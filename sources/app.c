#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../headers/functions.h"

int main() {
    int i, j;

    srand(time(NULL));
    for (i = 0; i < K; i++) {
        Node *root = NULL;
        int h, sum = 0, *vec = (int*)malloc(sizeof(int)*_10K);

        paInVec(vec, (rand() % 100)+1);
        for(j = 0; j < _10K; j++) {
            insertAVL(vec[j], &root, &h);
        }
        printf("%d. AVL Tree\n", i+1);
        tests(&root, vec, &sum, &h);
        freeAVL(&root);
        free(vec);
    }
    return 0;
}