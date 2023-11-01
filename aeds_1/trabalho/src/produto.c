#include "produto.h"
#include "utils.h"

struct Produto *cria_no_produto() {
    return (struct Produto *)malloc(sizeof(struct Produto));
}

struct Produto *busca_produto_id(struct Produto *cab, int id) {
    struct Produto *p = cab;
    while (p->prox != NULL && p->id != id) {
        p = p->prox;
    }
    return p;
}

void insere_produto(struct Produto *cab) {
    struct Produto *p = busca_produto_id(cab, -1);
    int ultimo_id = p->id;

    p->prox = cria_no_produto();
    p = p->prox;

    p->id = ultimo_id + 1;
    printf("Nome do produto: ");
    read_string(p->nome, sizeof(p->nome));
    printf("Preço do produto: ");
    read_float(&p->preco);
    printf("Categoria do produto: ");
    read_string(p->categoria, sizeof(p->categoria));
    printf("Descrição do produto: ");
    read_string(p->descricao, sizeof(p->descricao));
    p->prox = NULL;
}

void remove_produto(struct Produto *cab) {
    struct Produto *p = cab->prox;
    struct Produto *ant = cab;
    int id;

    printf("ID do produto: ");
    read_integer(&id);

    while (p != NULL) {
        if (p->id == id) {
            ant->prox = p->prox;
            free(p);
            break;
        }
        p = p->prox;
        ant = ant->prox;
    }
}

void imprime_produto(struct Produto *p) {
    printf("----------");
    printf("\nID: %d\n", p->id);
    printf("Nome: %s\n", p->nome);
    printf("Preço: %f\n", p->preco);
    printf("Categoria: %s\n", p->categoria);
    printf("Descrição: %s\n", p->descricao);
    printf("----------");
}

void imprime_todos_produtos(struct Produto *cab) {
    if (cab->prox == NULL) {
        printf("Lista encadeada ordenada vazia!\n");
        return;
    }

    struct Produto *p = cab->prox;
    while (p != NULL) {
        imprime_produto(p);
        p = p->prox;
    }
    printf("\n");
}

void imprime_produto_id(struct Produto *cab) {
    int id;

    printf("ID do produto: ");
    read_integer(&id);

    struct Produto *p = busca_produto_id(cab, id);
    if (p->id == id) {
        imprime_produto(p);
    } else {
        printf("Produto não encontrado");
    }
}