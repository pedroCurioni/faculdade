/**
 * @file carrinho.h
 * @author Pedro Henrique Curioni de Moura
 * @brief Definições de funções relacioadas ao gerenciamento do carrinho
 * @version 0.1
 * @date 2023-11-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef CARRINHO_H
#define CARRINHO_H

#include "cliente.h"
#include "produto.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Adiciona um produto ao carrinho
 *
 * @param cab_produto Ponteiro para o inicio da lista de produto
 * @param cab_carrinho Ponteiro para o inicio da lista do carrinho
 */
void insere_carrinho(struct Produto *cab_produto, struct Produto *cab_carrinho);

/**
 * @brief Remove um produto do carrinho
 *
 * @param cab_produto Ponteiro para o inicio da lista de produto
 * @param cab_carrinho Ponteiro para o inicio da lista do carrinho
 */
void remove_carrinho(struct Produto *cab_produto, struct Produto *cab_carrinho);

/**
 * @brief Imprime os itens do carrinho
 *
 * @param cab_carrinho Ponteiro para o inicio da lista do carrinho
 * @return total Float valor total do carrinho
 */
float imprime_carrinho(struct Produto *cab_carrinho);

/**
 * @brief Fecha o pedido com os itens no carrinho
 *
 * @param cab_cliente Ponteiro para o inicio da lista de cliente
 * @param cab_carrinho Ponteiro para o inicio da lista do carrinho
 * @param total Valor total do carrinho
 * @param valor_caixa Ponteiro para o valor total guardado no caixa
 */
void fechar_carrinho(struct Cliente *cab_cliente, struct Produto *cab_carrinho,
                     float total, float *valor_caixa);

#endif