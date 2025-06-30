#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

#define START_SEMAPHORE "/semaphore_start"
#define MEMMORY_SEMAPHORE "/semaphore_memory"
#define MESSAGE_QUEUE_KEY 10
#define MESSAGE_RESPONSE_TYPE 1

struct msg_queue_item
{
    long mtype;
    int mvalue;
};

struct thread_data
{
    int pid;
    int value;
};

void child_process(int process_id, sem_t *start_semaphore, sem_t *memmory_semaphore, int *shared_memory, int msgid);

void wait_post(sem_t *start_semaphore);

void acess_memmory(sem_t *memmory_semaphore, int *shared_memory, int *value);

void *thread_function(void *arg);
void print_thread(int process_id, int value);

void send_msg_end(int msgid);

void start_child(sem_t *start_semaphore, int num_children);

int wait_child(int msgid, int num_children);
