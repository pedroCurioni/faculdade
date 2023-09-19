#include <stdio.h>
#include <stdlib.h>

void troca(int *v, int i, int j) {
    int t = v[i];
    v[i] = v[j];
    v[j] = t;
}

void selecao(int *v, int n) {
    for (int i = 0; i < (n - 1); i++) {
        int m = i;

        for (int j = (i + 1); j < n; j++) {
            if (v[j] < v[m]) {
                m = j;
            }
        }

        troca(v, i, m);
    }
}

void insercao(int *v, int n) {
    for (int i = 1; i < n; i++) {
        int j = i, t = v[i];
        while (j > 0 && v[j - 1] > t) {
            v[j] = v[j - 1];
            j--;
        }
        v[j] = t;
    }
}

void merge(int *v, int e, int m, int d) {
    // e1 = e; d1 = m; e2 = m + 1; d2 = d
    int i = e, j = (m + 1), k = 0;
    int vAux[d - e + 1];

    while (i <= m && j <= d) {
        if (v[i] <= v[j]) {
            vAux[k] = v[i];
            i++;
        } else {
            vAux[k] = v[j];
            j++;
        }
        k++;
    }

    while (i <= m) {
        vAux[k] = v[i];
        k++;
        i++;
    }
    while (j <= d) {
        vAux[k] = v[j];
        k++;
        j++;
    }

    for (i = 0; i < k; i++) {
        v[i + e] = vAux[i];
    }
}

void mergeSort(int *v, int e, int d) {
    if (e < d) {
        int m = (e + d) / 2;
        mergeSort(v, e, m);
        mergeSort(v, m + 1, d);
        merge(v, e, m, d);
    }
}

int particao(int *v, int e, int d) {
    int i = e, j = d;
    int pivo = v[(e + d) / 2];

    while (i <= j) {
        while (v[i] < pivo) {
            i++;
        }
        while (v[j] > pivo) {
            j--;
        }

        if (i < j) {
            troca(v, i, j);
            i++;
            j--;
        } else {
            break;
        }
    }
    return j;
}

void quickSort(int *v, int e, int d) {
    if (e < d) {
        int pivo = particao(v, e, d);
        quickSort(v, e, pivo);
        quickSort(v, pivo + 1, d);
    }
}

void shellSort(int *v, int n) {
    int p = n / 2;
    while (p > 0) {
        for (int i = p; i < n; i++) {
            int aux = v[i];
            int j = i;

            while (j >= p && v[j - p] > aux) {
                v[j] = v[j - p];
                j -= p;
            }
            v[j] = aux;
        }
        p = p / 2;
    }
}

void sobeHeap(int *v, int n) {
    for (int i = 0; i < n; i++) {
        int f;
    }
}

int main(int argc, char const *argv[]) {
    int a;
    
    int v[10] = {17, 2, 9, 4, 6, 1, 8, 3, 10, 5};
    int s = sizeof(v) / sizeof(int);

    for (int i = 0; i < s; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    // selecao(v, s);
    // insercao(v, s);
    // mergeSort(v, 0, s - 1);
    // quickSort(v, 0, s - 1);
    // shellSort(v, s);

    for (int i = 0; i < s; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    return 0;
}
