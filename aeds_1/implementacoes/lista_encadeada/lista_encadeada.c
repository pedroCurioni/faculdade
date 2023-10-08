#include <stdlib.h>
#include <stdio.h>

#include "operacoes_lista_enc.h"

int main () {
    // Nó cabela inicializado, e utilizado como nó auxiliar da lista encadeada.
    struct no *cab = cria_no();
    cab->prox = NULL;

    cria_lista_ordenada(cab, 10);
    imprime_lista(cab);
    insere_ordenada(cab, 9);
    imprime_lista(cab);
    insere_ordenada(cab, 9);
    insere_ordenada(cab, 7);
    insere_ordenada(cab, 5);
    insere_ordenada(cab, 11);
    insere_ordenada(cab, 12);
    imprime_lista(cab);
    apaga_lista(cab);
    imprime_lista(cab);
    
    // Libera memória utilizada pelo nó cabeça.
    free(cab);
    return EXIT_SUCCESS;
}