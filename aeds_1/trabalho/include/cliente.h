/**
 * @file cliente.h
 * @author Pedro Henrique Curioni de Moura
 * @brief Definições de funções relacioadas ao gerenciamento de clientes
 * @version 0.1
 * @date 2023-11-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Elemento da lista encadeada simples de cliente
 * 
 */
struct Cliente {
    struct Cliente *prox;
    char cpf[12];
    char nome[64];
    char telefone[16];
    char email[64];
};

/**
 * @brief Aloca um cliente
 *
 * @return struct Cliente* Ponteiro para o cliente alocado
 */
struct Cliente *cria_no_cliente();

/**
 * @brief Realiza a busca de um cliente baseado no CPF
 *
 * @param cab Ponteiro para o inicio da lista de cliente
 * @param cpf CPF do cliente que se quer buscar
 * @return struct Cliente* Ponteiro para o cliente buscado
 */
struct Cliente *busca_cliente_cpf(struct Cliente *cab, char cpf[12]);

/**
 * @brief Insere um cliente na lista
 *
 * @param cab Ponteiro para o inicio da lista de cliente
 */
void insere_cliente(struct Cliente *cab);

/**
 * @brief Edita um cliente a partir do cpf
 *
 * @param cab Ponteiro para o inicio da lista de produto
 */
void editar_cliente(struct Cliente *cab);

/**
 * @brief Remove um cliente da lista
 *
 * @param cab Ponteiro para o inicio da lista de cliente
 */
void remove_cliente(struct Cliente *cab);

/**
 * @brief Imprime um unico cliente
 *
 * @param cab Ponteiro para o inicio da lista de cliente
 */
void imprime_cliente(struct Cliente *p);

#endif