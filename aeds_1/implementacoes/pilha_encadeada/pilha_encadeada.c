#include "pilha_encadeada.h"

int main() {
    struct Node *topo = NULL;
    push(&topo, 5);
    push(&topo, 2);
    push(&topo, 1);
    push(&topo, 6);
    pop(&topo);
    esvazia(&topo);

    imprime_lista(topo);
    return 0;
}