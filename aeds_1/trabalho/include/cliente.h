#include <stdio.h>
#include <stdlib.h>

struct Cliente {
    struct Cliente *prox;
    char cpf[12];
    char nome[64];
    char telefone[16];
    char email[64];
};