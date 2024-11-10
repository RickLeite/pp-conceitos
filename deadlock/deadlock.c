#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t recurso1;
pthread_mutex_t recurso2;

void* thread1(void* arg) {
    printf("Thread 1 tentando obter recurso 1...\n");
    pthread_mutex_lock(&recurso1);
    printf("Thread 1 obteve recurso 1.\n");

    sleep(1); // Simula algum processamento

    printf("Thread 1 tentando obter recurso 2...\n");
    pthread_mutex_lock(&recurso2);
    printf("Thread 1 obteve recurso 2.\n");

    // Libera os recursos
    pthread_mutex_unlock(&recurso2);
    pthread_mutex_unlock(&recurso1);

    printf("Thread 1 liberou ambos os recursos.\n");
    return NULL;
}

void* thread2(void* arg) {
    printf("Thread 2 tentando obter recurso 2...\n");
    pthread_mutex_lock(&recurso2);
    printf("Thread 2 obteve recurso 2.\n");

    sleep(1); // Simula algum processamento

    printf("Thread 2 tentando obter recurso 1...\n");
    pthread_mutex_lock(&recurso1);
    printf("Thread 2 obteve recurso 1.\n");

    // Libera os recursos
    pthread_mutex_unlock(&recurso1);
    pthread_mutex_unlock(&recurso2);

    printf("Thread 2 liberou ambos os recursos.\n");
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Inicializa os mutexes (recursos)
    pthread_mutex_init(&recurso1, NULL);
    pthread_mutex_init(&recurso2, NULL);

    // Cria as threads
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    // Espera ambas as threads terminarem
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroi os mutexes
    pthread_mutex_destroy(&recurso1);
    pthread_mutex_destroy(&recurso2);

    printf("Programa finalizado.\n");
    return 0;
}

