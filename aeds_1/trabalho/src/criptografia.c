#include "criptografia.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

void encrypt_decrypt_string(char *input, char *key, char *output) {
    int len = strlen(input);
    int key_len = strlen(key);

    for (int i = 0; i < len; ++i) {
        output[i] = input[i] ^ key[i % key_len];
    }

    output[len] = '\0';
}

void encrypt_decrypt_int(int *value, int key) { *value = *value ^ key; }

void encrypt_decrypt_float(float *value, int key) {
    int *intPtr = (int *)value;
    *intPtr ^= key;
}

void encrypt_decrypt_produto(struct Produto *cab_produto, char *senha) {
    struct Produto *p = cab_produto->prox;
    char categoria[255];
    char nome[255];
    char descricao[256];

    while (p != NULL) {
        encrypt_decrypt_int(&p->id, atoi(senha));
        encrypt_decrypt_float(&p->preco, atoi(senha));
        encrypt_decrypt_string(p->categoria, senha, categoria);
        encrypt_decrypt_string(p->nome, senha, nome);
        encrypt_decrypt_string(p->descricao, senha, descricao);
        strcpy(p->categoria, categoria);
        strcpy(p->nome, nome);
        strcpy(p->descricao, descricao);

        p = p->prox;
    }
}

void encrypt_decrypt_cliente(struct Cliente *cab_cliente, char *senha) {
    struct Cliente *c = cab_cliente->prox;
    char cpf[12];
    char nome[64];
    char telefone[16];
    char email[64];

    while (c != NULL) {
        encrypt_decrypt_string(c->cpf, senha, cpf);
        encrypt_decrypt_string(c->nome, senha, nome);
        encrypt_decrypt_string(c->telefone, senha, telefone);
        encrypt_decrypt_string(c->email, senha, email);

        strcpy(c->cpf, cpf);
        strcpy(c->nome, nome);
        strcpy(c->telefone, telefone);
        strcpy(c->email, email);

        c = c->prox;
    }
}
