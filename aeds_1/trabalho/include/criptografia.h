/**
 * @file criptografia.h
 * @author Pedro Henrique Curioni de Moura
 * @brief Definições de funções relacionada a criptografia dos dados
 * @version 0.1
 * @date 2023-11-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef CRIPTOGRAFIA_H
#define CRIPTOGRAFIA_H

#include "cliente.h"
#include "produto.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Encripta/Decripta a string recebida atraves de uma senha, utilizando a
 * cifra de XOR Para desfazer um XOR basta realiza-lo novamente
 *
 * @param data Dado que se quer criptografar
 * @param password Sehna, Chave de criptografia
 * @param output Variavel onde os dado criptografado sera salvo
 */
void encrypt_decrypt_string(char *data, char *password, char *output);

/**
 * @brief Encripta/Decripta o inteiro recebido atraves de uma senha, utilizando
 * a cifra de XOR Para desfazer um XOR basta realiza-lo novamente
 *
 * @param data Valor que se quer criptografar
 * @param password Sehna, Chave de criptografia
 */
void encrypt_decrypt_int(int *value, int key);

/**
 * @brief Encripta/Decripta o float recebido atraves de uma senha, utilizando a
 * cifra de XOR Para desfazer um XOR basta realiza-lo novamente
 *
 * @param data Dado que se quer criptografar
 * @param password Sehna, Chave de criptografia
 */
void encrypt_decrypt_float(float *value, int key);

/**
 * @brief Encripta a lista de produtos
 *
 * @param cab_produto Ponteiro para o inicio da lista de produto
 * @param senha Chave de criptografia
 */
void encrypt_decrypt_produto(struct Produto *cab_produto, char *senha);

/**
 * @brief Encripta a lista de cliente
 *
 * @param cab_cliente Ponteiro para o inicio da lista de cliente
 * @param senha Chave de criptografia
 */
void encrypt_decrypt_cliente(struct Cliente *cab_cliente, char *senha);

#endif