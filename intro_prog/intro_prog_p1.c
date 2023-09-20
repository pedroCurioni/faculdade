#include <stdio.h>
#include <string.h>

// Declaração das structs
typedef struct {
    // Índice de tranporte urbano
    float itu;
    // Índice de densidade populacional
    float idp;
    // Identificador da região
    char id[60];
} Dados;

typedef struct {
    // Posição da região em x
    int pos_x;
    // Posição da região em y
    int pos_y;
    // Identificador da região
    char id[60];
} Posicao;

// Declaração das funções
void montarMapaDados(Dados dados[35]);
void montarMapaPos(Posicao posicoes[35]);
void juncaoDadosPos(Dados mapa[7][5], Dados dados[35], Posicao posicoes[35]);

int main() {
    Dados mapa[7][5];
    Dados dados[35];
    Posicao posicoes[35];

    montarMapaDados(dados);
    montarMapaPos(posicoes);

    juncaoDadosPos(mapa, dados, posicoes);

    /* Print do mapa de ITU */
    printf("Mapa de ITU");
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 5; y++) {
            printf("%s - ", mapa[x][y].id);
            printf("%f", mapa[x][y].itu);
        }
        printf("\n");
    }

    /* Print do mapa de IDP */
    printf("Mapa de IDP");
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 5; y++) {
            printf("%s - ", mapa[x][y].id);
            printf("%f", mapa[x][y].idp);
        }
        printf("\n");
    }

    /* Print do mapa relacional */
    printf("Mapa relacianal");
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 5; y++) {
            if ((mapa[x][y].itu < 20) && (mapa[x][y].idp > 55)) {
                printf("%s - ", mapa[x][y].id);
                printf("1");
            } else if ((mapa[x][y].itu > 0) && (mapa[x][y].idp == 0)) {
                printf("%s - ", mapa[x][y].id);
                printf("2");
            } else {
                printf("%s - ", mapa[x][y].id);
                printf("0");
            }
        }
        printf("\n");
    }

    return 0;
}

void montarMapaDados(Dados dados[35]) {
    /*
     * Monta uma lista no formato da struct Dados com tamanho 35 items
     * Com as infromações de identificador da região, ITU E ITP
     */
    for (int x = 0; x < 35; x++) {
        printf("Digite a identificacao da regiao: ");
        scanf("%s", &dados[x].id);

        printf("Digite o indice de transporte urbano (ITU): ");
        scanf("%f", &dados[x].itu);

        printf("Digite o indice de densidade populacional (IDP): ");
        scanf("%f", &dados[x].idp);
    }
}

void montarMapaPos(Posicao posicoes[35]) {
    /*
     * Monta uma lista no formato da struct Posicao com tamanho 35 items
     * Com as infromações de identificador da região, posição em x e posição em
     * y
     */
    for (int x = 0; x < 35; x++) {
        printf(
            "Digite a identificacao da regiao, deve ser identica a digitada na "
            "outra etapa: ");
        scanf("%s", &posicoes[x].id);

        printf("Digite a posicao em X da regiao: ");
        scanf("%f", &posicoes[x].pos_x);

        printf("Digite a posicao em Y da regiao: ");
        scanf("%f", &posicoes[x].pos_y);
    }
}

void juncaoDadosPos(Dados mapa[7][5], Dados dados[35], Posicao posicoes[35]) {
    /*
     * Realiza a união da lista de dados com a lista de posições
     * A variavel i controla a posição da lista de dados
     * A variavel j controla a posição da lista de posicoes
     */
    for (int i = 0; i < 35; i++) {
        for (int j = 0; j < 35; j++) {
            if (strcmp(dados[i].id, posicoes[j].id) == 0) {
                strcpy(mapa[posicoes[j].pos_x][posicoes[j].pos_y].id,
                       dados[i].id);
                mapa[posicoes[j].pos_x][posicoes[j].pos_y].idp = dados[i].idp;
                mapa[posicoes[j].pos_x][posicoes[j].pos_y].itu = dados[i].itu;
            }
        }
    }
}