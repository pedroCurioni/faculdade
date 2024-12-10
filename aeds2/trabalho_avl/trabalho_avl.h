#ifndef TRABALHO_AVL_H
#define TRABALHO_AVL_H

struct noAVL {
	char nome[256];
	char descricao[1000];
	int fb;	// Fator de balanceamento
	struct noAVL* pai;
	struct noAVL* esquerda;
	struct noAVL* direita;
};

struct noAVL* busca(struct noAVL* raiz, char nome[]);

void insercao(struct noAVL** raiz, char nome[], char descricao[]);

void remocao(struct noAVL** raiz, char nome[]);

void imprimir(struct noAVL* raiz);

int profundidade_filho(struct noAVL* no);

void atualiza_fb(struct noAVL* no);

void rr(struct noAVL* no);

void ll(struct noAVL* no);

void balancear(struct noAVL** raiz, struct noAVL* no);

void balancear_no(struct noAVL* no);

void altura_arvore(struct noAVL* no);

#endif // TRABALHO_AVL_H