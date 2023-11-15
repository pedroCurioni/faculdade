#include "caixa.h"
#include "stdio.h"
#include "utils.h"

void remover_caixa(float *valor_caixa) {
    float valor;

    printf("Digite um valor para remover do caixa: ");
    read_float(&valor);

    (*valor_caixa) -= valor;

    printf("Valor removido com sucesso!\n");
    wait_keypress();
}