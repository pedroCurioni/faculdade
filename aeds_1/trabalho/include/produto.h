/**
 * @file produto.h
 * @author Pedro Henrique Curioni de Moura
 * @brief Definições de funções relacioadas ao gerenciamento de protudos
 * @version 0.1
 * @date 2023-11-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Elemento da lista encadeada simples de produto
 * 
 */
struct Produto {
    int id;
    float preco;
    struct Produto *prox;
    char categoria[32];
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
 * @param cab Ponteiro para o inicio da lista de produto
 * @param id Id do produto que se quer encontar
 * @return struct Produto* Ponteiro para o elmento anterior encontrado
 */
struct Produto *busca_produto_id(struct Produto *cab, int id);

/**
 * @brief Busca e imprime todos os produtos com o nome recebido do usuario
 *
 * @param cab Ponteiro para o inicio da lista de produto
 */
void busca_produto_nome(struct Produto *cab);

/**
 * @brief Busca e imprime todos os produtos no intervalo de preço digitado pelo
 * usuario
 *
 * @param cab Ponteiro para o inicio da lista de produto
 */
void busca_produto_preco(struct Produto *cab);

/**
 * @brief Busca e imprime todos os produtos com uma categoria recebida do
 * usuario
 *
 * @param cab Ponteiro para o inicio da lista de produto
 */
void busca_produto_categoria(struct Produto *cab);

/**
 * @brief Insere um produto na lista
 *
 * @param cab Ponteiro para o inicio da lista de produto
 * @param ultimo_id Ponteiro para o ultimo id salvo na lista
 */
void insere_produto(struct Produto *cab, int *ultimo_id);

/**
 * @brief Edita um produto a partiro do id
 *
 * @param cab Ponteiro para o inicio da lista de produto
 */
void editar_produto(struct Produto *cab);

/**
 * @brief Remove um produto da lista
 *
 * @param cab Ponteiro para o inicio da lista de produto
 */
void remove_produto(struct Produto *cab);

/**
 * @brief Imprime um unico produto
 *
 * @param cab Ponteiro para o inicio da lista de produto
 */
void imprime_produto(struct Produto *p);

/**
 * @brief Imprime todos os produtos da lista
 *
 * @param cab Ponteiro para o inicio da lista de produto
 */
void imprime_todos_produtos(struct Produto *cab);

/**
 * @brief Imprime um unico produto baseado no ID recebido
 *
 * @param cab Ponteiro para o inicio da lista de produto
 */
void imprime_produto_id(struct Produto *cab);

#endif