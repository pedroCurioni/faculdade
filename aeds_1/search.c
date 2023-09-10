#include <stdio.h>
#include <stdlib.h>

int sequencial_search(int *v, int n, int chave)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        if (v[i] == chave)
        {
            return i;
        }
    }
    return -1;
}

int binary_search(int *arr, int inf, int sup, int value)
{
    int m = (inf + sup) / 2;
    if (inf > sup)
    {
        return -1;
    }
    else if (arr[m] == value)
    {
        return m;
    }
    else if (arr[m] <= value)
    {
        return binary_search(arr, (inf + m + 1), sup, value);
    }
    else
    {
        return binary_search(arr, inf, (sup - m - 1), value);
    }
}

int main()
{
    int arr[10] = {1, 1, 2, 3, 5, 7, 10, 22, 34, 54};

    printf("%d\n", sequencial_search(arr, 9, 22));
    printf("%d\n", binary_search(arr, 0, 9, 22));
}
