#include "interface.h"
#include "arquivo.h"
#include "caixa.h"
#include "carrinho.h"
#include "utils.h"

void menu_principal(struct Produto *cab_produto, struct Cliente *cab_cliente,
                    struct Produto *cab_carrinho, int *ultimo_id,
                    float *valor_caixa) {

    int controle;

    do {
        clear_terminal();

        controle = -1;

        printf("------ Menu Principal ------\n\n");

        printf("1 - Gerenciador de produtos\n");
        printf("2 - Busca de produtos\n");
        printf("3 - Cadastro de clientes\n");
        printf("4 - Carrinho de compras\n");
        printf("5 - Exportação/importação dos dados\n");
        printf("6 - Caixa\n");
        printf("0 - Sair\n\n");

        while (controle < 0 || controle > 6) {
            printf("Digite o numero da opção desejada: ");
            read_integer(&controle);
        }

        printf("\n");

        switch (controle) {
        case 0:
            /* Finaliza o programa */
            break;
        case 1:
            menu_gerenciador(cab_produto, ultimo_id);
            break;
        case 2:
            menu_busca(cab_produto);
            break;
        case 3:
            menu_cadastro(cab_cliente);
            break;
        case 4:
            menu_carrinho(cab_produto, cab_cliente, cab_carrinho, valor_caixa);
            break;
        case 5:
            menu_arquivo(cab_produto, cab_cliente, ultimo_id);
            break;
        case 6:
            menu_caixa(valor_caixa);
            break;
        default:
            break;
        }
    } while (controle != 0);
}

void menu_gerenciador(struct Produto *cab_produto, int *ultimo_id) {
    int controle;

    do {
        clear_terminal();

        controle = -1;

        printf("------ Gerenciador de Produtos ------\n\n");

        printf("1 - Adicionar produto\n");
        printf("2 - Remover produto\n");
        printf("3 - Editar produto\n");
        printf("4 - Vizualizar catalogo\n");
        printf("5 - Vizulualizar por ID\n");
        printf("0 - Voltar\n\n");

        while (controle < 0 || controle > 5) {
            printf("Digite o numero da opção desejada: ");
            read_integer(&controle);
        }

        printf("\n");

        switch (controle) {
        case 0:
            /* Volta para o menu principal */
            break;
        case 1:
            insere_produto(cab_produto, ultimo_id);
            break;
        case 2:
            remove_produto(cab_produto);
            break;
        case 3:
            editar_produto(cab_produto);
            break;
        case 4:
            imprime_todos_produtos(cab_produto);
            break;
        case 5:
            imprime_produto_id(cab_produto);
            break;

        default:
            break;
        }
    } while (controle != 0);
}

void menu_busca(struct Produto *cab_produto) {
    int controle;

    do {
        clear_terminal();

        controle = -1;

        printf("------ Busca de Produtos ------\n\n");

        printf("1 - Buscar por nome\n");
        printf("2 - Buscar por intervalo de preço\n");
        printf("3 - Buscar por categoria\n");
        printf("0 - Voltar\n\n");

        while (controle < 0 || controle > 5) {
            printf("Digite o numero da opção desejada: ");
            read_integer(&controle);
        }

        printf("\n");

        switch (controle) {
        case 0:
            /* Volta para o menu principal */
            break;
        case 1:
            busca_produto_nome(cab_produto);
            break;
        case 2:
            busca_produto_preco(cab_produto);
            break;
        case 3:
            busca_produto_categoria(cab_produto);
            break;
        default:
            break;
        }
    } while (controle != 0);
}

void menu_cadastro(struct Cliente *cab_cliente) {
    int controle;

    do {
        clear_terminal();

        controle = -1;

        printf("------ Cadastro de Clientes ------\n\n");

        printf("1 - Cadastrar novo cliente\n");
        printf("2 - Alterar dados do cliente\n");
        printf("3 - Apagar dados do cliente\n");
        printf("0 - Voltar\n\n");

        while (controle < 0 || controle > 5) {
            printf("Digite o numero da opção desejada: ");
            read_integer(&controle);
        }

        printf("\n");

        switch (controle) {
        case 0:
            /* Volta para o menu principal */
            break;
        case 1:
            insere_cliente(cab_cliente);
            break;
        case 2:
            editar_cliente(cab_cliente);
            break;
        case 3:
            remove_cliente(cab_cliente);
            break;

        default:
            break;
        }
    } while (controle != 0);
}

void menu_carrinho(struct Produto *cab_produto, struct Cliente *cab_cliente,
                   struct Produto *cab_carrinho, float *valor_caixa) {
    int controle;

    do {
        clear_terminal();

        controle = -1;

        printf("------ Carrinho de Compras ------\n\n");

        printf("1 - Adicionar produto ao carrinho\n");
        printf("2 - Remover produto do carrinho\n");
        printf("3 - Finalizar compra\n");
        printf("4 - Busca de produtos\n");
        printf("0 - Voltar\n\n");

        float total = imprime_carrinho(cab_carrinho);

        while (controle < 0 || controle > 5) {
            printf("Digite o numero da opção desejada: ");
            read_integer(&controle);
        }

        switch (controle) {
        case 0:
            /* Volta para o menu principal */
            break;
        case 1:
            insere_carrinho(cab_produto, cab_carrinho);
            break;
        case 2:
            remove_carrinho(cab_produto, cab_carrinho);
            break;
        case 3:
            fechar_carrinho(cab_cliente, cab_carrinho, total, valor_caixa);
            return;
        case 4:
            menu_busca(cab_produto);
            break;

        default:
            break;
        }
    } while (controle != 0);
}

void menu_arquivo(struct Produto *cab_produto, struct Cliente *cab_cliente,
                  int *ultimo_id) {
    int controle;

    do {
        clear_terminal();

        controle = -1;

        printf("------ Exportação/Importação dos Dados ------\n\n");

        printf("1 - Exportar dados\n");
        printf("2 - Importar dados\n");
        printf("0 - Voltar\n\n");

        while (controle < 0 || controle > 2) {
            printf("Digite o numero da opção desejada: ");
            read_integer(&controle);
        }

        printf("\n");

        switch (controle) {
        case 0:
            /* Volta para o menu principal */
            break;
        case 1:
            export(cab_produto, cab_cliente);
            break;
        case 2:
            import(cab_produto, cab_cliente, ultimo_id);
            break;
        default:
            break;
        }
    } while (controle != 0);
}

void menu_caixa(float *valor_caixa) {
    int controle;

    do {
        clear_terminal();

        controle = -1;

        printf("------ Exportação/Importação dos Dados ------\n\n");

        printf("Total do Caixa: %.2f\n", *valor_caixa);
        printf("1 - Remover quantia\n");
        printf("0 - Voltar\n\n");

        while (controle < 0 || controle > 1) {
            printf("Digite o numero da opção desejada: ");
            read_integer(&controle);
        }

        printf("\n");

        switch (controle) {
        case 0:
            /* Volta para o menu principal */
            break;
        case 1:
            remover_caixa(valor_caixa);
            break;
        default:
            break;
        }
    } while (controle != 0);
}