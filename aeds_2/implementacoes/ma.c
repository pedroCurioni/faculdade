#include <stdio.h>

void imprimir(int n, int grafo[][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", grafo[i][j]);
        }
        printf("\n");
    }
}

int grau_saida(int n, int grafo[][n], int v)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (grafo[v][i] > 0)
        {
            count++;
        }
    }
    return count;
}

int grau_entrada(int n, int grafo[][n], int v)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (grafo[i][v] > 0)
        {
            count++;
        }
    }
    return count;
}

void grau_total_saida(int n, int grafo[][n])
{
    for (int i = 0; i < n; i++)
    {
        printf("GRAU SAIDA %d: %d\n", i + 1, grau_saida(n, grafo, i));
    }
}

void grau_total_entrada(int n, int grafo[][n])
{
    for (int i = 0; i < n; i++)
    {
        printf("GRAU ENTRADA %d: %d\n", i + 1, grau_entrada(n, grafo, i));
    }
}

int grau_maximo_entrada(int n, int grafo[][n])
{
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        int tmp_grau = grau_entrada(n, grafo, i);
        if (tmp_grau > max)
        {
            max = tmp_grau;
        }
    }
    return max;
}
int grau_maximo_saida(int n, int grafo[][n])
{
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        int tmp_grau = grau_saida(n, grafo, i);
        if (tmp_grau > max)
        {
            max = tmp_grau;
        }
    }
    return max;
}

int grau_minimo_saida(int n, int grafo[][n])
{
    int min = grau_saida(n, grafo, 0);
    for (int i = 1; i < n; i++)
    {
        int tmp_grau = grau_saida(n, grafo, i);
        if (tmp_grau < min)
        {
            min = tmp_grau;
        }
    }
    return min;
}
int grau_minimo_entrada(int n, int grafo[][n])
{
    int min = grau_entrada(n, grafo, 0);
    for (int i = 1; i < n; i++)
    {
        int tmp_grau = grau_entrada(n, grafo, i);
        if (tmp_grau < min)
        {
            min = tmp_grau;
        }
    }
    return min;
}

void paralelo(int n, int grafo[][n])
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grafo[i][j] > 1 && i != j)
            {
                count++;
                printf("PARALELO: %d\n", i + 1);
            }
        }
    }
    printf("QNT PARALELO: %d\n", count);
}

void loop(int n, int grafo[][n])
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (grafo[i][i] > 0)
        {
            count++;
            printf("LOOP: %d\n", i + 1);
        }
    }
    printf("QNT LOOP: %d\n", count);
}

void isolado(int n, int grafo[][n])
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (grau_saida(n, grafo, i) == 0 && grau_entrada(n, grafo, i) == 0)
        {
            count++;
            printf("ISOLADO: %d\n", i + 1);
        }
    }
    printf("QNT ISOLADO: %d\n", count);
}

void regular(int n, int grafo[][n])
{
    if (grau_maximo_entrada(n, grafo) == grau_maximo_saida(n, grafo) && grau_minimo_entrada(n, grafo) == grau_minimo_saida(n, grafo) && grau_maximo_entrada(n, grafo) == grau_minimo_saida(n, grafo))
    {
        printf("É REGULAR\n");
    }
    else
    {
        printf("NÃO É REGULAR\n");
    }
}

void completo(int n, int grafo[][n])
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grafo[i][j] == 1)
            {
                count++;
            }
        }
    }
    if (count == (n * n - n))
    {
        printf("GRAFO COMPLETO\n");
    }
    else
    {
        printf("GRAFO NÃO E COMPLETO\n");
    }
}

void main()
{
    FILE *file;
    int n, a, o, t1, t2, count = 0;
    char line[10];
    file = fopen("G4.txt", "r");

    fscanf(file, "%d %d %d", &n, &a, &o);

    int grafo[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            grafo[i][j] = 0;
        }
    }

    while (fgets(line, sizeof(line), file))
    {
        if (count == 0)
        {
            count++;
            continue;
        }
        sscanf(line, "%d %d", &t1, &t2);
        grafo[t1 - 1][t2 - 1]++;
        if (o != 1)
        {
            grafo[t2 - 1][t1 - 1]++;
        }
    }
    fclose(file);

    if (o == 0)
    {
        printf("------------------\n");
        grau_total_entrada(n, grafo);
        printf("------------------\n");
        printf("GRAU MINIMO: %d\n", grau_minimo_entrada(n, grafo));
        printf("------------------\n");
        printf("GRAU MAXIMO: %d\n", grau_maximo_entrada(n, grafo));
        printf("------------------\n");
    }
    else
    {
        printf("------------------\n");
        grau_total_entrada(n, grafo);
        printf("------------------\n");
        printf("GRAU MINIMO SAIDA: %d\n", grau_minimo_saida(n, grafo));
        printf("------------------\n");
        printf("GRAU MINIMO ENTRADA: %d\n", grau_minimo_entrada(n, grafo));
        printf("------------------\n");
        printf("GRAU MAXIMO SAIDA: %d\n", grau_maximo_saida(n, grafo));
        printf("------------------\n");
        printf("GRAU MAXIMO ENTRADA: %d\n", grau_minimo_entrada(n, grafo));
        printf("------------------\n");
    }

    loop(n, grafo);
    printf("------------------\n");
    paralelo(n, grafo);
    printf("------------------\n");
    isolado(n, grafo);
    printf("------------------\n");
    regular(n, grafo);
    printf("------------------\n");
    completo(n, grafo);
    printf("------------------\n");
    imprimir(n, grafo);
}