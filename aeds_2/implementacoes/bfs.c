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

        insert(grafo, t1 - 1, t2 - 1);
        if (ordenado != 1) // Se o grafo não e ordenado
        {
            insert(grafo, t2 - 1, t1 - 1);
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
            printf("%d ", aux->indice + 1);
            aux = aux->prox;
        }
        printf("\n");
    }
}

void print_plus_one(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d | ", arr[i] + 1);
    }
}

void print_int_array(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d | ", arr[i]);
    }
}

void print_char_array(char arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c | ", arr[i]);
    }
}

void print_loop(int d[], int fila[], int pi[], char cor[], int n)
{
    printf("\nDistancia: ");
    print_int_array(d, n);

    printf("\nPi: ");
    print_plus_one(pi, n);

    printf("\nCor: ");
    print_char_array(cor, n);

    printf("\nFila: ");
    print_plus_one(fila, n);

    printf("\n\n");
}

void bfs(No *grafo[], int n, int s, int pi[])
{
    int d[n], fila[n], start_fila = 0, end_fila = 1, u, v;
    char cor[n];
    No *aux = grafo[s]->prox;

    for (int i = 0; i < n; i++)
    {
        d[i] = -2;
        pi[i] = -2;
        cor[i] = 'b';
        fila[i] = -2;
    }

    d[s] = 0;
    cor[s] = 'c';
    fila[start_fila] = s;

    print_loop(d, fila, pi, cor, n);

    while ((fila[start_fila] != -1) && (end_fila != start_fila))
    {
        u = fila[start_fila];
        aux = grafo[u]->prox;

        while (aux != NULL)
        {
            v = aux->indice;

            if (cor[v] == 'b')
            {
                cor[v] = 'c';
                d[v] = d[u] + 1;
                pi[v] = u;

                fila[end_fila] = v;
                end_fila++;
            }
            aux = aux->prox;
        }
        cor[u] = 'p';
        start_fila++;

        print_loop(d, fila, pi, cor, n);
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

    imprimir(grafo, qnt_nos);

    int pi[qnt_nos], s = 1, v = 4;

    bfs(grafo, qnt_nos, s - 1, pi);
    // printf("Hello worl");
    // print_path(s - 1, v - 1, pi);
}