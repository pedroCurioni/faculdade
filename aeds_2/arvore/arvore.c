// arvore.cpp : Defines the entry point for the application.
//

#include "arvore.h"
#include <cstddef>

void inserir(struct arvore_avl** raiz, int chave) {
	if (*raiz == NULL) {
		*raiz = (struct arvore_avl*)malloc(sizeof(struct arvore_avl));
		(*raiz)->chave = chave;
		(*raiz)->esq = NULL;
		(*raiz)->dir = NULL;
		(*raiz)->altura = 0;
	}
	else {
		if (chave < (*raiz)->chave) {
			inserir(&(*raiz)->esq, chave);
		}
		else {
			inserir(&(*raiz)->dir, chave);
		}
	}
}