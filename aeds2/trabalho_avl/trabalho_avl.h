#ifndef TRABALHO_AVL_H
#define TRABALHO_AVL_H

struct noAVL {
	int valor;
	int fb;	// Fator de balanceamento
	struct noAVL* pai;
	struct noAVL* esquerda;
	struct noAVL* direita;
};

void busca(struct noAVL* raiz, struct noAVL** result, int v);

void insercao(struct noAVL** raiz, int v);

void remocao(struct noAVL* raiz, int v);

void imprimir(struct noAVL* raiz);

int altura(struct noAVL* no);

void atualiza_fb(struct noAVL* no);

void rr(struct noAVL* no);

void ll(struct noAVL* no);

void balancear(struct noAVL* no);

void balancear_no(struct noAVL* no);

#endif // TRABALHO_AVL_H