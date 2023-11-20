#include "arquivo.h"
#include "cliente.h"
#include "criptografia.h"
#include "produto.h"
#include "utils.h"

void export_produto(struct Produto *cab_produto) {
    struct Produto *p = cab_produto->prox;
    FILE *file_produto;

    file_produto = fopen("produto.bin", "wb");
    if (file_produto == NULL) {
        printf("Erro ao criar arquivo de produtos\n");
        wait_keypress();
        return;
    }

    while (p != NULL) {
        fwrite(p, sizeof(struct Produto), 1, file_produto);
        p = p->prox;
    }
    fclose(file_produto);

    printf("\nDados de produto exportados com sucesso!\n");
}

void export_cliente(struct Cliente *cab_cliente) {
    struct Cliente *c = cab_cliente->prox;
    FILE *file_cliente;

    file_cliente = fopen("cliente.bin", "wb");
    if (file_cliente == NULL) {
        printf("Erro ao criar arquivo de cliente\n");
        wait_keypress();
        return;
    }

    while (c != NULL) {
        fwrite(c, sizeof(struct Cliente), 1, file_cliente);
        c = c->prox;
    }
    fclose(file_cliente);

    printf("\nDados de cliente exportados com sucesso!\n");
}

void export(struct Produto *cab_produto, struct Cliente *cab_cliente) {
    char senha[64];

    printf("Digite uma senha numerica para criptografar os dados: ");
    read_string(senha, sizeof(senha));

    encrypt_decrypt_produto(cab_produto, senha);
    encrypt_decrypt_cliente(cab_cliente, senha);

    export_produto(cab_produto);
    export_cliente(cab_cliente);

    wait_keypress();
}

void import_produto(struct Produto *cab_produto, int *ultimo_id) {
    struct Produto *p, *ant_p;
    FILE *file_produto;
    cab_produto->prox = cria_no_produto();
    ant_p = cab_produto;
    p = cab_produto->prox;

    file_produto = fopen("produto.bin", "rb");
    if (file_produto == NULL) {
        printf("Erro ao abrir arquivo de produto\n");
        wait_keypress();
        return;
    }

    while (fread(p, sizeof(struct Produto), 1, file_produto) == 1) {
        p->prox = cria_no_produto();
        ant_p = p;
        p = p->prox;
    }

    // Ultima posição fica vazia
    free(ant_p->prox);
    ant_p->prox = NULL;
    (*ultimo_id) = ant_p->id;

    fclose(file_produto);

    printf("\nDados de produto importados com sucesso!\n");
}

void import_cliente(struct Cliente *cab_cliente) {
    struct Cliente *c, *ant_c;
    FILE *file_cliente;

    cab_cliente->prox = cria_no_cliente();
    ant_c = cab_cliente;
    c = cab_cliente->prox;

    file_cliente = fopen("cliente.bin", "rb");
    if (file_cliente == NULL) {
        printf("Erro ao abrir arquivo de cliente\n");
        wait_keypress();
        return;
    }

    // Read data from the binary file and save it to the list
    while (fread(c, sizeof(struct Cliente), 1, file_cliente) == 1) {
        c->prox = cria_no_cliente();
        ant_c = c;
        c = c->prox;
    }

    // Ultima posição fica vazia
    free(ant_c->prox);
    ant_c->prox = NULL;

    fclose(file_cliente);

    printf("\nDados de cliente importados com sucesso!\n");
}

void import(struct Produto *cab_produto, struct Cliente *cab_cliente,
            int *ultimo_id) {
    char senha[64];

    printf("Digite uma senha numerica para descriptografar os dados: ");
    read_string(senha, sizeof(senha));
    
    import_produto(cab_produto, ultimo_id);
    import_cliente(cab_cliente);

    encrypt_decrypt_produto(cab_produto, senha);
    encrypt_decrypt_cliente(cab_cliente, senha);

    wait_keypress();
}