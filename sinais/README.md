# Demonstração de Manipulação de Sinais em C

Este programa demonstra o uso de diferentes sinais em C e como manipulá-los adequadamente. O programa implementa handlers para três tipos diferentes de sinais: SIGINT, SIGTERM e SIGUSR1.

## Execução e Testes

### 1. Teste com SIGINT (Ctrl+C)

```bash
$ ./signals
PID do processo: 5022
Comandos disponíveis:
- Ctrl+C (SIGINT): Pressione 3 vezes para encerrar
- kill -TERM 5022 (SIGTERM): Encerra com limpeza
- kill -USR1 5022 (SIGUSR1): Executa ação personalizada
Processo em execução... (PID: 5022)
```

Pressionando Ctrl+C três vezes:
```bash
^C
Sinal SIGINT recebido (1 vezes)
Pressione Ctrl+C mais 2 vezes para encerrar
^C
Sinal SIGINT recebido (2 vezes)
Pressione Ctrl+C mais 1 vezes para encerrar
^C
Sinal SIGINT recebido (3 vezes)
Recebido SIGINT 3 vezes. Encerrando...
Programa encerrado normalmente.
```

### 2. Teste com SIGTERM

Em um terminal:
```bash
$ ./signals
PID do processo: 5121
Comandos disponíveis:
[...]
Processo em execução... (PID: 5121)
```

Em outro terminal:
```bash
$ kill -TERM 5121
```

Resultado no primeiro terminal:
```bash
Sinal SIGTERM recebido. Realizando limpeza...
Limpeza concluída. Encerrando...
Programa encerrado normalmente.
```

### 3. Teste com SIGUSR1

Em um terminal:
```bash
$ ./signals
PID do processo: 5303
Comandos disponíveis:
[...]
Processo em execução... (PID: 5303)
```

Em outro terminal:
```bash
$ kill -USR1 5303
```

Resultado no primeiro terminal:
```bash
Sinal SIGUSR1 recebido. Executando ação personalizada...
```

Verificando o arquivo de log:
```bash
$ cat signal_log.txt
SIGUSR1 recebido em 1731266930
SIGUSR1 recebido em 1731266936
```

## Características do Programa

1. **Manipulação de SIGINT (Ctrl+C)**:
   - Requer três pressionamentos para encerrar
   - Mostra contador de pressionamentos restantes

2. **Manipulação de SIGTERM**:
   - Realiza procedimento de limpeza antes de encerrar
   - Fornece feedback sobre o processo de limpeza

3. **Manipulação de SIGUSR1**:
   - Executa uma ação personalizada
   - Registra a ocorrência em arquivo de log (signal_log.txt)

4. **Recursos de Segurança**:
   - Uso de `sig_atomic_t` para variáveis compartilhadas
   - Implementação através de `sigaction`
   - Feedback claro sobre estados e ações

## Arquivos Gerados

- `signal_log.txt`: Contém registros de timestamp para cada sinal SIGUSR1 recebido

## Notas

- O programa mantém um loop contínuo até receber o sinal apropriado para encerramento
- SIGINT requer 3 pressionamentos deliberados para evitar encerramentos acidentais
- SIGTERM realiza limpeza controlada antes do encerramento
- SIGUSR1 demonstra como sinais podem ser usados para comunicação entre processos