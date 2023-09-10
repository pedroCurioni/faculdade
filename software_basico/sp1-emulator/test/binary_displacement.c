#include <stdio.h>

int main() {
    char a = 127;

    printf("%u\n", (a >> 9) & 1);
}