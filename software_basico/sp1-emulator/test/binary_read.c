#include <stdio.h>

struct threeNum {
    int n1, n2, n3;
};

int main(int argc, char *argv[]) {
    FILE *fptr = fopen(argv[1], "rb");
    // Se o arquivo não for encontrato
    if (fptr == NULL) {
        printf("Erro abrindo arquivo\n");
        fclose(fptr);
        return 1;
    }

    struct threeNum num;

    for (int n = 1; n < 5; ++n) {
        fread(&num, sizeof(struct threeNum), 1, fptr);
        switch (num.n2) {
            case 00001111:
                printf("yes\n");
                break;

            default:
                break;
        }
        printf("n1: %08x \tn2: %d\tn3: %d\n", num.n1, num.n2, num.n3);
    }

    // struct threeNum num[4];

    // fread(&num, sizeof(struct threeNum) * 4, 1, fptr);

    // for (int i = 0; i < 4; i++) {
    //     printf("n1: %08x \tn2: %d\tn3: %d\n", num[i].n1, num[i].n2, num[i].n3);
    // }
}