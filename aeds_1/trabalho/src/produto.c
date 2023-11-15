#include "produto.h"
#include "utils.h"

struct Produto *cria_no_produto() {
    return (struct Produto *)malloc(sizeof(struct Produto));
}

struct Produto *busca_produto_id(struct Produto *cab, int id) {
    struct Produto *ant = cab;
    struct Produto *p = cab->prox;

    while (p != NULL && p->id != id) {
        ant = p;
        p = p->prox;
    }
    return ant;
}

void busca_produto_nome(struct Produto *cab) {
    struct Produto *p;
    char nome[64];

    printf("Nome do produto: ");
    read_string(nome, sizeof(nome));

    p = cab->prox;

    while (p != NULL) {
        if (strcmp(nome, p->nome) == 0) {
            imprime_produto(p);
        }
        p = p->prox;
    }

    wait_keypress();
}

void busca_produto_preco(struct Produto *cab) {
    struct Produto *p;
    int preco_minimo, preco_maximo;

    printf("Preço minimo do produto: ");
    read_integer(&preco_minimo);
    printf("Preço maximo do produto: ");
    read_integer(&preco_maximo);

    p = cab->prox;

    while (p != NULL) {
        if (p->preco >= preco_minimo && p->preco <= preco_maximo) {
            imprime_produto(p);
        }
        p = p->prox;
    }

    wait_keypress();
}

void busca_produto_categoria(struct Produto *cab) {
    struct Produto *p;
    char categoria[32];

    printf("Categoria do produto: ");
    read_string(categoria, sizeof(categoria));

    p = cab->prox;

    while (p != NULL) {
        if (strcmp(categoria, p->categoria) == 0) {
            imprime_produto(p);
        }
        p = p->prox;
    }

    wait_keypress();
}

void insere_produto(struct Produto *cab, int *ultimo_id) {
    struct Produto *ant, *p;

    ant = busca_produto_id(cab, -1);

    *ultimo_id = *ultimo_id + 1;

    p = cria_no_produto();
    p->id = *ultimo_id;
    printf("Nome do produto: ");
    read_string(p->nome, sizeof(p->nome));
    printf("Preço do produto: ");
    read_float(&p->preco);
    printf("Categoria do produto: ");
    read_string(p->categoria, sizeof(p->categoria));
    printf("Descrição do produto: ");
    read_string(p->descricao, sizeof(p->descricao));
    p->prox = NULL;

    p->prox = ant->prox;
    ant->prox = p;

    printf("\nProduto inserido com sucesso!\n");
    wait_keypress();
}

void editar_produto(struct Produto *cab) {
    struct Produto *p, *ant;
    int id, controle = -1;

    printf("ID do produto: ");
    read_integer(&id);

    ant = busca_produto_id(cab, id);
    p = ant->prox;

    if (p == NULL) {
        printf("\nProduto não encontrado\n");
        wait_keypress();
        return;
    } else {
        printf("\n1 - Nome\n"
               "2 - Preço\n"
               "3 - Categoria\n"
               "4 - Descrição\n");
        imprime_produto(p);
    }

    while (controle < 1 || controle > 4) {
        printf("\nDigite o numero do dado o qual voce quer editar: ");
        read_integer(&controle);
    }

    switch (controle) {
    case 1:
        printf("Digite o nome desejado: ");
        read_string(p->nome, sizeof(p->nome));
        printf("\nNome alterado com sucesso!\n");
        wait_keypress();
        break;
    case 2:
        printf("Digite o preço desejado: ");
        read_float(&p->preco);
        printf("\nPreço alterado com sucesso!\n");
        wait_keypress();
        break;
    case 3:
        printf("Digite a categoria desejada: ");
        read_string(p->categoria, sizeof(p->categoria));
        printf("\nCategoria alterada com sucesso!\n");
        wait_keypress();
        break;
    case 4:
        printf("Digite a descrição desejada: ");
        read_string(p->descricao, sizeof(p->descricao));
        printf("\nDescrição alterada com sucesso!\n");
        wait_keypress();
        break;
    default:
        break;
    }
}

void remove_produto(struct Produto *cab) {
    struct Produto *p, *ant;
    int id;

    printf("ID do produto: ");
    read_integer(&id);

    ant = busca_produto_id(cab, id);
    p = ant->prox;

    if (p != NULL) {
        ant->prox = p->prox;
        free(p);
        printf("\nProduto removido com sucesso!\n");
    } else {
        printf("\nProduto não encontrado!\n");
    }

    wait_keypress();
}

void imprime_produto(struct Produto *p) {
    printf("--------------------\n"
           "ID: %d\n"
           "Nome: %s\n"
           "Preço: %.2f\n"
           "Categoria: %s\n"
           "Descrição: %s\n",
           p->id, p->nome, p->preco, p->categoria, p->descricao);
}

void imprime_todos_produtos(struct Produto *cab) {
    struct Produto *p = cab->prox;

    if (p == NULL) {
        printf("Não existem produtos no sistema!\n");
        wait_keypress();
        return;
    }

    while (p != NULL) {
        imprime_produto(p);
        p = p->prox;
    }
    printf("\n");

    wait_keypress();
}

void imprime_produto_id(struct Produto *cab) {
    struct Produto *p, *ant;
    int id;

    printf("ID do produto: ");
    read_integer(&id);

    ant = busca_produto_id(cab, id);
    p = ant->prox;

    if (p != NULL && p->id == id) {
        imprime_produto(p);
        printf("\n");
    } else {
        printf("\nProduto não encontrado\n");
    }

    wait_keypress();
}