#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "trabalho_avl.h"


int main() {
	struct noAVL* raiz = NULL;
	FILE* arquivo;
	char buffer[10000], nome[256], descricao[1000];

	arquivo = fopen("1.in", "r");

	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo\n");
		return 1;
	}

	while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
		if (buffer[0] == '1') {
			printf("Árvores criadas sucesso:\n");
		}
		else if (buffer[0] == '2') {
			sscanf(buffer + 1, "%s", nome);
			nome[strcspn(nome, "\n")] = '\0';

			remocao(&raiz, nome);
		}
		else if (buffer[0] == '3') {
			fgets(nome, sizeof(buffer), arquivo);
			nome[strcspn(nome, "\n")] = '\0';

			fgets(descricao, sizeof(buffer), arquivo);
			descricao[strcspn(descricao, "\n")] = '\0';

			insercao(&raiz, nome, descricao);
		}
		else if (buffer[0] == '4') {
			fgets(nome, sizeof(buffer), arquivo);
			nome[strcspn(nome, "\n")] = '\0';

			struct noAVL* result = busca(raiz, nome);
			if (result == NULL) {
				printf("Palavra %s não encontrada\n", nome);
			}
			else {
				printf("%s encontrado no dicionario fb=%d\n%s: %s\n", result->nome, result->fb, result->nome, result->descricao);
			}
		}
		else if (buffer[0] == '5') {
			fgets(nome, sizeof(buffer), arquivo);
			nome[strcspn(nome, "\n")] = '\0';

			struct noAVL* result = busca(raiz, nome);
			if (result == NULL) {
				printf("Palavra %s não encontrada\n", nome);
			}
			else {
				printf("%s encontrado no dicionario fb=%d\n%s: %s\n", result->nome, result->fb, result->nome, result->descricao);
			}
		}
		else if (buffer[0] == '6') {
			altura_arvore(raiz);
			printf("\n");
		}
		else if (buffer[0] == '7') {
			break;
		}
	}

	return 0;
}