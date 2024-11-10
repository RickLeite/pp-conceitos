#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// Número de threads que vamos criar
#define NUM_THREADS 3

// Nossa estrutura de barreira simplificada
typedef struct {
    pthread_mutex_t mutex;    // Para proteger o acesso à variável contador
    pthread_cond_t cond;      // Para sinalizar quando todos chegarem
    int count;                // Conta quantas threads chegaram
    int total;                // Total de threads que precisamos esperar
} Barreira;

// Variável global para nossa barreira
Barreira barreira;

// Função para inicializar a barreira
void inicializar_barreira(Barreira *b, int total) {
    pthread_mutex_init(&b->mutex, NULL);
    pthread_cond_init(&b->cond, NULL);
    b->count = 0;
    b->total = total;
}

// Função que cada thread executa quando chega na barreira
void esperar_na_barreira(Barreira *b) {
    pthread_mutex_lock(&b->mutex);
    
    b->count++;  // Mais uma thread chegou
    
    if (b->count == b->total) {
        // Se for a última thread
        b->count = 0;  // Reseta o contador
        // Acorda todas as threads que estão esperando
        pthread_cond_broadcast(&b->cond);
    } else {
        // Se não for a última, espera
        pthread_cond_wait(&b->cond, &b->mutex);
    }
    
    pthread_mutex_unlock(&b->mutex);
}

// Função que cada thread vai executar
void* trabalho_thread(void* arg) {
    int id = *(int*)arg;
    
    // FASE 1
    printf("Thread %d iniciando fase 1\n", id);
    sleep(id);  // Simula trabalho diferente para cada thread
    printf("Thread %d terminou fase 1\n", id);
    
    // BARREIRA - Espera todas as threads terminarem fase 1
    printf("Thread %d esperando na barreira 1\n", id);
    esperar_na_barreira(&barreira);
    printf("Thread %d passou da barreira 1\n", id);
    
    // FASE 2
    printf("Thread %d iniciando fase 2\n", id);
    sleep(id);  // Simula trabalho diferente para cada thread
    printf("Thread %d terminou fase 2\n", id);
    
    // BARREIRA - Espera todas as threads terminarem fase 2
    printf("Thread %d esperando na barreira 2\n", id);
    esperar_na_barreira(&barreira);
    printf("Thread %d passou da barreira 2\n", id);
    
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    // Inicializa a barreira
    inicializar_barreira(&barreira, NUM_THREADS);
    
    // Cria as threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, trabalho_thread, &thread_ids[i]);
    }
    
    // Espera todas as threads terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Limpa a barreira
    pthread_mutex_destroy(&barreira.mutex);
    pthread_cond_destroy(&barreira.cond);
    
    printf("Programa finalizado!\n");
    return 0;
}