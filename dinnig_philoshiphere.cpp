#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

#define N 5

pthread_mutex_t mutex;
sem_t chopstick[N];

// Philosopher Function
void* philosopher(void* num)
{
    int id = *((int*)num);

    // Thinking
    cout << "Philosopher " << id << " is thinking" << endl;
    sleep(1);

    // Pick left chopstick
    sem_wait(&chopstick[id]);

    // Pick right chopstick
    sem_wait(&chopstick[(id + 1) % N]);

    // Eating
    pthread_mutex_lock(&mutex);

    cout << "Philosopher " << id << " is eating" << endl;
    sleep(1);

    pthread_mutex_unlock(&mutex);

    // Release chopsticks
    sem_post(&chopstick[id]);
    sem_post(&chopstick[(id + 1) % N]);

    cout << "Philosopher " << id << " finished eating" << endl;

    return NULL;
}

int main()
{
    pthread_t phil[N];
    int ids[N];

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Initialize semaphores
    for(int i = 0; i < N; i++)
    {
        sem_init(&chopstick[i], 0, 1);
    }

    // Create philosopher threads
    for(int i = 0; i < N; i++)
    {
        ids[i] = i;

        pthread_create(&phil[i], NULL, philosopher, &ids[i]);
    }

    // Join threads
    for(int i = 0; i < N; i++)
    {
        pthread_join(phil[i], NULL);
    }

    // Destroy semaphores
    for(int i = 0; i < N; i++)
    {
        sem_destroy(&chopstick[i]);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}