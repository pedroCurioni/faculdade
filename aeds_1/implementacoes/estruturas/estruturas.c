#include <stdio.h>

/**
 * @brief Move a variavel topo para 0 esvaziando a pilha
 *
 * @param topo Guarda a posição do ultimo element da pilha
 */
void esvaziaPilha(int *topo) { (*topo) = 0; }

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

void esvaziaFila(int *f, int *r) {
    (*f) = 0;
    (*r) = 0;
}

int enfila(int *fila, int *f, int *r, int n, int k) {
    int prov = ((*r) % n) + 1;
    if (prov != (*f)) {
        (*r) = prov;
        fila[(*r)] = prov;
        if ((*f) == 0) {
            (*f) = 1;
        }
        return (*r);
    } else {
        return -1;
    }
}

int desenfila(int *fila, int *f, int *r, int n) {
    if ((*f) != 0) {
        int k = fila[(*f)];
        if ((*f) == (*r)) {
            esvaziaFila(f, r);
        } else {
            (*f) = ((*f) % n) + 1;
        }
        return k;
    } else {
        return -1;
    }
}

int main() {
    /* Pilha */
    /* topo Guarda a posição do ultimo element da pilha */
    int stack[10], topo = 0;

    // esvazia(&topo);
    // push(stack, &topo, 9, 7);

    /* Filha */
    int fila[10], f, r;

    return 0;
}