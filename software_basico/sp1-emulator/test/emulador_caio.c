#include <stdio.h>
typedef signed char byte;
typedef struct {
    byte opcode;
    byte operand;

} inst;

int main(int argc, char **argv) {
    int pc = 0;
    byte stat = 0b00000000;

    if (argc != 2) {
        printf("%s <file name>\n", argv[0]);
        return 1;
    }
    inst programa[256];
    int acc = 0;
    signed char memoria[256];
    FILE *filein = fopen(argv[1], "rb");
    unsigned short buf;
    int i = 0;

    while (fread(&buf, 2, 1, filein) != 0) {
        programa[i].opcode = buf & 0xFF;
        programa[i].operand = (buf >> 8) & 0xFF;
        i++;
    }
    fclose(filein);
    int original = 0;
    while (programa[pc].opcode != 0b00010011) {
        switch (programa[pc].opcode) {
            case 0b00000000:
                // load memória
                acc = memoria[programa[pc].operand];
                pc++;
                if (acc == 0) {
                    // deu 0
                    stat = 0b00000011;
                } else {
                    stat = 0b00000000;
                }
                break;

            case 0b00000001:
                // load valor
                acc = programa[pc].operand;
                if ((acc & 0x100) != 0) {
                    // overflow
                    stat = 0b00000001;
                } else if (acc == 0) {
                    // deu 0
                    printf("Entrei aq\n");
                    stat = 0b00000011;
                } else {
                    stat = 0b00000000;
                }
                pc++;
                break;

            case 0b00000010:
                // store
                memoria[programa[pc].operand] = acc;
                // printf("Oq tem na memória é': %d \n" , memoria[programa[pc].operand]);
                pc++;
                break;

            case 0b00000011:
                // add
                printf("Entrei \n");
                acc += memoria[programa[pc].operand];
                original = acc - memoria[programa[pc].operand];
                if (((original)&0x80) != (memoria[programa[pc].operand] & 0x80) && (original & 0x80) != (acc & 0x80)) {
                    // overflow
                    stat = 0b00000001;
                } else if ((acc & 0x100) != 0) {
                    // carry
                    stat = 0b00000010;
                } else if (acc == 0) {
                    // deu 0
                    stat = 0b00000011;
                } else {
                    printf("Entrei aq ");
                    stat = 0b00000000;
                }
                pc++;
                break;

            case 0b00000100:
                // sub
                acc = acc - memoria[programa[pc].operand];
                original = acc + memoria[programa[pc].operand];
                int original = acc + memoria[programa[pc].operand];
                unsigned char res = 0;
                res = acc;
                if (((original)&0x80) != (memoria[programa[pc].operand] & 0x80) && (original & 0x80) != (res & 0x80)) {
                    // overflow
                    stat = 0b00000001;
                } else if ((acc & 0x100) != 0) {
                    // carry
                    stat = 0b00000010;
                } else if (acc == 0) {
                    // deu 0
                    stat = 0b00000011;
                } else {
                    stat = 0b00000000;
                }
                pc++;
                break;

            case 0b00000101:
                // mul
                acc *= memoria[programa[pc].operand];
                original = acc / memoria[programa[pc].operand];
                pc++;
                if (((original)&0x80) != (memoria[programa[pc].operand] & 0x80) && (original & 0x80) != (acc & 0x80)) {
                    // overflow
                    stat = 0b00000001;
                } else if ((acc & 0x100) != 0) {
                    // carry
                    stat = 0b00000010;
                } else if (acc == 0) {
                    // deu 0
                    stat = 0b00000011;
                } else {
                    stat = 0b00000000;
                }
                break;

            case 0b00000110:
                // div
                if (programa[pc].operand != 0) {
                    acc /= programa[pc].operand;
                } else {
                    // stat = 1; // divisão por zero
                }
                pc++;
                break;
            case 0b00000111:
                // inc
                acc++;
                if ((acc & 0x100) != 0) {
                    // carry
                    stat = 0b00000010;
                } else if (acc == 0) {
                    // deu 0
                    stat = 0b00000011;
                } else {
                    stat = 0b00000000;
                }
                pc++;
                break;

            case 0b00001000:
                // dec
                acc--;
                if ((acc & 0x100) != 0) {
                    // carry
                    stat = 0b00000010;
                } else if (acc == 0) {
                    // deu 0
                    stat = 0b00000011;
                } else {
                    stat = 0b00000000;
                }
                pc++;
                break;

            case 0b00001001:
                // and
                acc &= memoria[programa[pc].operand];
                if (acc == 0) {
                    stat = 0b00000011;
                }
                pc++;
                break;

            case 0b00001010:
                // or
                acc |= memoria[programa[pc].operand];
                if (acc == 0) {
                    stat = 0b00000011;
                }
                pc++;
                break;

            case 0b00001011:
                // not
                acc = ~acc;
                if (acc == 0) {
                    stat = 0b00000011;
                }
                pc++;
                break;

            case 0b00001100:
                // jump
                pc = programa[pc].operand / 2;
                continue;
                break;

            case 0b00001101:
                // jz
                if (acc == 0) {
                    // printf("%d\n");
                    pc = programa[pc].operand / 2;
                    continue;
                } else {
                    pc++;
                }
                break;

            case 0b00001110:
                // jnz
                if (acc != 0) {
                    pc = programa[pc].operand / 2;
                    continue;
                } else {
                    pc++;
                }
                break;

            case 0b00001111:
                // jg
                if (acc > 0) {
                    pc = programa[pc].operand / 2;
                    continue;
                } else {
                    pc++;
                }
                break;

            case 0b00010000:
                // jl
                if (acc < 0) {
                    pc = programa[pc].operand / 2;
                    printf("Entrei \n");
                    continue;
                } else {
                    pc++;
                }
                break;

            case 0b00010001:
                // jge
                if (acc >= 0) {
                    pc = programa[pc].operand / 2;
                    printf("Entrei !\n");
                    continue;
                } else {
                    pc++;
                }
                break;

            case 0b00010010:
                // jle
                if (acc <= 0) {
                    pc = programa[pc].operand / 2;
                    continue;
                } else {
                    pc++;
                }
                break;
            default:
                // stat = 2; // opcode inválido
                pc++;
                break;
        }
        // printf("Na posição %d o acc é : %d \n",pc,acc);
    }
    printf("%d\n O valor do stat é : %d \n ", acc, stat);
    return 0;
}