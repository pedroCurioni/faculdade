/**
 * @file arquivo.h
 * @author Pedro Henrique Curioni de Moura
 * @brief Definições de funções relacioadas a exportação/importação de arquivos
 * @version 0.1
 * @date 2023-11-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "cliente.h"
#include "produto.h"

/**
 * @brief Exporta os dados da lista de produtos para um arquivo
 *
 * @param cab_produto Ponteiro para o inicio da lista de produto
 */
void export_produto(struct Produto *cab_produto);

/**
 * @brief Exporta os dados da lista de clientes para um arquivo
 *
 * @param cab_cliente Ponteiro para o inicio da lista do cliente
 */
void export_cliente(struct Cliente *cab_cliente);

/**
 * @brief Exporta os dados da lista de produtos e de clientes para um arquivo
 *
 * @param cab_produto Ponteiro para o inicio da lista de produto
 * @param cab_cliente Ponteiro para o inicio da lista do cliente
 */
void export(struct Produto *cab_produto, struct Cliente *cab_cliente);

/**
 * @brief Importa os dados de um arquivo para a lista de produto
 *
 * @param cab_produto Ponteiro para o inicio da lista de produto
 * @param ultimo_id Ponteiro para a variavel contendo o dado do ultimo id contido na lista
 */
void import_produto(struct Produto *cab_produto, int *ultimo_id);

/**
 * @brief Importa os dados de um arquivo para a lista de clientes
 *
 * @param cab_cliente Ponteiro para o inicio da lista do cliente
 */
void import_cliente(struct Cliente *cab_cliente);

/**
 * @brief Importa os dados de um arquivo para a lista de produtos e de clientes
 *
 * @param cab_produto Ponteiro para o inicio da lista de produto
 * @param cab_cliente Ponteiro para o inicio da lista do cliente
 * @param ultimo_id Ponteiro para a variavel contendo o dado do ultimo id contido na lista
 */
void import(struct Produto *cab_produto, struct Cliente *cab_cliente, int *ultimo_id);

#endif