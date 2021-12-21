#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/functions.h"

int main() {
    int i, list[] = {20,18,14,12,10,1,24,26,30,32};
    int tam = sizeof(list)/sizeof(list[0]);
    int h, sum = 0;
    Node *root = NULL;
    
    for (i = 0; i < tam; i++)
        insertAVL(list[i], &root, &h);

    for (i = 5; i < tam; i++)
        removeAVL(list[i], &root, &h);

    if(root != NULL) {
        outputAVL(root);
        printf("CheckAVL: %d\n", checkAVL(root));
        printf("HeightAVL: %d\n", height(root));
        countNodes(root, &sum);
        printf("CountNodes: %d", sum);
        puts("");
    }
    else {
        puts("Non-existent tree!");
    }




    return 0;
}