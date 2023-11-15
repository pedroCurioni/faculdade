/**
 * @file utils.h
 * @author Pedro Henrique Curioni de Moura
 * @brief Definições gerais de funções de utilidade
 * @version 0.1
 * @date 2023-11-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Lima o texto do terminal
 *
 */
void clear_terminal();

/**
 * @brief Limpa o input buffer
 *
 */
void clean_buffer();

/**
 * @brief Espere o usuario digitar qualquer tecla para continuar o programa
 *
 */
void wait_keypress();

/**
 * @brief Le um int digitado pelo usuario
 *
 * @param value Ponteiro para a posição de memoria onde se quer salvar o dado
 */
void read_integer(int *value);

/**
 * @brief Le um float digitado pelo usuario
 *
 * @param value Ponteiro para a posição de memoria onde se quer salvar o dado
 */
void read_float(float *value);

/**
 * @brief Le uma string digitada pelo usuario
 *
 * @param value Ponteiro para a posição de memoria onde se quer salvar o dado
 * @param size Tamanho em bytes do maxima da string lida
 */
void read_string(char *value, int size);

#endif