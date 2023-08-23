#include <stdio.h>
#include <stdlib.h>

// A quantidade da instrução mais executada e n^2
// A complexidade e O(n^2)
void soma_mat_1riz(int n, int mat_1[][n], int mat_2[][n]) {
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {   
            printf("%d %d\n", mat_1[i][j], mat_2[i][j]);
            mat_1[i][j] += mat_2[i][j];
        }  
    }
    
}

int main() {
    int mat_1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int mat_2[3][3] = {{7, 8, 9}, {4, 5, 6},{1, 2, 3}};

    soma_mat_1riz(3, mat_1, mat_2);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", mat_1[i][j]);
        }
        printf("\n");
        
    }
    
}