#include <stdio.h>
#include <stdlib.h>

struct Produto {
    int id;
    float preco;
    struct Produto *prox;
    char categoria[16];
    char nome[64];
    char descricao[256];
};

/**
 * @brief Aloca um produto
 *
 * @return struct Produto* Ponteiro para o produto alocado
 */
struct Produto *cria_no_produto();

/**
 * @brief Busca um produto na lista.
 * Passe o ID -1 para buscar o ultimo elemento
 *
 * @param cab Ponteiro para o inicio da lista
 * @param id Id do produto que se quer encontar
 * @return struct Produto* Ponteiro para o elmento encontrado
 */
struct Produto *busca_produto_id(struct Produto *cab, int id);

/**
 * @brief Insere um produto na lista
 *
 * @param cab Ponteiro para o inicio da lista
 */
void insere_produto(struct Produto *cab);

/**
 * @brief 
 * 
 * @param cab Ponteiro para o inicio da lista
 * @param id Id do produto que se quer encontar 
*/
void remove_produto(struct Produto *cab);

/**
 * @brief Imprime um unico produto
 *
 * @param cab Ponteiro para o produto que se quer imprimir
 */
void imprime_produto(struct Produto *p);

/**
 * @brief Imprime todos os produtos da lista
 *
 * @param cab Ponteiro para o inicio da lista
 */
void imprime_todos_produtos(struct Produto *cab);

/**
 * @brief Imprime um unico produto baseado no ID recebido
 *
 * @param cab Ponteiro para o inicio da lista
 * @param id ID do produto que se quer imprimir
 */
void imprime_produto_id(struct Produto *cab);
