#include "criptografia.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

void encrypt_decrypt_string(char *data, char *password) {
    int i, j = 0;
    int data_len = strlen(data);
    int password_len = strlen(password);

    for (i = 0; i < data_len; i++) {
        data[i] = data[i] ^ password[j];
        j = (j + 1) % password_len;
    }
}

void encrypt_decrypt_int(int *value, int key) { *value = *value ^ key; }

void encrypt_decrypt_float(float *value, int key) {
    int *intPtr = (int *)value;
    *intPtr ^= key;
}

void encrypt_decrypt_produto(struct Produto *cab_produto, char *senha) {
    struct Produto *p = cab_produto->prox;

    while (p != NULL) {
        encrypt_decrypt_int(&p->id, atoi(senha));
        encrypt_decrypt_float(&p->preco, atoi(senha));
        encrypt_decrypt_string(p->categoria, senha);
        encrypt_decrypt_string(p->categoria, senha);
        encrypt_decrypt_string(p->nome, senha);
        encrypt_decrypt_string(p->descricao, senha);

        p = p->prox;
    }
}

void encrypt_decrypt_cliente(struct Cliente *cab_cliente, char *senha) {
    struct Cliente *c = cab_cliente->prox;

    while (c != NULL) {
        encrypt_decrypt_string(c->cpf, senha);
        encrypt_decrypt_string(c->nome, senha);
        encrypt_decrypt_string(c->telefone, senha);
        encrypt_decrypt_string(c->email, senha);

        c = c->prox;
    }
}
