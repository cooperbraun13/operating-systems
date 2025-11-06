#include "buffer2.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

buffer_item buffer[BUFFER_SIZE];

// global variables for synchronization
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

// circular queue indices
int next_add = 0;
int next_remove = 0;

void print_buffer(){
    for(int i = 0; i < BUFFER_SIZE-1; i++){
        printf("%d, ", buffer[i]);
    }
    printf("%d\n", buffer[BUFFER_SIZE-1]);
}

int insert_item(buffer_item item){
    // wait for an empty slot
    sem_wait(&empty);
    
    // lock the mutex
    pthread_mutex_lock(&mutex);
    
    // insert item into buffer
    buffer[next_add] = item;
    next_add = (next_add + 1) % BUFFER_SIZE;
    
    // unlock the mutex
    pthread_mutex_unlock(&mutex);
    
    // signal that there's a full slot
    sem_post(&full);
    
    return 0;
}

int remove_item(buffer_item *item){
    // wait for a full slot
    sem_wait(&full);
    
    // lock the mutex
    pthread_mutex_lock(&mutex);
    
    // remove item from buffer
    *item = buffer[next_remove];
    next_remove = (next_remove + 1) % BUFFER_SIZE;
    
    // unlock the mutex
    pthread_mutex_unlock(&mutex);
    
    // signal that there's an empty slot
    sem_post(&empty);
    
    return 0;
}

void * producer(void * arg){
    buffer_item item;
    int r;
    while(1){
        r = rand() % 5;
        sleep(r);
        
        item = rand();
        if (insert_item(item)){
            fprintf(stderr, "report error condition, Producer");
        }
        else{
            printf("producer produced %d\n",item); 
        }
    }
}

void * consumer(void * arg){
    buffer_item item;
    int r;
    while(1){
        r = rand() % 5;
        sleep(r);
        
        item = rand();

        if (remove_item(&item)){
            fprintf(stderr, "report error condition, Consumer");
        }
        else{
            printf("consumer consumed %d\n",item);
        }
    }
}


int main(int argc, char *argv[]) {
    int sleep_time = 3, prod = 10, con = 10;
    if (argc != 4){
        printf("USAGE:./a.out <sleep_time> <producer thread count> <consumer thread count>\n");
        return -1;
    }
    sleep_time = atoi(argv[1]);   // argv[1]=sleep seconds
    prod       = atoi(argv[2]);   // argv[2]=# producers
    con        = atoi(argv[3]);   // argv[3]=# consumers

    // initialize mutex
    pthread_mutex_init(&mutex, NULL);
    
    // initialize semaphores
    // empty starts at BUFFER_SIZE (all slots empty)
    // full starts at 0 (no slots full)
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    
    // create producer threads
    pthread_t producers[prod];
    for (int i = 0; i < prod; i++) {
        pthread_create(&producers[i], NULL, producer, NULL);
    }
    
    // create consumer threads
    pthread_t consumers[con];
    for (int i = 0; i < con; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    sleep(sleep_time);

    return 0;
}