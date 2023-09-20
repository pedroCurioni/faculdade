#include <stdio.h>
#include <stdlib.h>
/**
 * @brief  por todos os elementos do vetor ate encontrar a chave,
 * Se encontrar retorna seu índice, se não retorna -1
 *
 * @param v Ponteiro para o vetor
 * @param n Tamanho do vetor começando em 1
 * @param chave Elemento que se busca
 * @return Índice de onde o elemento foi encontrado ou -1 se não for encontrado
 */
int sequencialSearch(int *v, int n, int chave) {
    for (int i = 0; i < n; ++i) {
        if (v[i] == chave) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Pesquisa utilizada em vetores ordenados.
 * Divide o vetor sempre na metade.
 * Se a chave for maior que a metade, chama-se recursivamente para buscar na
 * metade menor. Caso contrario busca na metade maior.
 *
 * @param arr Vetor onde se quer buscar o valor
 * @param inf Limite inferior do vetor
 * @param sup Limite superior do vetor
 * @param value Valor que se quer encontrar
 * @return Índice de onde o elemento foi encontrado ou -1 se não for encontrado
 */
int binarySearch(int *arr, int inf, int sup, int value) {
    int m = (inf + sup) / 2; /* Calcula a metade do vetor */
    if (inf > sup) {
        return -1;
    } else if (arr[m] == value) {
        return m;
    } else if (arr[m] <= value) {
        /* Se o valor desejado for maior que o valor na metade do vetor
         * Recursivamente chame a função novamente na metade acima do meio do
         * vetor */
        return binarySearch(arr, (inf + m + 1), sup, value);
    } else {
        /* Se o valor desejado for menor que o valor na metade do vetor
         * Recursivamente chame a função novamente na metade abaixo do meio do
         * vetor */
        return binarySearch(arr, inf, (sup - m - 1), value);
    }
}

int main() {
    /* Declaração de um vetor genérico */
    int arr[10] = {1, 1, 2, 3, 5, 7, 10, 22, 34, 54};

    /* Pesquisa através do método Pesquisa Sequencial */
    printf("%d\n", sequencialSearch(arr, 10, 54));

    /* Pesquisa através do método Pesquisa Binaria */
    printf("%d\n", binarySearch(arr, 0, 10, 54));
}
