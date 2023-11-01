#include "utils.h"
#include <stdlib.h>

void clean_buffer (void)
{
    while ( getchar() != '\n' );
}

void read_integer(int *value) {
    // clean_buffer();
    while (scanf("%d", value) != 1) {
        printf("Valor digitado não e um número, digite novamente: ");
    }
}

void read_float(float *value) {
    // clean_buffer();
    while (scanf("%f", value) != 1) {
        printf("Valor digitado não e um número, digite novamente: ");
    }
}

void read_string(char *value) {
    fgets(value, sizeof(value), stdin);
}