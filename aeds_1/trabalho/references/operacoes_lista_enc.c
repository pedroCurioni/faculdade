#include "operacoes_lista_enc.h"

void cria_lista_ordenada(struct no *cab, int n) {
    struct no *p = NULL;
    for (int i = n; i > 0; i = i - 2) {
        p = cria_no();
        p->c = i;
        p->prox = cab->prox;
        cab->prox = p;
    }
}

struct no *busca_ordenada(struct no *cab, int k) {
    struct no *ant = cab;
    struct no *p = cab->prox;
    while (p != NULL && p->c < k) {
        ant = p;
        p = p->prox;
    }
    return ant;
}

void insere_ordenada(struct no *cab, int k) {
    struct no *ant = busca_ordenada(cab, k);
    if (ant->prox == NULL || ant->prox->c != k) {
        struct no *p = cria_no();
        p->c = k;
        p->prox = ant->prox;
        ant->prox = p;

        printf("Elemento %d inserido na lista encadeada ordenada.\n", k);
    } else {
        printf("Elemento %d já estava contida na lista encadeada ordenada.\n",
               k);
    }
}

void apaga_lista(struct no *cab) {
    struct no *p = cab->prox;
    struct no *ant = cab;
    while (p != NULL) {
        ant->prox = p->prox;
        free(p);
        p = ant->prox;
    }
    printf("Lista apagada com sucesso!\n");
}

void imprime_lista(struct no *cab) {
    if (cab->prox == NULL) {
        printf("Lista encadeada ordenada vazia!\n");
        return;
    }

    struct no *p = cab->prox;
    while (p != NULL) {
        printf("%d ", p->c);
        p = p->prox;
    }
    printf("\n");
}

struct no *cria_no() { return (struct no *)malloc(sizeof(struct no)); }