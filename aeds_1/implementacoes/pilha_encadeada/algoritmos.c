#include "pilha_encadeada.h"

void imprime_lista(struct Node *cab) {
    if (cab == NULL) {
        printf("Lista encadeada ordenada vazia!\n");
        return;
    }

    struct Node *p = cab;
    while (p != NULL) {
        printf("%d ", p->c);
        p = p->prox;
    }
    printf("\n");
}


void esvazia(struct Node **topo) {
    struct Node *p = *topo;
    struct Node *c = NULL;
    while (p != NULL) {
        c = p;
        p = p->prox;
        free(c);
    }
    (*topo) = NULL;
}

void push(struct Node **topo, int k) {
    struct Node *p = malloc(sizeof(struct Node));
    p->c = k;
    p->prox = (*topo);
    (*topo) = p;
}

void pop(struct Node **topo) {
    if ((*topo) != NULL) {
        struct Node *c = (*topo);
        (*topo) = (*topo)->prox;
        free(c);
    }
}