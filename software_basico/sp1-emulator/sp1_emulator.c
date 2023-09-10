#include <stdio.h>

#define LOAD_ADDR 0x00
#define LOAD_NUM 0x01
#define STORE 0x02
#define ADD 0x03
#define SUB 0x04
#define MUL 0x05
#define DIV 0x06
#define INC 0x07
#define DEC 0x08
#define AND 0x09
#define OR 0x0a
#define NOT 0x0b
#define JMP 0x0c
#define JZ 0x0d
#define JNZ 0x0e
#define JG 0x0f
#define JL 0x10
#define JGE 0x11
#define JLE 0x12
#define HLT 0x13

#define MAX_SIZE 255
#define MIN_SIZE 0

typedef struct Instruction {
    char opcode;
    char operand;
} Instruction;

unsigned char stat_handler(int calculation) {
    char stat = 0x00;
    if (calculation == 0) {
        stat = stat ^ 0x01;
    }
    // Carry
    if ((calculation > MAX_SIZE) || (calculation < MIN_SIZE)) {
        stat = stat ^ 0x02;

        if (((calculation >> 7) & 1) == 0) {
            stat = stat ^ 0x04;
        }
    } else if (((calculation >> 7) & 1) == 1) {
        stat = stat ^ 0x04;
    }
    return stat;
}

int main(int argc, char *argv[]) {
    // Instruções do programa, opcode e operação
    Instruction program[256];
    // Memoria do programa
    char memory[256];
    // Program counter
    unsigned char pc = 0, acc = 0, stat, opcode, operand;
    // Calculo do ACC
    int calculation;

    // Se o programa não receber o arquivo, ou receber argumentos demais
    if (argc != 2) {
        printf("Quantidade de parametros invalida\n");
        return 1;
    }

    FILE *fptr = fopen(argv[1], "rb");
    // Se o arquivo não for encontrato
    if (fptr == NULL) {
        printf("Erro abrindo arquivo\n");
        fclose(fptr);
        return 1;
    }

    // Le o arquivo 2 bytes de cada vez e salva na memoria do programa
    fread(&program, sizeof(Instruction) * 256, 1, fptr);
    fclose(fptr);

    while (1) {
        opcode = program[pc].opcode;
        operand = program[pc].operand;
        stat = 0x00;

        pc++;

        switch (opcode) {
            case LOAD_ADDR:
                acc = memory[operand];
                if (acc == 0) {
                    stat = stat ^ 0x01;
                }
                break;
            case LOAD_NUM:
                acc = operand;
                if (acc == 0) {
                    stat = stat ^ 0x01;
                }

                break;
            case STORE:
                memory[operand] = acc;
                break;
            case ADD:
                calculation = acc + memory[operand];
                stat = stat_handler(calculation);
                acc += memory[operand];
                break;
            case SUB:
                calculation = acc - memory[operand];
                stat = stat_handler(calculation);
                acc -= memory[operand];
                break;
            case MUL:
                calculation = acc * memory[operand];
                stat = stat_handler(calculation);
                acc *= memory[operand];
                break;
            case DIV:
                calculation = acc / memory[operand];
                stat = stat_handler(calculation);
                acc /= memory[operand];
                break;
            case INC:
                calculation = acc + 1;
                stat = stat_handler(calculation);
                acc++;
                break;
            case DEC:
                calculation = acc - 1;
                stat = stat_handler(calculation);
                acc--;
                break;
            case AND:
                acc = acc & memory[operand];
                break;
            case OR:
                acc = acc | memory[operand];
                break;
            case NOT:
                acc = ~acc;
                break;
            case JMP:
                pc = operand / 2;
                break;
            case JZ:
                if (acc == 0) {
                    pc = operand / 2;
                }
                break;
            case JNZ:
                if (acc != 0) {
                    pc = operand / 2;
                }
                break;
            case JG:
                if (acc > 0) {
                    pc = operand / 2;
                }
                break;
            case JL:
                if (acc < 0) {
                    pc = operand / 2;
                }
                break;
            case JGE:
                if (acc >= 0) {
                    pc = operand / 2;
                }
                break;
            case JLE:
                if (acc <= 0) {
                    pc = operand / 2;
                }
                break;
            case HLT:
                printf("HLT: Acumulador = %d\n", acc);
                return 0;
            default:
                printf("Ocorreu um erro\n");
                return 1;
        }
    }

    return 0;
}