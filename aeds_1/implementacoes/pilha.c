#include <stdio.h>

/**
 * @brief Move a variavel topo para 0 esvaziando a pilha
 *
 * @param topo Guarda a posição do ultimo element da pilha
 */
void esvazia(int *topo) { (*topo) = 0; }

/**
 * @brief Adiciona um elemento no topo da pilha
 *
 * @param stack Pilha
 * @param topo Guarda a posição do ultimo element da pilha
 * @param n Ultima posição do vetor stack
 * @param k Elemento a ser inserido
 */
int push(int *stack, int *topo, int n, int k) {
    /* Se o topo não for igual ao tamanho do vetor */
    if ((*topo) != n) {
        stack[(*topo)] = k;
        (*topo)++;
        return (*topo);
    } else {
        return -1;
    }
}

/**
 * @brief Retira o ultimo elemento da pilha decrescendo o topo
 * 
 * @param stack Pilha
 * @param topo Guarda a posição do ultimo element da pilha
 * @return int Valor removido ou -1 se não houver valor para ser removido
 */
int pop(int *stack, int *topo) {
    if ((*topo) > 0) {
        int k = stack[(*topo)];
        (*topo)++;
        return k;
    } else {
        return -1;
    }
}

int main() {
    /* topo Guarda a posição do ultimo element da pilha */
    int stack[10], topo = 0;

    // esvazia(&topo);
    // push(stack, &topo, 9, 7);

    return 0;
}