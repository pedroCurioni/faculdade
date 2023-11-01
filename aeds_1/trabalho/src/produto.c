#include "produto.h"
#include "utils.h"

struct Produto *cria_no_produto() {
    return (struct Produto *)malloc(sizeof(struct Produto));
}

struct Produto *busca_produto(struct Produto *cab, int id) {
    struct Produto *p = cab;
    while (p->id != id || p->prox != NULL) {
        p = p->prox;
    }
    return p;
}

void insere_produto(struct Produto *cab) {
    struct Produto *p = busca_produto(cab, -1);
    int ultimo_id = p->id;

    p->prox = cria_no_produto();
    p = p->prox;

    p->id = ultimo_id + 1;
    printf("\nNome do produto: ");
    read_string(p->nome);
    printf("\nPreço do produto: ");
    read_float(&p->preco);
    printf("\nCategoria do produto: ");
    read_string(p->categoria);
    printf("\nDescrição do produto: ");
    read_string(p->descricao);
    p->prox = NULL;
}

void imprime_produto(struct Produto *p) {
    printf("ID: %d", p->id);
    printf("Nome: %s", p->nome);
    printf("Preço: %f", p->preco);
    printf("Categoria: %s", p->categoria);
    printf("Descrição: %s", p->descricao);
    printf("-----");
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