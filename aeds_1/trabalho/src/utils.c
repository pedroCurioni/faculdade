#include "utils.h"

void clear_terminal() { printf("\e[1;1H\e[2J"); }

void clean_buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void wait_keypress() {
    char c;

    printf("\nPressione enter para continuar...\n");
    
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
    // clean_buffer();
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
    size_t length;

    fgets(value, size, stdin);

    length = strlen(value);

    if (length > 0 && value[length - 1] == '\n') {
        // String digitada menor que o tamanho maximo
        // Remove o \n da string
        value[strcspn(value, "\n")] = '\0';
    } else {
        // String digitata excede o tamanho maximo
        clean_buffer();
    }
}
