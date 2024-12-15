#include "trabalho_avl.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char nome_arquivo[100], buffer[1000], nome[1000], descricao[1000];
    FILE *arquivo;
    struct noAVL *raiz = NULL;

    if (argc > 0) {
        arquivo = fopen(argv[1], "r");
    } else {
        printf("Nao foi recebido um arquivo\n");
        return 1;
    }

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        if (buffer[0] == '1') {
            printf("Árvores criadas sucesso:\n");
        } else if (buffer[0] == '2') {
            fgets(nome, sizeof(buffer), arquivo);
            nome[strcspn(nome, "\n")] = '\0';

            remocao(&raiz, nome);
        } else if (buffer[0] == '3') {
            fgets(nome, sizeof(buffer), arquivo);
            nome[strcspn(nome, "\n")] = '\0';

            fgets(descricao, sizeof(buffer), arquivo);
            descricao[strcspn(descricao, "\n")] = '\0';

            insercao(&raiz, nome, descricao);
        } else if (buffer[0] == '4') {
            fgets(nome, sizeof(buffer), arquivo);
            nome[strcspn(nome, "\n")] = '\0';

            struct noAVL *result = busca(raiz, nome);
            if (result == NULL) {
                printf("Palavra %s não encontrada\n", nome);
            } else {
                printf("%s encontrado no dicionario h=%d\n%s: %s\n",
                       result->nome, altura_no(result), result->nome,
                       result->descricao);
            }
        } else if (buffer[0] == '5') {
            altura_arvore(raiz);
            printf("\n");
        }
        printf("\n");
    }

    fclose(arquivo);

    return 0;
}