#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Função que troca duas variáveis de posição
 *
 * @param v Vetor onde se deseja trocar
 * @param i Posição 1
 * @param j Posição 2
 */
void troca(int *v, int i, int j) {
    int t = v[i];
    v[i] = v[j];
    v[j] = t;
}

/**
 * @brief Dado um vetor com n elementos, a cada iteração selecionar o menor
 * elemento do subconjunto não ordenado, e o inserir no subconjunto ordenado
 *
 * @param v Vetor que se quer ordenar
 * @param n Ultima posição do vetor
 */
void selecao(int *v, int n) {
    /*
     * O ultimo elemento do vetor ja esta ordenado na ultima iteração
     * Para cada item na lista
     */
    for (int i = 0; i < n - 1; i++) {
        // /* Sava o índice atual */
        int m = i;
        /* Para cada item na lista ordenada acima do item atual */
        for (int j = (i + 1); j < n; j++) {
            if (v[j] < v[m]) {
                /* Se for encontrado um valor menor do que o valor no índice
                 * atual */
                m = j;
            }
        }
        /* Realiza a troca */
        troca(v, i, m);
    }
}

/**
 * @brief Semelhante à arrumação ordenada de uma mão de cartas. A cada iteração,
 * o elemento selecionado é inserido na sua posição correta dentro do conjunto
 * ordenado
 *
 * @param v Vetor que se quer ordenar
 * @param n Ultima posição do vetor
 */
void insercao(int *v, int n) {
    /* Para cada elemento no conjunto não ordenado */
    for (int i = 1; i < n; i++) {
        /* Salva o índice atual e o valor na posição atual */
        int j = i, t = v[i];
        /* Enquanto o valor de j não for 0 e o valor na posição anterior for
         * menor que o do índice atual */
        while (j > 0 && v[j - 1] > t) {
            /* Faz com que a posição atual seja o valor da posição anterior ja
             * que ele e menor */
            v[j] = v[j - 1];
            /* Decresce o j que desce pelo vetor ordenado */
            j--;
        }
        /* O vetor na posição de j, que percorre o a porção ordenada, recebe o
         * valor da chave no índice atual */
        v[j] = t;
    }
}

void merge(int *v, int e, int m, int d) {
    // e1 = e; d1 = m; e2 = m + 1; d2 = d
    int i = e, j = (m + 1), k = 0;
    int vAux[d - e + 1];

    while (i <= m && j <= d) {
        if (v[i] <= v[j]) {
            vAux[k] = v[i];
            i++;
        } else {
            vAux[k] = v[j];
            j++;
        }
        k++;
    }

    while (i <= m) {
        vAux[k] = v[i];
        k++;
        i++;
    }
    while (j <= d) {
        vAux[k] = v[j];
        k++;
        j++;
    }

    for (i = 0; i < k; i++) {
        v[i + e] = vAux[i];
    }
}

void mergeSort(int *v, int e, int d) {
    if (e < d) {
        int m = (e + d) / 2;
        mergeSort(v, e, m);
        mergeSort(v, m + 1, d);
        merge(v, e, m, d);
    }
}

int particao(int *v, int e, int d) {
    int i = e, j = d;
    int pivo = v[(e + d) / 2];

    while (i <= j) {
        while (v[i] < pivo) {
            i++;
        }
        while (v[j] > pivo) {
            j--;
        }

        if (i < j) {
            troca(v, i, j);
            i++;
            j--;
        } else {
            break;
        }
    }
    return j;
}

void quickSort(int *v, int e, int d) {
    if (e < d) {
        int pivo = particao(v, e, d);
        quickSort(v, e, pivo);
        quickSort(v, pivo + 1, d);
    }
}

void shellSort(int *v, int n) {
    int p = n / 2;
    while (p > 0) {
        for (int i = p; i < n; i++) {
            int aux = v[i];
            int j = i;

            while (j >= p && v[j - p] > aux) {
                v[j] = v[j - p];
                j -= p;
            }
            v[j] = aux;
        }
        p = p / 2;
    }
}

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
    selecao(v, s);
    // insercao(v, s);
    // mergeSort(v, 0, s - 1);
    // quickSort(v, 0, s - 1);
    // shellSort(v, s);

    printf("----- Vetor Final -----\n");
    for (int i = 0; i < s; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    return 0;
}
