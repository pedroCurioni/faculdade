struct arvore_avl {
	int chave;
	struct arvore_avl* esq;
	struct arvore_avl* dir;
	int altura;
};

void inserir(struct arvore_avl** raiz, int chave);
void remover(struct arvore_avl** raiz, int chave);