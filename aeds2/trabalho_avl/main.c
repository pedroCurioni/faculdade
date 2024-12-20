#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct noAVL {
    char nome[1000];
    char descricao[1000];
    int fb; // Fator de balanceamento
    struct noAVL* pai;
    struct noAVL* esquerda;
    struct noAVL* direita;
};

struct noAVL* busca(struct noAVL* raiz, char nome[]);

void insercao(struct noAVL** raiz, char nome[], char descricao[]);

struct noAVL* sucessor(struct noAVL* no);

void atualiza_pai(struct noAVL* no, struct noAVL* novo);

void remocao(struct noAVL** raiz, char nome[]);

void imprimir(struct noAVL* raiz);

int profundidade_filho(struct noAVL* no);

void atualiza_fb(struct noAVL* no);

void rr(struct noAVL* no);

void ll(struct noAVL* no);

void balancear(struct noAVL** raiz, struct noAVL* no);

void balancear_no(struct noAVL* no);

void altura_arvore(struct noAVL* no);

int altura_no(struct noAVL* no);

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


struct noAVL* busca(struct noAVL* raiz, char nome[]) {
    struct noAVL* aux = raiz;
    while (aux != NULL) {
        if (strcmp(nome, aux->nome) < 0) {
            aux = aux->esquerda;
        }
        else if (strcmp(nome, aux->nome) > 0) {
            aux = aux->direita;
        }
        else {
            if (strcmp(nome, aux->nome) == 0) {
                return aux;
            }
            return NULL;
        }
    }
}

void insercao(struct noAVL** raiz, char nome[], char descricao[]) {
    struct noAVL* novo = (struct noAVL*)malloc(sizeof(struct noAVL));

    if (novo == NULL) {
        printf("Ocorreu um erro ao alocar!\n");
        return;
    }

    struct noAVL* aux = *raiz;
    struct noAVL* pai = NULL;

    strcpy(novo->nome, nome);
    strcpy(novo->descricao, descricao);
    novo->fb = 0;
    novo->pai = NULL;
    novo->esquerda = NULL;
    novo->direita = NULL;

    // Se a raiz for nula a arvore está vazia inicialize ela
    if (*raiz == NULL) {
        *raiz = novo;
        printf("Inserção de %s com sucesso\n", nome);
        return;
    }

    // Procura o espaço correto para inserir o nó
    while (aux != NULL) {
        pai = aux;
        if (strcmp(novo->nome, aux->nome) == 0) {
            printf("%s já se encontra no dicionário\n", nome);
            return;
        }
        else if (strcmp(novo->nome, aux->nome) < 0) {
            aux = aux->esquerda;
        }
        else {
            aux = aux->direita;
        }
    }
    if (strcmp(novo->nome, pai->nome) < 0) {
        pai->esquerda = novo;
    }
    else {
        pai->direita = novo;
    }
    novo->pai = pai;
    printf("Inserção de %s com sucesso\n", nome);

    balancear(raiz, pai);
}

struct noAVL* sucessor(struct noAVL* no) {
    struct noAVL* aux = no->direita;
    while (aux->esquerda != NULL) {
        aux = aux->esquerda;
    }
    return aux;
}

void atualiza_pai(struct noAVL* no, struct noAVL* novo) {
    if (no->pai != NULL) {
        if (no->pai->esquerda == no) {
            no->pai->esquerda = novo;
        }
        else {
            no->pai->direita = novo;
        }
    }
}

void remocao(struct noAVL** raiz, char nome[]) {
    struct noAVL* no = busca(*raiz, nome);
    struct noAVL* inicio_balanceamento = NULL;

    if (no == NULL) {
        printf("Operação de remoção da palavra %s inválida\n", nome);
        return;
    }
    else if (no->esquerda == NULL && no->direita == NULL) { // Nó folha
        atualiza_pai(no, NULL);
        inicio_balanceamento = no->pai;
    }
    else if (no->esquerda == NULL) {
        atualiza_pai(no, no->direita);
        inicio_balanceamento = no->pai;
    }
    else if (no->direita == NULL) {
        atualiza_pai(no, no->esquerda);
        inicio_balanceamento = no->pai;
    }
    else {
        struct noAVL* suc = sucessor(no);

        suc->esquerda = no->esquerda;
        if (no->direita != suc) {
            suc->direita = no->direita; // Sucessor aponta para o filho direito do nó
            suc->pai->esquerda =
                NULL; // Tira a referencia do sucessor do pai dele
        }
        else {
            suc->direita =
                NULL; // O Suecssor e o primeiro filho a direita do nó
        }

        atualiza_pai(no, suc);
        no->esquerda->pai = suc;
        no->direita->pai = suc;

        inicio_balanceamento = suc->pai;

        suc->pai = no->pai;
    }
    printf("%s removido com sucesso\n", nome);
    balancear(raiz, inicio_balanceamento);
    free(no);
}

void imprimir(struct noAVL* raiz) {
    if (raiz != NULL) {
        imprimir(raiz->esquerda);
        printf("Fator de Balanceamento: %d\tValor: %s\n", raiz->fb, raiz->nome);
        imprimir(raiz->direita);
    }
}

int profundidade_filho(struct noAVL* no) {
    if (no == NULL) {
        return -1;
    }
    int esq = profundidade_filho(no->esquerda);
    int dir = profundidade_filho(no->direita);

    if (esq > dir) {
        return esq + 1;
    }
    else {
        return dir + 1;
    }
}

void atualiza_fb(struct noAVL* no) {
    if (no != NULL) {
        no->fb = profundidade_filho(no->esquerda) - profundidade_filho(no->direita);
    }
}

void ll(struct noAVL* no) {
    struct noAVL* filho_dir = no->direita;

    no->direita = filho_dir->esquerda;
    if (filho_dir->esquerda != NULL) {
        filho_dir->esquerda->pai = no;
    }
    filho_dir->esquerda = no;

    filho_dir->pai = no->pai;
	atualiza_pai(no, filho_dir);

    no->pai = filho_dir;

    atualiza_fb(no);
    atualiza_fb(filho_dir);
}

void rr(struct noAVL* no) {
    struct noAVL* filho_esq = no->esquerda;

    no->esquerda = filho_esq->direita;
    if (filho_esq->direita != NULL) {
        filho_esq->direita->pai = no;
    }
    filho_esq->direita = no;

    filho_esq->pai = no->pai;
	atualiza_pai(no, filho_esq);

    no->pai = filho_esq;

    atualiza_fb(no);
    atualiza_fb(filho_esq);
}

void balancear_no(struct noAVL* no) {
    struct noAVL* aux = NULL;
    // Pode ocorrer de uma inserçãoo ser realizada,
    // então atualiza o fator de balanceamento enquanto sobe na arvore
    atualiza_fb(no);
    if (no->fb == 2) {
        if (no->esquerda->fb == -1) {
            aux = no->esquerda;
            ll(aux);
        }
        rr(no);
    }
    else if (no->fb == -2) {
        if (no->direita->fb == 1) {
            aux = no->direita;
            rr(aux);
        }
        ll(no);
    }
}

void balancear(struct noAVL** raiz, struct noAVL* no) {
    struct noAVL* ultimo_no = no;
    while (no != NULL) {
        balancear_no(no);
        ultimo_no = no;
        no = no->pai;
    }
    if (ultimo_no != NULL && ultimo_no->pai == NULL) {
        *raiz = ultimo_no;
    }
}

int altura_no(struct noAVL* no) {
    int altura = 1;
    while (no->pai != NULL) {
        altura++;
        no = no->pai;
    }
    return altura;
}

void altura_arvore(struct noAVL* no) {
    if (no != NULL) {
        altura_arvore(no->esquerda);
        printf("%s h=%d\t", no->nome, altura_no(no));
        altura_arvore(no->direita);
    }
}
