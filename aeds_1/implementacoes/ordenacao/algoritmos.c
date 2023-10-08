#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

void troca(int *v, int i, int j) {
    int t = v[i];
    v[i] = v[j];
    v[j] = t;
}

void selecao(int *v, int n) {
    /*
     * O ultimo elemento do vetor ja esta ordenado na ultima iteração
     * Para cada item na lista
     */
    for (int i = 0; i < n - 1; i++) {
        // /* Sava o índice atual */
        int m = i;
        /* Para cada item na lista ordema do item atual */
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
    /* Relação com o código do professor e1 = e; d1 = m; e2 = m + 1; d2 = d */

    /* i salva a posição de inicio para poder ser alterada */
    /* j salva a posição de inicio da segunda metade do vetor */
    /* j salva a posição de iteração do vetor auxiliar */
    int i = e, j = (m + 1), k = 0;

    /* Tamanho mínimo para comportar a quantidade de elementos a serem
     * analisados */
    int vAux[d - e + 1];

    /* Enquanto i e j estiver no intervalo valido. Procura qual e o menor entre
     * eles e salva na posição k do vetor auxiliar, incrementando somente a
     * variável referente ao seu índice e o índice do vetor auxiliar */
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

    /* Apos i ou j saírem do espaço permitido adicione os elementos restantes do
     * vetor que ainda esta no espaço permitido no vetor auxiliar. Esses
     * elementos restantes não estarão ordenados */
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

    /* Passa os valores do vetor auxiliar para o vetor original */
    for (i = 0; i < k; i++) {
        v[i + e] = vAux[i];
    }
}

void mergeSort(int *v, int e, int d) {
    /* Se o lado esquerdo for menor que realize a ordenação da parte */
    if (e < d) {
        /* Calcule a metade do vetor */
        int m = (e + d) / 2;
        /* Chame o mergeSort da direita ate a metade */
        mergeSort(v, e, m);
        /* Chame o mergeSort da metade + 1 ate a esquerda */
        mergeSort(v, m + 1, d);
        /* Realiza o merge com todo o espaço */
        merge(v, e, m, d);
    }
}

int particao(int *v, int e, int d) {
    int i = e, j = d;
    /* Pivô e o elemento na metade do vetor */
    int pivo = v[(e + d) / 2];

    /* Enquanto a esquerda for <= a direita */
    while (i <= j) {
        /* Procura um elemento da esquerda que seja maior que o pivô, salva sua
         * posição em i */
        while (v[i] < pivo) {
            i++;
        }
        /* Procura um elemento da esquerda que seja menor que o pivô, salva sua
         * posição em j */
        while (v[j] > pivo) {
            j--;
        }

        /* Enquanto a esquerda for <= a direita */
        if (i < j) {
            /* Troca o elemento da esquerda que e maior que o pivô com o da
             * direita que e maior que o pivô*/
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
        /* Recebe um pivô da partição para dividir o vetor */
        int pivo = particao(v, e, d);
        /* Chama o quickSort da direita ate o pivô */
        quickSort(v, e, pivo);
        /* Chama o quickSort da posição apos o pivô ate a esquerda */
        quickSort(v, pivo + 1, d);
    }
}

void shellSort(int *v, int n) {
    /* Calcula o pulo como a metade do tamanho */
    int p = n / 2;
    while (p > 0) {
        /* Para todos os valores de pulo ate o tamanho do vetor */
        for (int i = p; i < n; i++) {
            /* Salva o valor do vetor na posição atual */
            int aux = v[i];
            /* Salva a posição atual em uma variável de posição que possa ser
             * alterada  */
            int j = i;

            /* Enquanto a posição do vetor na posição j-p for menor do que o
             * valor atual, a posição atual recebe o valor que e maior, o j
             * diminui em p, voltando para a posição onde ocorreu a comparação
             * para verificar se tem como realizar mais uma troca */
            while (j >= p && v[j - p] > aux) {
                v[j] = v[j - p];
                j -= p;
            }
            /* Para evitar realizar trocas aux salva o valor de comparação,
             * assim sempre que ocorre  v[j] = v[j - p] o valor de referencia
             * seria perdido, portanto ele e guardado em uma variável para
             * utilizar ao final*/
            v[j] = aux;
        }
        /* Calcula o proximo pulo */
        p = p / 2;
    }
}

void sobeHeap(int *v, int n) {
    for (int i = 1; i <= n; i++) {
        /* Salva a posição da interação e o valor */
        int k = i;
        int t = v[k];

        /* Enquando o pai for menor que o filho */
        while (v[k / 2] < t) {
            /* O filho recebe o valor do pai */
            v[k] = v[(k / 2)];
            /* A posição do filho vira a posição do pai para ser comparado com o
             * novo pai do elemento */
            k /= 2;
        }
        /* Como não houve troca, a ultima posição k recebera o valor do
         * elemento que era o filho original */
        v[k] = t;
    }
}

void desceHeap(int *v, int k, int n) {
    int t, x, j;
    /* Salva o valor do pai */
    t = v[k];
    /* Verifica se existem filhos para k */
    x = (k <= (n / 2));

    while (x) {
        /* Filho da esquerda */
        j = 2 * k;
        /* Se existe o filho da direita e o filho da esquerda for menor que
         * filho da direita*/
        if ((j < n) && (v[j] < v[j + 1])) {
            /* Filho da direita existe e e maior que o da esquerda */
            j++;
        }
        /* Se o filho selecionado e menor que o pai */
        if (t >= v[j]) {
            x = 0;
        } else {
            /* Pai recebe o filho */
            v[k] = v[j];
            k = j;
            /* Verifica se o filho tem outros filhos*/
            x = (k <= (n / 2));
        }
    }
    /* Como não houve troca, a ultima posição k recebera o valor do
     * elemento que era o filho original */
    v[k] = t;
}

void heapSort(int *v, int n) {
    /* Cria um heap de maximo */
    sobeHeap(v, n);

    for (int i = n; i > 0; i--) {
        /* Em um heap de maximo a primeira posição e sempre a maior, portanto
         * troca com a ultima*/
        troca(v, 0, i);
        /* Aplica o desce heap para ordenar um galho da arvore, sempre ignorando
         * os ultimos elementos pois a troca ja deixa eles oredenados*/
        desceHeap(v, 0, i - 1);
    }
}