#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <fcntl.h>

#define START_SEMAPHORE "/semaphore_start"
#define MEMMORY_SEMAPHORE "/semaphore_memory"
#define MESSAGE_QUEUE_KEY 1234

void clean_semaphores() {
    sem_unlink(MEMMORY_SEMAPHORE);
    sem_unlink(START_SEMAPHORE);
}

void clean_shared_memory() {
    int shmid = shmget(1, sizeof(int), 0666);
    if (shmid != -1) {
        shmctl(shmid, IPC_RMID, NULL);
    }
}

void clean_message_queue() {
    int msgid = msgget(MESSAGE_QUEUE_KEY, 0666);
    if (msgid != -1) {
        msgctl(msgid, IPC_RMID, NULL);
    }
}

int main() {
    clean_semaphores();
    clean_shared_memory();
    clean_message_queue();
    return 0;
}
