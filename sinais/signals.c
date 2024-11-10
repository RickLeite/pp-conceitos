#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

// Variável global para controle do loop principal
volatile sig_atomic_t running = 1;

// Contador de sinais recebidos
volatile sig_atomic_t sigint_count = 0;

// Handler para SIGINT (Ctrl+C)
void handle_sigint(int sig) {
    sigint_count++;
    printf("\nSinal SIGINT recebido (%d vezes)\n", sigint_count);
    
    if (sigint_count >= 3) {
        printf("Recebido SIGINT 3 vezes. Encerrando...\n");
        running = 0;
    } else {
        printf("Pressione Ctrl+C mais %d vezes para encerrar\n", 3 - sigint_count);
    }
}

// Handler para SIGTERM
void handle_sigterm(int sig) {
    printf("\nSinal SIGTERM recebido. Realizando limpeza...\n");
    // Simulação de limpeza de recursos
    sleep(1);
    printf("Limpeza concluída. Encerrando...\n");
    running = 0;
}

// Handler para SIGUSR1
void handle_sigusr1(int sig) {
    printf("\nSinal SIGUSR1 recebido. Executando ação personalizada...\n");
    // Exemplo de ação personalizada
    FILE *fp = fopen("signal_log.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "SIGUSR1 recebido em %ld\n", (long)time(NULL));
        fclose(fp);
    }
}

int main() {
    // Configuração dos handlers de sinais
    struct sigaction sa_int, sa_term, sa_usr1;
    
    // Configurando SIGINT
    memset(&sa_int, 0, sizeof(sa_int));
    sa_int.sa_handler = handle_sigint;
    sigaction(SIGINT, &sa_int, NULL);
    
    // Configurando SIGTERM
    memset(&sa_term, 0, sizeof(sa_term));
    sa_term.sa_handler = handle_sigterm;
    sigaction(SIGTERM, &sa_term, NULL);
    
    // Configurando SIGUSR1
    memset(&sa_usr1, 0, sizeof(sa_usr1));
    sa_usr1.sa_handler = handle_sigusr1;
    sigaction(SIGUSR1, &sa_usr1, NULL);
    
    // Imprime o PID do processo para referência
    printf("PID do processo: %d\n", getpid());
    printf("Comandos disponíveis:\n");
    printf("- Ctrl+C (SIGINT): Pressione 3 vezes para encerrar\n");
    printf("- kill -TERM %d (SIGTERM): Encerra com limpeza\n", getpid());
    printf("- kill -USR1 %d (SIGUSR1): Executa ação personalizada\n", getpid());
    
    // Loop principal
    while (running) {
        printf("Processo em execução... (PID: %d)\n", getpid());
        sleep(2);
    }
    
    printf("Programa encerrado normalmente.\n");
    return 0;
}