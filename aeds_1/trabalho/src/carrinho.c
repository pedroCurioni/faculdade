#include "carrinho.h"
#include "utils.h"

void insere_carrinho(struct Produto *cab_produto,
                     struct Produto *cab_carrinho) {
    struct Produto *p, *ant, *pc;
    int id;

    printf("ID do produto: ");
    read_integer(&id);

    ant = busca_produto_id(cab_produto, id);
    p = ant->prox;

    if (p != NULL && p->id == id) {
        pc = cria_no_produto();

        pc->id = p->id;
        pc->preco = p->preco;
        strcpy(pc->categoria, p->categoria);
        strcpy(pc->descricao, p->descricao);
        strcpy(pc->nome, p->nome);

        pc->prox = cab_carrinho->prox;
        cab_carrinho->prox = pc;
        printf("\nProduto inserido ao carrinho com sucesso!\n");
    } else {
        printf("\nProduto não encontrado!\n");
    }

    wait_keypress();
}

void remove_carrinho(struct Produto *cab_produto,
                     struct Produto *cab_carrinho) {
    struct Produto *p, *ant;
    int id;

    printf("ID do produto: ");
    read_integer(&id);

    ant = busca_produto_id(cab_carrinho, id);
    p = ant->prox;

    if (p != NULL) {
        ant->prox = p->prox;
        free(p);
        printf("\nProduto removido do carrinho com sucesso!\n");
    } else {
        printf("\nProduto não encontrado no carrinho!\n");
    }

    wait_keypress();
}

float imprime_carrinho(struct Produto *cab_carrinho) {
    struct Produto *p = cab_carrinho->prox;
    float total = 0;

    if (p == NULL) {
        printf("Carrinho vazio\n");
    }

    while (p != NULL) {
        printf("----------\n");
        printf("ID: %d\n", p->id);
        printf("Nome: %s\n", p->nome);
        printf("Preço: %.2f\n", p->preco);

        total += p->preco;
        p = p->prox;
    }

    printf("\nTotal: %.2f\n\n", total);

    return total;
}

void apaga_carrinho(struct Produto *cab_carrinho) {
    struct Produto *p = cab_carrinho->prox;
    struct Produto *ant = cab_carrinho;
    while (p != NULL) {
        ant->prox = p->prox;
        free(p);
        p = ant->prox;
    }
}

void fechar_carrinho(struct Cliente *cab_cliente, struct Produto *cab_carrinho,
                     float total, float *valor_caixa) {
    int controle = -1;
    char cpf[12];

    while (controle < 1 || controle > 2) {
        printf("O cliente esta cadastrado? (1 para sim, 2 para não): ");
        read_integer(&controle);
    }

    if (controle == 2) {
        printf("Valor total; %f", total);

    } else if (controle == 1) {
        printf("Digite o cpf do cliente, somente números: ");
        read_string(cpf, sizeof(cpf));

        struct Cliente *c = busca_cliente_cpf(cab_cliente, cpf);
        c = c->prox;
        if (c == NULL) {
            printf("Cliente não encontdado!\n");
            wait_keypress();
            return;
        }

        total = total * 0.9;
        printf("Valor total, com desconto: %f\n", total);
    }

    apaga_carrinho(cab_carrinho);

    (*valor_caixa) += total;
    printf("Pedido realizado com sucesso!\n");
    wait_keypress();
}