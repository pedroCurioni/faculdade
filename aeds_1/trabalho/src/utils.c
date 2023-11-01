#include "utils.h"

void clean_buffer() {
    int c;
    /* discard all characters up to and including newline */
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void read_integer(int *value) {
    while (scanf("%d", value) != 1) {
        clean_buffer();
        printf("Valor digitado não e um número, digite novamente: ");
    }
    clean_buffer();
}

void read_float(float *value) {
    while (scanf("%f", value) != 1) {
        clean_buffer();
        printf("Valor digitado não e um número, digite novamente: ");
    }
    clean_buffer();
}

void read_string(char *value, int size) {
    fgets(value, size, stdin);
    // Remove o \n da string
    value[strcspn(value, "\n")] = '\0';
}