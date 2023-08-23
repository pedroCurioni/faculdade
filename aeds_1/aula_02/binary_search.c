#include <stdio.h>
#include <stdlib.h>

int binary_search(int *arr, int inf, int sup, int value) {
    int m = (inf + sup) / 2;

    if (inf > sup) {
        return -1;
    } else if (arr[m] == value) {
        return m;
    } else if (arr[m] <= value) {
        return binary_search(arr, (inf - m + 1), sup, value);
    } else if (arr[m] >= m) {
        return binary_search(arr, inf, (sup - m - 1), value);
    }
    ;
    
}

int main() {
    int arr[10] = {1,1,2,3,5,7,10,22,34,54};

    printf("%d\n", binary_search(arr, 0, 9, 22));
}