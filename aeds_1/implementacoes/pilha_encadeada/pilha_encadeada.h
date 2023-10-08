#include <stdio.h>
#include <stdlib.h>

struct Node {
    int c;
    struct Node *prox;
};

void imprime_lista(struct Node *cab);


/**
 * @brief Esvazia a pilha
 *
 * @param topo Ponteiro para a posição de memoria onde a variavel do topo da
 * pilha esta guardada
 */
void esvazia(struct Node **topo);

/**
 * @brief Adiciona um elemento no topo da pilha
 *
 * @param topo Ponteiro para a posição de memoria onde a variavel do topo da
 * pilha esta guardada
 * @param k Elemento para ser adicionado
 */
void push(struct Node **topo, int k);

/**
 * @brief Remove o elemento no topo da pilha
 *
 * @param topo Ponteiro para a posição de memoria onde a variavel do topo da
 * pilha esta guardada
 */
void pop(struct Node **topo);