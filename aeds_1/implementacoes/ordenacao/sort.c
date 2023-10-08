#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    /* Declaração de um vetor genérico */
    int v[10] = {17, 2, 9, 4, 6, 1, 8, 3, 10, 5};
    /* Tamanho total do vetor, não e a ultima posição */
    int s = (sizeof(v) / sizeof(int));

    printf("----- Vetor Inicial -----\n");
    for (int i = 0; i < s; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    /* Retire o comentário para utilizar uma função de sort especifica*/
    // selecao(v, s);
    // insercao(v, s);
    // mergeSort(v, 0, s - 1); /* Recebe a ultima posição do vetor */
    // quickSort(v, 0, s - 1); /* Recebe a ultima posição do vetor */
    // shellSort(v, s);
    // heapSort(v, s - 1); /* Recebe a ultima posição do vetor */

    printf("----- Vetor Final -----\n");
    for (int i = 0; i < s; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    return 0;
}
