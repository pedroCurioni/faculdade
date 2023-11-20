#include "hash.h"

int hash(int value) { return value % 10; }

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

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}
