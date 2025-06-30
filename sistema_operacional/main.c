#include "main.h"

int main()
{
    sem_t *start_semaphore = sem_open(START_SEMAPHORE, O_CREAT | O_EXCL, 0666, 0);
    if (start_semaphore == SEM_FAILED)
    {
        perror("Ocorreu um erro ao criar o semáforo de inicio\n");
        return 1;
    }

    sem_t *memmory_semaphore = sem_open(MEMMORY_SEMAPHORE, O_CREAT | O_EXCL, 0666, 1);
    if (memmory_semaphore == SEM_FAILED)
    {
        perror("Ocorreu um erro ao criar o semáforo de memoria\n");
        return 1;
    }

    int msgid = msgget(MESSAGE_QUEUE_KEY, IPC_CREAT | 0666);
    if (msgid == -1)
    {
        printf("Erro ao criar fila de mensagens");
        return 1;
    }

    int shmid = shmget(1, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1)
    {
        printf("Ocorreu um erro ao criar a memória compartilhada\n");
        return 1;
    }

    int *shared_memory = (int *)shmat(shmid, NULL, 0);
    if (shared_memory == (int *)-1)
    {
        perror("Erro ao conectar memória compartilhada");
        return 1;
    }

    *shared_memory = 1;

    // execução dos 4 processos filhos
    for (int i = 0; i < 4; i++)
    {
        int pid = fork();

        if (pid < 0)
        {
            printf("Ocorreu um erro ao criar o processo filho\n");
            return 1;
        }
        else if (pid == 0)
        {
            int process_id = getpid();
            child_process(process_id, start_semaphore, memmory_semaphore, shared_memory, msgid);
            exit(0);
        }
    }

    sleep(2);

    start_child(start_semaphore, 4);

    int result = wait_child(msgid, 4);
    if (result != 0)
    {
        return 1;
    }

    printf("Processo pai de PID %d informa que todos os filhos foram finalizados e o valor atual da memória compartilhada é %d\n", getpid(), *shared_memory);

    sem_close(memmory_semaphore);
    sem_unlink(MEMMORY_SEMAPHORE);

    sem_close(start_semaphore);
    sem_unlink(START_SEMAPHORE);

    shmctl(shmid, IPC_RMID, NULL);

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}

void start_child(sem_t *start_semaphore, int num_children)
{
    for (int i = 0; i < num_children; i++)
    {
        sem_post(start_semaphore);
    }
}

int wait_child(int msgid, int num_children)
{
    int process_responses = 0, recieved = 0;
    struct msg_queue_item msg;

    while (process_responses < num_children)
    {
        recieved = msgrcv(msgid, &msg, sizeof(int), MESSAGE_RESPONSE_TYPE, 0);
        if (recieved == -1)
        {
            printf("Ocorreu um erro ao receber mensagem da fila\n");
            return 1;
        }
        process_responses++;
    }

    return 0;
}

void wait_post(sem_t *start_semaphore)
{
    sem_wait(start_semaphore);

    int delay = 200 + rand() % 801; // entre 200 e 1000
    usleep(delay * 1000);
}

void acess_memmory(sem_t *memmory_semaphore, int *shared_memory, int *value)
{
    // espera o semaforo da memoria compartilhada
    sem_wait(memmory_semaphore);

    *value = *shared_memory;
    (*shared_memory)--;
    int delay = 500 + rand() % 501; // entre 500 e 1000
    usleep(delay * 1000);

    sem_post(memmory_semaphore);
}

void *thread_function(void *arg)
{
    struct thread_data *data = (struct thread_data *)arg;
    printf("Processo de PID %d copiou o valor %d\n", data->pid, data->value);
    return NULL;
}

void print_thread(int process_id, int value)
{
    // criar uma thread para imprimir o valor
    struct thread_data data;
    data.pid = process_id;
    data.value = value;

    pthread_t thread_id;
    int result = pthread_create(&thread_id, NULL, thread_function, (void *)&data);
    if (result != 0)
    {
        perror("Erro ao criar thread");
        return;
    }
    pthread_join(thread_id, NULL);

    printf("Processo filho de PID %d foi finalizado\n", getpid());
}

void send_msg_end(int msgid)
{
    // envia msg para a fila de mensagens
    struct msg_queue_item msg;
    msg.mtype = MESSAGE_RESPONSE_TYPE;
    msg.mvalue = 1;
    if (msgsnd(msgid, &msg, sizeof(int), 0) == -1)
    {
        perror("Erro ao enviar mensagem para a fila");
    }
}

void child_process(int process_id, sem_t *start_semaphore, sem_t *memmory_semaphore, int *shared_memory, int msgid)
{
    srand((time(NULL) ^ process_id));

    wait_post(start_semaphore);

    int value;
    acess_memmory(memmory_semaphore, shared_memory, &value);

    print_thread(process_id, value);

    send_msg_end(msgid);
}
