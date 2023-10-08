#include <stdio.h>
#include <stdlib.h>

struct Node {
    int c;
    struct Node *prox;
};

void imprime_lista(struct Node *cab);