#include "cliente.h"
#include "utils.h"

struct Cliente *cria_no_cliente() {
    return (struct Cliente *)malloc(sizeof(struct Cliente));
}

struct Cliente *busca_cliente_cpf(struct Cliente *cab, char cpf[12]) {
    struct Cliente *ant = cab;
    struct Cliente *c = cab->prox;

    while (c != NULL && strcmp(c->cpf, cpf) != 0) {
        ant = c;
        c = c->prox;
    }
    return ant;
}

void insere_cliente(struct Cliente *cab) {
    struct Cliente *c = cria_no_cliente();

    /* Adiciona no inicio da lista */
    c->prox = cab->prox;
    cab->prox = c;

    printf("CPF do cliente, somente numeros: ");
    read_string(c->cpf, sizeof(c->cpf));
    printf("Nome do cliente: ");
    read_string(c->nome, sizeof(c->nome));
    printf("Telefone do cliente: ");
    read_string(c->telefone, sizeof(c->telefone));
    printf("E-Mail do cliente: ");
    read_string(c->email, sizeof(c->email));

    printf("\nCliente inserido com sucesso!\n");
    wait_keypress();
}

void editar_cliente(struct Cliente *cab) {
    struct Cliente *c, *ant;
    char cpf[12];
    int controle = -1;

    printf("CPF do cliente, somente numeros: ");
    read_string(cpf, sizeof(cpf));

    ant = busca_cliente_cpf(cab, cpf);
    c = ant->prox;

    if (c == NULL) {
        printf("\nCliente não encontrado\n");
        wait_keypress();
        return;
    } else {
        printf("\n1 - Nome\n"
               "2 - Telefone\n"
               "3 - Email\n");
        imprime_cliente(c);
    }

    while (controle < 1 || controle > 3) {
        printf("\nDigite o numero do dado o qual voce quer editar: ");
        read_integer(&controle);
    }

    switch (controle) {
    case 1:
        printf("Digite o nome desejado: ");
        read_string(c->nome, sizeof(c->nome));
        printf("\nNome alterado com sucesso!\n");
        wait_keypress();
        break;
    case 2:
        printf("Digite o telefone desejado: ");
        read_string(c->telefone, sizeof(c->telefone));
        printf("\nTelefone alterado com sucesso!\n");
        wait_keypress();
        break;
    case 3:
        printf("Digite o email desejada: ");
        read_string(c->email, sizeof(c->email));
        printf("\nEmail alterado com sucesso!\n");
        wait_keypress();
        break;
    default:
        break;
    }
}

void remove_cliente(struct Cliente *cab) {
    struct Cliente *c, *ant;
    char cpf[12];

    printf("CPF do cliente, somente numeros: ");
    read_string(cpf, sizeof(cpf));

    ant = busca_cliente_cpf(cab, cpf);
    c = ant->prox;

    if (c != NULL) {
        ant->prox = c->prox;
        free(c);
        printf("\nCliente removido com sucesso!\n");
    } else {
        printf("\nCliente não encontrado!\n");
    }

    wait_keypress();
}

void imprime_cliente(struct Cliente *c) {
    printf("--------------------\n"
           "CPF: %s\n"
           "Nome: %s\n"
           "Telefone: %s\n"
           "Email: %s\n",
           c->cpf, c->nome, c->telefone, c->email);
}