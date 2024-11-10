# Simulação de Deadlock em C

Este programa demonstra uma situação clássica de deadlock usando threads e mutexes em C. O deadlock ocorre quando duas threads tentam adquirir os mesmos recursos em ordem diferente, criando uma situação de espera circular.

## Exemplo de Saída

```
Thread 2 tentando obter recurso 2...
Thread 2 obteve recurso 2.
Thread 1 tentando obter recurso 1...
Thread 1 obteve recurso 1.
Thread 2 tentando obter recurso 1...
Thread 1 tentando obter recurso 2...
```

O programa trava neste ponto, demonstrando o deadlock.

## Explicação do Código

### Estruturas Principais

```c
pthread_mutex_t recurso1;
pthread_mutex_t recurso2;
```

- Dois mutexes são usados para simular recursos compartilhados
- Cada thread precisa adquirir ambos os recursos para completar sua execução

### Comportamento das Threads

#### Thread 1
1. Tenta obter recurso1
2. Obtém recurso1
3. Espera 1 segundo
4. Tenta obter recurso2 (pode resultar em deadlock)

#### Thread 2
1. Tenta obter recurso2
2. Obtém recurso2
3. Espera 1 segundo
4. Tenta obter recurso1 (pode resultar em deadlock)

## Sequência que leva ao Deadlock

1. Thread 2 obtém recurso2
2. Thread 1 obtém recurso1
3. Thread 2 tenta obter recurso1 (bloqueada - recurso com Thread 1)
4. Thread 1 tenta obter recurso2 (bloqueada - recurso com Thread 2)
5. Sistema entra em deadlock

## Notas Adicionais

- Este é um exemplo didático para demonstrar o conceito de deadlock
- Em sistemas reais, deadlocks devem ser evitados através de design apropriado
- O programa precisa ser forçadamente encerrado após entrar em deadlock