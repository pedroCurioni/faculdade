#include "interface.h"
#include "utils.h"

int main() {
    struct Produto *cab_produto, *cab_carrinho;
    struct Cliente *cab_cliente;
    int ultimo_id = 0;
    float valor_caixa = 0;

    cab_produto = cria_no_produto();
    cab_produto->prox = NULL;

    cab_cliente = cria_no_cliente();
    cab_cliente->prox = NULL;

    cab_carrinho = cria_no_produto();
    cab_carrinho->prox = NULL;

    menu_principal(cab_produto, cab_cliente, cab_carrinho, &ultimo_id, &valor_caixa);

    return 0;
}
