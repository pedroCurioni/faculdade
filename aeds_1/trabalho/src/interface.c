#include "interface.h"
#include "utils.h"

void menu_principal(struct Produto *cab_produto) {
    int controle;

    do {
        controle = -1;

        printf("\n\n------ Menu Principal ------\n\n");

        printf("1 - Gerenciador de produtos\n");
        printf("2 - Busca de produtos\n");
        printf("3 - Cadastro de clientes\n");
        printf("4 - Carrinho de compras\n");
        printf("5 - Exportação/importação dos dados\n");
        printf("0 - Sair\n\n");

        while (controle < 0 || controle > 5) {
            printf("Digite o numero da opção desejada: ");
            read_integer(&controle);
        }

        printf("\n");

        switch (controle) {
        case 1:
            menu_gerenciador(cab_produto);
            break;
        case 2:
            menu_busca(cab_produto);
            break;
        case 3:
            menu_cadastro();
            break;
        case 4:
            menu_carrinho();
            break;
        case 5:
            /* code */
            break;

        default:
            /* Programa so chega aqui se controle == 0 */
            break;
        }
    } while (controle != 0);
}

void menu_gerenciador(struct Produto *cab_produto) {
    int controle;

    do {
        controle = -1;

        printf("\n\n------ Gerenciador de produtos ------\n\n");

        printf("1 - Adicionar produto\n");
        printf("2 - Remover produto\n");
        printf("3 - Editar produto\n");
        printf("4 - Vizualizar catalogo\n");
        printf("5 - Vizulualizar por ID\n");
        printf("0 - Sair\n\n");

        while (controle < 0 || controle > 5) {
            printf("Digite o numero da opção desejada: ");
            read_integer(&controle);
        }

        printf("\n");

        switch (controle) {
        case 1:
            insere_produto(cab_produto);
            break;
        case 2:
            remove_produto(cab_produto);
            break;
        case 3:
            /* code */
            break;
        case 4:
            imprime_todos_produtos(cab_produto);
            break;
        case 5:
            imprime_produto_id(cab_produto);
            break;

        default:
            /* Programa so chega aqui se controle == 0 */
            break;
        }
    } while (controle != 0);
}

void menu_busca(struct Produto *cab_produto) {
    int controle;

    do {
        controle = -1;

        printf("\n\n------ Busca de produtos ------\n\n");

        printf("1 - Buscar por nome\n");
        printf("2 - Buscar por intervalo de preço\n");
        printf("3 - Buscar por categoria\n");
        printf("0 - Sair\n");

        while (controle < 0 || controle > 5) {
            printf("Digite o numero da opção desejada: ");
            read_integer(&controle);
        }

        printf("\n");

        switch (controle) {
        case 1:
            /* code */
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;

        default:
            /* Programa so chega aqui se controle == 0 */
            break;
        }
    } while (controle != 0);
}

void menu_cadastro() {
    int controle;

    do {
        controle = -1;

        printf("\n\n------ Cadastro de clientes ------\n\n");

        printf("1 - Cadastrar novo cliente\n");
        printf("2 - Alterar dados do cliente\n");
        printf("3 - Apagar dados do cliente\n");
        printf("0 - Sair\n");

        while (controle < 0 || controle > 5) {
            printf("Digite o numero da opção desejada: ");
            read_integer(&controle);
        }

        printf("\n");

        switch (controle) {
        case 1:
            /* code */
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;

        default:
            /* Programa so chega aqui se controle == 0 */
            break;
        }
    } while (controle != 0);
}

void menu_carrinho() {
    int controle;

    do {
        controle = -1;

        printf("------ Carrinho de compras ------\n\n");

        printf("1 - Adicionar produto ao carrinho\n");
        printf("2 - Remover produto do carrinho\n");
        printf("3 - Finalizar compra\n");
        printf("0 - Sair\n");

        while (controle < 0 || controle > 5) {
            printf("Digite o numero da opção desejada: ");
            read_integer(&controle);
        }

        printf("\n");

        switch (controle) {
        case 1:
            /* code */
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;

        default:
            /* Programa so chega aqui se controle == 0 */
            break;
        }
    } while (controle != 0);
}