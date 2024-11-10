#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Banco de dados simulado (apenas um valor inteiro)
int banco_de_dados = 100;

// Mutex para controlar acesso
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int leitores_ativos = 0;

void consultar_dados(int id_leitor) {
    // Início da leitura
    pthread_mutex_lock(&mutex);
    leitores_ativos++;
    printf("Leitor %d iniciando leitura. Leitores ativos: %d\n", id_leitor, leitores_ativos);
    pthread_mutex_unlock(&mutex);
    
    // Simulando leitura do banco
    printf("Leitor %d leu o valor: %d\n", id_leitor, banco_de_dados);
    sleep(1); // Simula processamento
    
    // Fim da leitura
    pthread_mutex_lock(&mutex);
    leitores_ativos--;
    printf("Leitor %d finalizando leitura. Leitores ativos: %d\n", id_leitor, leitores_ativos);
    pthread_mutex_unlock(&mutex);
}

void* leitor(void* arg) {
    int id = *(int*)arg;
    consultar_dados(id);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int ids[3] = {1, 2, 3};
    
    printf("Iniciando programa com 3 leitores\n");
    
    // Criando 3 leitores
    for(int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, leitor, &ids[i]);
    }
    
    // Esperando todos terminarem
    for(int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Programa finalizado\n");
    return 0;
}