/**
 * @file interface.h
 * @author Pedro Henrique Curioni de Moura
 * @brief Definições de funções relacioadas as interfaces do programa
 * @version 0.1
 * @date 2023-11-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include "cliente.h"
#include "produto.h"
#include <stdio.h>
#include <unistd.h>

/**
 * @brief Menu principal do programa utilizado para chamar os menus secundarios
 *
 * @param cab_produto Ponteiro para o inicio da lista de produtos
 * @param cab_cliente Ponteiro para o inicio da lista de clientes
 * @param cab_carrinho Ponteiro para o inicio da lista contendo os itens do
 * carrinho
 * @param ultimo_id Ponteiro para a variavel contendo o dado do ultimo id contido na lista
 * @param valor_caixa Ponteiro para o valor total guardado no caixa
 */
void menu_principal(struct Produto *cab_produto, struct Cliente *cab_cliente,
                    struct Produto *cab_carrinho, int *ultimo_id,
                    float *valor_caixa);

/**
 * @brief Menu de seleção das opções de gerenciamento dos produtos
 *
 * @param cab_produto Ponteiro para o inicio da lista de produtos
 * @param ultimo_id Ponteiro para a variavel contendo o dado do ultimo id lido
 */
void menu_gerenciador(struct Produto *cab_produto, int *ultimo_id);

/**
 * @brief Menu de seleção das opções de busca dos produtos
 *
 * @param cab_produto Ponteiro para o inicio da lista de produtos
 */
void menu_busca(struct Produto *cab_produto);

/**
 * @brief Menu de seleção das opções de gerenciamento dos dados dos usuarios
 *
 * @param cab_cliente Ponteiro para o inicio da lista de clientes
 */
void menu_cadastro(struct Cliente *cab_cliente);

/**
 * @brief Menu de seleção das opções do carrinho de compras
 *
 * @param cab_produto Ponteiro para o inicio da lista de produtos
 * @param cab_cliente Ponteiro para o inicio da lista de clientes
 * @param cab_carrinho Ponteiro para o inicio da lista contendo os itens do
 * carrinho
 * @param valor_caixa Ponteiro para o valor total guardado no caixa
 */
void menu_carrinho(struct Produto *cab_produto, struct Cliente *cab_cliente,
                   struct Produto *cab_carrinho, float *valor_caixa);

/**
 * @brief Menu principal do programa utilizado para chamar os menus secundarios
 * relacionado aos arquivos
 *
 * @param cab_produto Ponteiro para o inicio da lista de produtos
 * @param cab_cliente Ponteiro para o inicio da lista de clientes
 * @param ultimo_id Ponteiro para a variavel contendo o dado do ultimo id lido
 */
void menu_arquivo(struct Produto *cab_produto, struct Cliente *cab_cliente,
                  int *ultimo_id);

/**
 * @brief Menu de seleção das opções do caixa e vizualização do valor guardado
 *
 * @param valor_caixa Ponteiro para o valor total guardado no caixa
 */
void menu_caixa(float *valor_caixa);

#endif