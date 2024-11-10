#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Banco de dados simulado (array de inteiros)
int banco_de_dados[5] = {10, 20, 30, 40, 50};

// Mutex para controle de acesso exclusivo
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void iniciar_escrita() {
    pthread_mutex_lock(&mutex);
    printf("Iniciando escrita - Acesso exclusivo garantido\n");
}

void finalizar_escrita() {
    printf("Finalizando escrita - Liberando acesso\n");
    pthread_mutex_unlock(&mutex);
}

void atualizar_dados(int id_escritor, int posicao, int novo_valor) {
    // Registra acesso exclusivo
    iniciar_escrita();
    
    // Mostra valor atual
    printf("Escritor %d: Valor atual na posição %d: %d\n", 
           id_escritor, posicao, banco_de_dados[posicao]);
    
    // Realiza atualização
    banco_de_dados[posicao] = novo_valor;
    printf("Escritor %d: Atualizou posição %d para %d\n", 
           id_escritor, posicao, novo_valor);
    
    // Simula algum processamento
    sleep(2);
    
    // Finaliza acesso exclusivo
    finalizar_escrita();
}

void* escritor(void* arg) {
    int id = *(int*)arg;
    // Cada escritor atualiza uma posição diferente com um valor diferente
    atualizar_dados(id, id % 5, id * 100);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int ids[3] = {1, 2, 3};
    
    printf("Estado inicial do banco: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", banco_de_dados[i]);
    }
    printf("\n");
    
    // Criando 3 escritores
    for(int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, escritor, &ids[i]);
    }
    
    // Esperando todos terminarem
    for(int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Estado final do banco: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", banco_de_dados[i]);
    }
    printf("\n");
    
    printf("Programa finalizado\n");
    return 0;
}