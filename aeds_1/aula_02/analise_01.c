#include <stdio.h>

// As instruções são executadas N/2 vezes
// A complexidade e O(n)
void inverter_vetor(int *vet, int n) {
    int tmp;

    for (int i = 0; i <= n/2; i++)
    {   
        tmp = vet[n - i];
        vet[n - i] = vet[i];
        vet[i] = tmp;
        printf("%d\n", vet[i]);
    }
}

int main() {
    int vet[5] = {1, 2, 3, 4, 5};

    int size = sizeof(vet) / sizeof(int);

    inverter_vetor(vet, size - 1);

    for (int i = 0; i < size; i++)
    {
        printf("%d ", vet[i]);
    }
    
}