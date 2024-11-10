#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>

// Semáforos POSIX
sem_t mutex;        // Controla acesso ao contador de leitores
sem_t rw_mutex;     // Controla acesso à base de dados
int read_count = 0; // Número de leitores ativos

// Base de dados simulada
int database = 0;

// Flag para controle de parada
volatile int should_stop = 0;

void read_database() {
    printf("Leitor %lu está lendo valor %d\n", pthread_self(), database);
    sleep(1);
}

void use_data_read() {
    printf("Leitor %lu está processando os dados\n", pthread_self());
    sleep(1);
}

void think_up_data() {
    printf("Escritor %lu está preparando dados\n", pthread_self());
    sleep(1);
}

void write_database() {
    if (database < 5) {  // Só incrementa se ainda não chegou a 5
        database++;
        printf("Escritor %lu atualizou valor para %d\n", pthread_self(), database);
        if (database >= 5) {
            should_stop = 1;  // Sinaliza que devemos parar
        }
    }
    sleep(2);
}

void* reader(void* arg) {
    int id = *(int*)arg;
    
    while (!should_stop) {
        printf("\nLeitor %d tentando ler\n", id);
        
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1)
            sem_wait(&rw_mutex);
        sem_post(&mutex);
        
        read_database();
        
        sem_wait(&mutex);
        read_count--;
        if (read_count == 0)
            sem_post(&rw_mutex);
        sem_post(&mutex);
        
        use_data_read();
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    
    while (!should_stop) {
        printf("\nEscritor %d tentando escrever\n", id);
        
        think_up_data();
        
        sem_wait(&rw_mutex);
        write_database();
        sem_post(&rw_mutex);
    }
    return NULL;
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);
    
    #define NUM_LEITORES 3
    #define NUM_ESCRITORES 2
    
    pthread_t leitores[NUM_LEITORES];
    pthread_t escritores[NUM_ESCRITORES];
    int ids_leitores[NUM_LEITORES];
    int ids_escritores[NUM_ESCRITORES];
    
    printf("Iniciando simulação\n");
    
    for (int i = 0; i < NUM_LEITORES; i++) {
        ids_leitores[i] = i + 1;
        pthread_create(&leitores[i], NULL, reader, &ids_leitores[i]);
    }
    
    for (int i = 0; i < NUM_ESCRITORES; i++) {
        ids_escritores[i] = i + 1;
        pthread_create(&escritores[i], NULL, writer, &ids_escritores[i]);
    }
    
    for (int i = 0; i < NUM_LEITORES; i++) {
        pthread_join(leitores[i], NULL);
    }
    
    for (int i = 0; i < NUM_ESCRITORES; i++) {
        pthread_join(escritores[i], NULL);
    }
    
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);
    
    printf("\nSimulação finalizada! Valor final: %d\n", database);
    return 0;
}