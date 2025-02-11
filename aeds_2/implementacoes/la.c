#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int indice;
    struct No *prox;
} No;

void insert(No *grafo[], int v1, int v2)
{
    No *aux = grafo[v1];
    No *new = malloc(sizeof(No));

    new->indice = v2;
    new->prox = NULL;

    new->prox = aux->prox;
    aux->prox = new;
}

void preenche_grafo_vazio(No *grafo[], int qnt_nos)
{
    for (int i = 0; i < qnt_nos; i++)
    {
        grafo[i] = malloc(sizeof(No));
        grafo[i]->indice = i + 1;
        grafo[i]->prox = NULL;
    }
}

void ler_arquivo(No *grafo[], FILE *file, int ordenado, int t1, int t2)
{
    char line[10];
    int count = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (count == 0)
        {
            count++;
            continue;
        }
        sscanf(line, "%d %d", &t1, &t2);

        insert(grafo, t1 - 1, t2);
        if (ordenado != 1) // Se o grafo não e ordenado
        {
            insert(grafo, t2 - 1, t1);
        }
    }
}

void imprimir(No *grafo[], int n)
{
    No *aux;
    for (int i = 0; i < n; i++)
    {
        printf("%d: ", i + 1);
        aux = grafo[i]->prox;
        while (aux != NULL)
        {
            printf("%d ", aux->indice);
            aux = aux->prox;
        }
        printf("\n");
    }
}

int grau_saida(No *grafo[], int valor)
{
    int qnt_grau = 0;
    No *aux = grafo[valor - 1]->prox;

    while (aux != NULL)
    {
        qnt_grau++;
        aux = aux->prox;
    }

    return qnt_grau;
}

int grau_entrada(No *grafo[], int qnt_nos, int valor)
{
    int qnt_grau = 0;
    for (int i = 0; i < qnt_nos; i++)
    {
        if (i == valor - 1)
        {
            continue;
        }

        No *aux = grafo[i]->prox;
        while (aux != NULL)
        {
            if (aux->indice == valor)
            {
                qnt_grau++;
            }
            aux = aux->prox;
        }
    }

    return qnt_grau;
}

int grau_maximo_entrada(int qnt_nos, No *grafo[])
{
    int max = 0;
    for (int i = 0; i < qnt_nos; i++)
    {
        int tmp_grau = grau_entrada(grafo, qnt_nos, i);
        if (tmp_grau > max)
        {
            max = tmp_grau;
        }
    }
    return max;
}

int grau_maximo_saida(int qnt_nos, No *grafo[])
{
    int max = 0;
    for (int i = 0; i < qnt_nos; i++)
    {   
        int tmp_grau = grau_saida(grafo, i);
        
        if (tmp_grau > max)
        {
            max = tmp_grau;
        }
    }
    return max;
}

int grau_minimo_saida(int qnt_nos, No *grafo[])
{
    int min = grau_saida(grafo, 1);
    for (int i = 0; i < qnt_nos; i++)
    {
        int tmp_grau = grau_saida(grafo, i);
        if (tmp_grau < min)
        {
            min = tmp_grau;
        }
    }
    return min;
}
int grau_minimo_entrada(int qnt_nos, No *grafo[])
{
    int min = grau_entrada(grafo, qnt_nos, 1);
    for (int i = 0; i < qnt_nos; i++)
    {
        int tmp_grau = grau_entrada(grafo, qnt_nos, i);
        if (tmp_grau < min)
        {
            min = tmp_grau;
        }
    }
    return min;
}

void no_isolado(No *grafo[], int qnt_nos, int valor)
{
    if (grau_saida(grafo, valor) == 0 && grau_entrada(grafo, qnt_nos, valor) == 0)
    {
        printf("O nó %d está islado\n", valor);
    }
    else
    {
        printf("O nó %d não esta isolado\n", valor);
    }
}

void main()
{
    int qnt_nos, qnt_arestas, ordenado, t1, t2;

    FILE *file = fopen("test.txt", "r");
    fscanf(file, "%d %d %d", &qnt_nos, &qnt_arestas, &ordenado);

    No *grafo[qnt_nos];

    preenche_grafo_vazio(grafo, qnt_nos);
    ler_arquivo(grafo, file, ordenado, t1, t2);
    fclose(file);

    // printf("GRAU SAIDA 5: %d\n", grau_saida(grafo, 5));
    // printf("GRAU ENTRADA 5: %d\n", grau_entrada(grafo, qnt_nos, 5));

    printf("Grau maximo entrada: %d\n", grau_maximo_entrada(qnt_nos, grafo));
    printf("%d", qnt_nos);
    // printf("Grau maximo saida: %d\n", grau_maximo_saida(qnt_nos, grafo));

    // no_isolado(grafo, qnt_nos, 5);

    imprimir(grafo, qnt_nos);
}