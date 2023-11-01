#include <stdio.h>

/**
 * @brief Limpa o input buffer
 * 
 */
void clean_buffer();

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
 */
void read_string(char *value);