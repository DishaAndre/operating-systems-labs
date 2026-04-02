#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

#define MAX 100

int buffer[MAX];
int in = 0, out = 0;
int n; // buffer size

sem_t empty_sem, full, mutex;

// Producer function
void* producer(void* arg) {
    int id = *((int*)arg);

    for (int i = 0; i < 5; i++) {  // produce 5 items
        int item = rand() % 100;

        sem_wait(&empty_sem);
        sem_wait(&mutex);

        buffer[in] = item;
        cout << "Producer " << id << " produced: " << item << " at " << in << endl;
        in = (in + 1) % n;

        sem_post(&mutex);
        sem_post(&full);

        sleep(1);
    }
    pthread_exit(NULL);
}

// Consumer function
void* consumer(void* arg) {
    int id = *((int*)arg);

    for (int i = 0; i < 5; i++) {  // consume 5 items
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out];
        cout << "Consumer " << id << " consumed: " << item << " from " << out << endl;
        out = (out + 1) % n;

        sem_post(&mutex);
        sem_post(&empty_sem);

        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    int p, c;

    cout << "Enter buffer size: ";
    cin >> n;

    cout << "Enter number of producers: ";
    cin >> p;

    cout << "Enter number of consumers: ";
    cin >> c;

    pthread_t prod[p], cons[c];
    int pid[p], cid[c];

    // Initialize semaphores
    sem_init(&empty_sem, 0, n);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // Create producer threads
    for (int i = 0; i < p; i++) {
        pid[i] = i + 1;
        pthread_create(&prod[i], NULL, producer, &pid[i]);
    }

    // Create consumer threads
    for (int i = 0; i < c; i++) {
        cid[i] = i + 1;
        pthread_create(&cons[i], NULL, consumer, &cid[i]);
    }

    // Join threads
    for (int i = 0; i < p; i++)
        pthread_join(prod[i], NULL);

    for (int i = 0; i < c; i++)
        pthread_join(cons[i], NULL);

    // Destroy semaphores
    sem_destroy(&empty_sem);
    sem_destroy(&full);
    sem_destroy(&mutex);
	
    return 0;
}
