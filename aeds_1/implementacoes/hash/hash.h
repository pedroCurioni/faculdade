#include <stdio.h>
#include <stdlib.h>

struct Node {
    int c;
    struct Node *prox;
};

/**
 * @brief Função de hash
 *
 * @param value Valor para buscar ou adicionar
 * @return int Posição retornada pela função de hash
 */
int hash(int value);

/**
 * @brief Realiza uma busca em uma tabela hash utilizando encadeamento exterior
 * 
 * @param v Tabela hash
 * @param k Chave de busca
 * @param i Indice para ser buscado
 * @param p Node para salvar o valor
 */
void busca_encadeamento_exterior(struct Node *v[], int k,int i, struct Node **p);

/**
 * @brief 
 * 
 * @param v Tabela hash
 * @param k Chave de busca
 */
void insercao_encadeamento_exterior(struct Node *v[], int k);