#include <stdio.h>

typedef struct No
{
    int indice;
    struct No* prox;
} No;


void preenche_grafo_vazio(No* grafo[], int qnt_nos);
void ler_arquivo(No* grafo[], FILE* file, int ordenado, int t1, int t2);
void imprimir(No* grafo[], int n);

int main()
{
    FILE* file = fopen("test.txt", "r");
    //fscanf(file, "%d %d %d", &qnt_nos, &qnt_arestas, &ordenado);

    //No* grafo[qnt_nos];

    //preenche_grafo_vazio(grafo, qnt_nos);
    //ler_arquivo(grafo, file, ordenado, t1, t2);
    //fclose(file);
	printf("Hello World\n");
    return 0;
}


void insert(No* grafo[], int v1, int v2)
{
    No* aux = grafo[v1];
    No* new = malloc(sizeof(No));

    new->indice = v2;
    new->prox = NULL;

    new->prox = aux->prox;
    aux->prox = new;
}

void preenche_grafo_vazio(No* grafo[], int qnt_nos)
{
    for (int i = 0; i < qnt_nos; i++)
    {
        grafo[i] = malloc(sizeof(No));
        grafo[i]->indice = i + 1;
        grafo[i]->prox = NULL;
    }
}

void ler_arquivo(No* grafo[], FILE* file, int ordenado, int t1, int t2)
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

void imprimir(No* grafo[], int n)
{
    No* aux;
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


void dijkstra(No* grafo[], int n, int s)
{
    int analisado[n], distancia[n], antecessor[n];

    for (int i = 0; i < n; i++)
    {
		analisado[i] = 0;
        distancia[i] = -1;
		antecessor[i] = -1;
    }
}
