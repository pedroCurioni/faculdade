#include "trabalho_avl.h"

#include <stdio.h>
#include <stdlib.h>


void busca(struct noAVL* raiz, struct noAVL** result, int v) {
	struct noAVL* aux = raiz;
	while (aux != NULL) {
		if (v < aux->valor) {
			aux = aux->esquerda;
		}
		else if (v > aux->valor) {
			aux = aux->direita;
		}
		else {
			*result = aux;
			return;
		}
	}
	*result = NULL;
}

void insercao(struct noAVL** raiz, int v) {
	struct noAVL* aux = *raiz;
	struct noAVL* pai = NULL;
	struct noAVL* novo = (struct noAVL*)malloc(sizeof(struct noAVL));

	if (novo == NULL) {
		printf("Ocorreu um erro ao alocar!\n");
		return;
	}

	novo->valor = v;
	novo->fb = 0;
	novo->pai = NULL;
	novo->esquerda = NULL;
	novo->direita = NULL;

	// Se a raiz for nula a arvore está vazia inicialize ela
	if (*raiz == NULL) {
		*raiz = novo;
		return;
	}

	// Procura o espaço correto para inserir o nó
	while (aux != NULL) {
		pai = aux;
		if (v < aux->valor) {
			aux->fb++;
			aux = aux->esquerda;
		}
		else {
			aux->fb--;
			aux = aux->direita;
		}
	}
	if (v < pai->valor) {
		pai->esquerda = novo;
	}
	else {
		pai->direita = novo;
	}
	novo->pai = pai;
	printf("Nó adicionado com sucesso!\n");

	balancear(pai);
}

void remocao(struct noAVL* raiz, int v) {
	struct noAVL* no = NULL;
	busca(raiz, &no, v);

	if (no == NULL) {
		return;
	}
	else if (no->esquerda == NULL && no->direita == NULL) { // Nó folha
		if (no->pai->esquerda == no) {
			no->pai->esquerda = NULL;
		}
		else {
			no->pai->direita = NULL;
		}
	}
	else if (no->esquerda == NULL) {
		if (no->pai->esquerda == no) {
			no->pai->esquerda = no->direita;
		}
		else {
			no->pai->direita = no->direita;
		}
	}
	else if (no->direita == NULL) {
		if (no->pai->esquerda == no) {
			no->pai->esquerda = no->esquerda;
		}
		else {
			no->pai->direita = no->esquerda;
		}
	}
	balancear(no->pai);
	free(no);
}

void imprimir(struct noAVL* raiz) {
	if (raiz != NULL) {
		imprimir(raiz->esquerda);
		printf("Fator de Balanceamento: %d\tValor: %d\n", raiz->fb, raiz->valor);
		imprimir(raiz->direita);
	}
}

int altura(struct noAVL* no) {
	if (no == NULL) {
		return -1;
	}
	int esq = altura(no->esquerda);
	int dir = altura(no->direita);

	// Ternário para retornar o maior valor, contando com o no atual
	return (esq > dir ? esq : dir) + 1;
}

void atualiza_fb(struct noAVL* no) {
	if (no != NULL) {
		no->fb = altura(no->esquerda) - altura(no->direita);
	}
}

void rr(struct noAVL* no) {
}

void ll(struct noAVL* no) {

}

void balancear_no(struct noAVL* no) {
	if (no->fb == 2) {
		if (no->esquerda->fb == -1) {
			ll(no->esquerda);
		}
		rr(no);
	}
	else if (no->fb == -2) {
		if (no->direita->fb == 1) {
			rr(no->direita);
		}
		ll(no);
	}
}

void balancear(struct noAVL* no) {
	while (no != NULL) {
		balancear_no(no);
		no = no->pai;
	}
}
