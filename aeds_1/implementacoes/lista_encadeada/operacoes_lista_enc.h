#include <stdio.h>
#include <stdlib.h>

struct no {
    int c;
    struct no *prox;
};

/* \brief
   \param cab
   \param n
*/
void cria_lista_ordenada(struct no *cab, int n);

/* \brief
   \param cab
   \param k
   \return
*/
struct no *busca_ordenada(struct no *cab, int k);
void insere_ordenada(struct no *cab, int k);
void apaga_lista(struct no *cab);
void imprime_lista(struct no *cab);
struct no *cria_no();