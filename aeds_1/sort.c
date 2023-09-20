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

/**
 * @brief Percorre um vetor simultaneamente a partir do início ate a metade e da
 * metade ate o fim. Junta as duas partes em um vetor auxiliar de forma que elas
 * estejam ordenadas no vetor auxiliar
 *
 * @param v Ponteiro para o vetor
 * @param e Posição de inicio
 * @param m Posição da metade
 * @param d Posição do fim
 */
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

/**
 * @brief Divide um vetor sucessivas vezes baseado na metade e ordena partes
 * dele para ordena-lo
 *
 * @param v Vetor
 * @param e Posição de inicio
 * @param d Posição do fim
 */
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

/**
 * @brief
 *
 * @param v Vetor
 * @param e Posição da esquerda
 * @param d Posição da direita
 * @return int
 */
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

/**
 * @brief
 *
 * @param v Vetor
 * @param e Posição da esquerda
 * @param d Posição da direita
 */
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

/**
 * @brief Usa um pulo para separar a distância entre os números comparados
 * dentro do vetor. Conforme o algoritmo vai avançando o pulo vai diminuindo
 * até ser 1, e o vetor estar devidamente ordenado
 *
 * @param v Vetor
 * @param n Tamanho do vetor
 */
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

/**
 * @brief Formata um vetor para transforma-lo em um heap de maximo. Um heap onde
 * o pai sempre e maior que o filho
 *
 * @param v Vetor
 * @param n Tamanho do vetor
 */
void sobeHeap(int *v, int n) {
    for (int i = 1; i < n; i++) {
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
    // mergeSort(v, 0, s - 1);  /* Recebe a ultima posição do vetor */
    // quickSort(v, 0, s - 1);  /* Recebe a ultima posição do vetor */
    // shellSort(v, s);
    sobeHeap(v, s);

    printf("----- Vetor Final -----\n");
    for (int i = 0; i < s; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    return 0;
}
