#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
    char *description;
} Point;

int main(int argc, char const *argv[]) {
    int lenght = 3;

    Point *array;
    array = malloc(sizeof(Point) * lenght);

    array[0].x = 1;
    array[0].y = 1;
    array[0].description = malloc(10);
    strcpy(array[0].description, "point 1");

    array[1].x = 2;
    array[1].y = 2;
    array[1].description = malloc(10);
    strcpy(array[1].description, "point 2");

    array[2].x = 3;
    array[2].y = 3;
    array[2].description = malloc(10);
    strcpy(array[2].description, "point 3");

    for (int i = 0; i < lenght; i++) {
        printf("(%d, %d)", array[i].x, array[i].y);
        printf(" - %s\n", array[i].description);
    }

    lenght = 4;

    array = realloc(array, sizeof(Point) * lenght);

    array[3].x = 4;
    array[3].y = 4;

    for (int i = 0; i < lenght; i++) {
        printf("(%d, %d)\n", array[i].x, array[i].y);
    }

    for (int i = 0; i < lenght; i++) {
        free(array[i].description);
    }

    free(array);

    return 0;
}
