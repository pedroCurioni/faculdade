#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define BUFFER "buffer.txt"
#define LOCK "buffer.txt.lock"

int file_exists(const char *filename);

void consumidor();
void produtor();

int main() {
    // srand(time(NULL));

    if(!file_exists(BUFFER)){
        printf("Erro ao abrir arquivo buffer\n");
        return 0;
    }

    FILE *file = fopen(BUFFER, "a");
    fprintf(file, "\n");
    fclose(file);

    int pid = fork();
    if (pid == 0) {
        srand(time(NULL));;
        consumidor();
    } else {
        srand(time(NULL) ^ (getpid()<<16));;
        produtor();
    }
    return 0;
}

int file_exists(const char *filename)
{
    // F_OK testa a existencia do arquivo
    // Acess retorna 0 zero se o acesso for permitido
    return access(filename, F_OK) == 0;
}

void lock_wait_create() {
    while(file_exists(LOCK)) {
        // Enquanto o arquivo existir espere por 0,2 segundos
        usleep(500 * 1000);
    }
    // Cria o arquivo .lock
    FILE *lock_file = fopen(LOCK, "w");
    fclose(lock_file);
}

int is_empty_file(FILE *fp) {
    int c = getc(fp);
    if (c == EOF)
        return 1;
    ungetc(c, fp);
    return 0;
}

void consumidor() {
    usleep(10000);
    while (1) {
        // Espere um tempo entre 1 e 3 segundos
        sleep((rand() % 3) + 1);

        lock_wait_create();
        
        FILE *file = fopen(BUFFER, "r");

        if (is_empty_file(file))
        {
            remove(LOCK);
            continue;
        }

        int data[1000];
        int i=0;
        int num;

        // Le os numeros do arquivo
        while(fscanf(file, "%d", &num) == 1) {
            data[i] = num;
            i++;
        }
        fclose(file);

        printf("Consumidor: %d\n", data[0]);

        file = fopen(BUFFER, "w");
        for(int j = 1; j < i; j++){
            fprintf(file, "%d\n", data[j]);
        }
        
        fclose(file);
        remove(LOCK);
    }
}

void produtor() {
    while (1) {
        // Espere um tempo entre 1 e 3 segundos
        sleep((rand() % 3) + 1);

        lock_wait_create();

        FILE *file = fopen(BUFFER, "a");
        
        // Escreva no final do arquivo um numero aleatorio entre 0 e 99
        int num = rand() % 100;
        fprintf(file, "%d\n", num);
        printf("Produtor: %d\n", num);

        fclose(file);
        remove(LOCK);

    }
    
}