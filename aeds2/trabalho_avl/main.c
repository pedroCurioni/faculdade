#include <stdio.h>
#include "trabalho_avl.h"

int main() {
	struct noAVL* raiz = NULL; // Raiz da arvore AVL

	insercao(&raiz, 10);
	insercao(&raiz, 2);
	insercao(&raiz, 1);

	// remocao(raiz, 1);

	imprimir(raiz);
	return 0;
}