#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

sem_t wrt;// write
pthread_mutex_t mutex; // readcount
int rc=0;// read count;


void* reader(void* arg){
int id =*((int*)arg);
pthread_mutex_lock(&mutex);
rc++;
if(rc==1){
    sem_wait(&wrt);
}
pthread_mutex_unlock(&mutex);
// critical section
cout<<"reader is reading "<<id<<endl;
sleep(1);

pthread_mutex_lock(&mutex);
rc--;
if(rc==0){
    sem_post(&wrt);

}

pthread_mutex_unlock(&mutex);

return NULL;




}

void* writer(void* arg){
    int id =*((int*)arg);

  sem_wait(&wrt);
  cout<<"writer is writing "<<id<<endl;
  sleep(1);

  sem_post(&wrt);
  return NULL;
}

int main()
{
    pthread_t r[3], w[2];

    int reader_ids[3] = {1, 2, 3};
    int writer_ids[2] = {1, 2};

    // Initialize mutex and semaphore
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    // Create reader threads
    for(int i = 0; i < 3; i++)
    {
        pthread_create(&r[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for(int i = 0; i < 2; i++)
    {
        pthread_create(&w[i], NULL, writer, &writer_ids[i]);
    }

    // Join reader threads
    for(int i = 0; i < 3; i++)
    {
        pthread_join(r[i], NULL);
    }

    // Join writer threads
    for(int i = 0; i < 2; i++)
    {
        pthread_join(w[i], NULL);
    }

    // Destroy mutex and semaphore
    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}