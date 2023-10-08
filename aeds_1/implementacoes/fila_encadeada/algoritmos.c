#include "fila.h"

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

void enfila(struct Node **f, struct Node **r, int k) {
    struct Node *p = malloc(sizeof(struct Node));
    p->c = k;
    p->prox = NULL;

    if ((*r) != NULL) {
        (*r)->prox = p;
    } else {
        (*f) = p;
    }
    (*r) = p;
}

void desenfila(struct Node **f, struct Node **r) {
    if ((*f) != NULL)
    {
        struct Node *p = (*f);
        (*f) = (*f)->prox;
        free(p);
        if ((*f) == NULL)
        {
            (*r) = NULL;
        }
    }
    
}