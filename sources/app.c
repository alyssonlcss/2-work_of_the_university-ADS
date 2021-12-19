#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/functions.h"

int main() {
    int i, list[] = {20,18,16,14,12,10,1,22,24,26,30,32};
    int tam = sizeof(list)/sizeof(list[0]);
    int sum = 0;
    Node *root = NULL;
    int h;
    
    for (i = 0; i < tam; i++)
        insertAVL(list[i], &root, &h);

    printf("CheckAVL: %d\n", checkAVL(&root));
    printf("HeightAVL: %d\n", height(&root));
    countNodes(root, &sum);
    printf("CountNodes: %d == %d\n", sum, tam);
    outputAVL(&root);
    puts("");




    return 0;
}