/**nada aci
 * @brief Função que troca duas variáveis de posição
 *
 * @param v Vetor onde se deseja trocar
 * @param i Posição 1
 * @param j Posição 2
 */
void troca(int *v, int i, int j);

/**
 * @brief Dado um vetor com n elementos, a cada iteração selecionar o menor
 * elemento do subconjunto não ordenado, e o inserir no subconjunto ordenado
 *
 * @param v Vetor que se quer ordenar
 * @param n Ultima posição do vetor
 */
void selecao(int *v, int n);

/**
 * @brief Semelhante à arrumação ordenada de uma mão de cartas. A cada iteração,
 * o elemento selecionado é inserido na sua posição correta dentro do conjunto
 * ordenado
 *
 * @param v Vetor que se quer ordenar
 * @param n Ultima posição do vetor
 */
void insercao(int *v, int n);
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
void merge(int *v, int e, int m, int d);
/**
 * @brief Divide um vetor sucessivas vezes baseado na metade e ordena partes
 * dele para ordena-lo
 *
 * @param v Vetor
 * @param e Posição de inicio
 * @param d Posição do fim
 */
void mergeSort(int *v, int e, int d);
/**
 * @brief Passa da esquerda para a direita e da direita ate a esquerda
 * procurando os elementos que estam na ordem erradas quando comparados com o
 * elemento no meio do vetor e troca-los
 *
 * @param v Vetor
 * @param e Posição da esquerda
 * @param d Posição da direita
 * @return int
 */
int particao(int *v, int e, int d);
/**
 * @brief Baseado em um pivo, separa o vetor em diversas partes para ordenar
 *
 * @param v Vetor
 * @param e Posição da esquerda
 * @param d Posição da direita
 */
void quickSort(int *v, int e, int d);
/**
 * @brief Usa um pulo para separar a distância entre os números comparados
 * dentro do vetor. Conforme o algoritmo vai avançando o pulo vai diminuindo
 * até ser 1, e o vetor estar devidamente ordenado
 *
 * @param v Vetor
 * @param n Tamanho do vetor
 */
void shellSort(int *v, int n);
/**
 * @brief Formata um vetor para transforma-lo em um heap de maximo. Um heap onde
 * o pai sempre e maior que o filho
 *
 * @param v Vetor
 * @param n Tamanho do vetor
 */
void sobeHeap(int *v, int n);

/**
 * @brief Formata um vetor para transforma-lo em um heap de minimo. Um heap onde
 * o pai sempre e menor que os filhos
 *
 * @param v Vetor
 * @param k Posição nó pai
 * @param n Tamanho do vetor
 */
void desceHeap(int *v, int k, int n);


/**
 * @brief Algoritomo de ordenação que recebe um heap de maximo como parametro
 *
 * @param v Vetor
 * @param n Ultima posição do vetor
 */
void heapSort(int *v, int n);