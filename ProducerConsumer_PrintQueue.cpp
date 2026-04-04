#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

#define MAX 100

int buffer[MAX];
int in = 0, out = 0;
int n;

sem_t empty_sem, full, mutex;

// Producer = User sending print job
void* producer(void* arg) {
    int id = *((int*)arg);

    for (int i = 0; i < 5; i++) {
        int document = rand() % 1000;

        sem_wait(&empty_sem);
        sem_wait(&mutex);

        buffer[in] = document;
        cout << "User " << id << " sent print job: Doc#" << document 
             << " to slot " << in << endl;

        in = (in + 1) % n;

        sem_post(&mutex);
        sem_post(&full);

        sleep(1);
    }
    pthread_exit(NULL);
}

// Consumer = Printer
void* consumer(void* arg) {
    int id = *((int*)arg);

    for (int i = 0; i < 5; i++) {
        sem_wait(&full);
        sem_wait(&mutex);

        int document = buffer[out];
        cout << "Printer " << id << " is printing Doc#" << document 
             << " from slot " << out << endl;

        out = (out + 1) % n;

        sem_post(&mutex);
        sem_post(&empty_sem);

        sleep(2);
    }
    pthread_exit(NULL);
}

int main() {
    int p, c;

    cout << "Enter buffer size (print queue size): ";
    cin >> n;

    cout << "Enter number of users (producers): ";
    cin >> p;

    cout << "Enter number of printers (consumers): ";
    cin >> c;

    pthread_t prod[p], cons[c];
    int pid[p], cid[c];

    sem_init(&empty_sem, 0, n);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < p; i++) {
        pid[i] = i + 1;
        pthread_create(&prod[i], NULL, producer, &pid[i]);
    }

    for (int i = 0; i < c; i++) {
        cid[i] = i + 1;
        pthread_create(&cons[i], NULL, consumer, &cid[i]);
    }

    for (int i = 0; i < p; i++)
        pthread_join(prod[i], NULL);

    for (int i = 0; i < c; i++)
        pthread_join(cons[i], NULL);

    sem_destroy(&empty_sem);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

#define MAX 100

int buffer[MAX];
int in = 0, out = 0;
int n;

sem_t empty_sem, full, mutex;

// Producer = User sending print job
void* producer(void* arg) {
    int id = *((int*)arg);

    for (int i = 0; i < 5; i++) {
        int document = rand() % 1000;

        sem_wait(&empty_sem);
        sem_wait(&mutex);

        buffer[in] = document;
        cout << "User " << id << " sent print job: Doc#" << document 
             << " to slot " << in << endl;

        in = (in + 1) % n;

        sem_post(&mutex);
        sem_post(&full);

        sleep(1);
    }
    pthread_exit(NULL);
}

// Consumer = Printer
void* consumer(void* arg) {
    int id = *((int*)arg);

    for (int i = 0; i < 5; i++) {
        sem_wait(&full);
        sem_wait(&mutex);

        int document = buffer[out];
        cout << "Printer " << id << " is printing Doc#" << document 
             << " from slot " << out << endl;

        out = (out + 1) % n;

        sem_post(&mutex);
        sem_post(&empty_sem);

        sleep(2);
    }
    pthread_exit(NULL);
}

int main() {
    int p, c;

    cout << "Enter buffer size (print queue size): ";
    cin >> n;

    cout << "Enter number of users (producers): ";
    cin >> p;

    cout << "Enter number of printers (consumers): ";
    cin >> c;

    pthread_t prod[p], cons[c];
    int pid[p], cid[c];

    sem_init(&empty_sem, 0, n);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < p; i++) {
        pid[i] = i + 1;
        pthread_create(&prod[i], NULL, producer, &pid[i]);
    }

    for (int i = 0; i < c; i++) {
        cid[i] = i + 1;
        pthread_create(&cons[i], NULL, consumer, &cid[i]);
    }

    for (int i = 0; i < p; i++)
        pthread_join(prod[i], NULL);

    for (int i = 0; i < c; i++)
        pthread_join(cons[i], NULL);

    sem_destroy(&empty_sem);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
