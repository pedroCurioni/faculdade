#include "hash.h"

int hash(int value) { return value % 10; }
int hash2(int value) { return value % 2; }

void busca_encadeamento_exterior(struct Node *v[], int k, int i,
                                 struct Node **p) {
    (*p) = v[i];
    while ((*p) != NULL && (*p)->c != k) {
        (*p) = (*p)->prox;
    }
}

void insercao_encadeamento_exterior(struct Node *v[], int k) {
    int i = hash(k);
    struct Node *p;

    busca_encadeamento_exterior(v, k, i, &p);
    if (p == NULL) {
        p = (struct Node *)malloc(sizeof(struct Node));
        p->c = k;
        p->prox = v[i];
        v[i] = p;
        free(p);
    } else {
        p = NULL;
    }
}

void busca_encadeamento_aberto(int **v, int M, int *ant, int *p, int k) {
    (*p) = hash(k);
    (*ant) = (*p);
    while (v[(*p)] != NULL && *v[(*p)] != k) {
        (*ant) = (*p);
        (*p) = ((*p) % M) + 1;
    }
    if (v[(*p)] == NULL) {
        p = NULL;
    }
}

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}
