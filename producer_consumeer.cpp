#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in=0;
int out=0;
sem_t full,empty;
pthread_mutex_t mutex;
void* producer(void* arg){
    int item;
    for(int i=1;i<=5;i++){
        item=i;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in]=item;
        cout<<"producer produced item "<<item<<endl;
        in=(in+1)%BUFFER_SIZE;
         pthread_mutex_unlock(&mutex);
         sem_post(&full);
         sleep(1);
        return NULL;

    }
}


void* consumer(void* arg){
    int item;
    for(int i=1;i<=5;i++){
        
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item=buffer[out];
        cout<<"consumer consumed item "<<item<<endl;
        out=(out+1)%BUFFER_SIZE;
         pthread_mutex_unlock(&mutex);
         sem_post(&empty);
         sleep(1);
        return NULL;

    }
}

int main()
{
    pthread_t p, c;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    // Wait for threads
    pthread_join(p, NULL);
    pthread_join(c, NULL);

    // Destroy mutex & semaphores
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}