#include "interface.h"
#include "utils.h"

int main() {
    struct Produto *cab_produto = cria_no_produto();
    cab_produto->id = 0;
    cab_produto ->prox = NULL;

    menu_principal(cab_produto);
    return 0;
}
