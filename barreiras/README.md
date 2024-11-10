# Implementação de Barreiras em Programação Paralela

Este programa demonstra o uso de barreiras para sincronização de threads em diferentes fases de execução. Uma barreira garante que todas as threads completem uma fase antes que qualquer uma possa prosseguir para a próxima.

## Análise da Execução

### Configuração Inicial
- 3 threads (ids: 0, 1, 2)
- 2 fases de execução
- 2 barreiras de sincronização

### Sequência de Execução

#### 1. Início da Fase 1
```
Thread 0 iniciando fase 1
Thread 2 iniciando fase 1
Thread 1 iniciando fase 1
```
- As threads iniciam a primeira fase em ordem não determinística
- Cada thread executa independentemente

#### 2. Término da Fase 1 e Primeira Barreira
```
Thread 0 terminou fase 1
Thread 0 esperando na barreira 1
Thread 1 terminou fase 1
Thread 1 esperando na barreira 1
Thread 2 terminou fase 1
Thread 2 esperando na barreira 1
```
- Cada thread chega à barreira após terminar sua execução
- Todas devem esperar na barreira até a última chegar

#### 3. Liberação da Primeira Barreira
```
Thread 2 passou da barreira 1
Thread 2 iniciando fase 2
Thread 1 passou da barreira 1
Thread 1 iniciando fase 2
Thread 0 passou da barreira 1
Thread 0 iniciando fase 2
```
- Quando a última thread chega, todas são liberadas
- Podem iniciar a fase 2 em qualquer ordem

#### 4. Término da Fase 2 e Segunda Barreira
```
Thread 0 terminou fase 2
Thread 0 esperando na barreira 2
Thread 1 terminou fase 2
Thread 1 esperando na barreira 2
Thread 2 terminou fase 2
Thread 2 esperando na barreira 2
```
- Processo se repete para a segunda fase
- Threads novamente esperam todas chegarem

#### 5. Liberação da Segunda Barreira e Término
```
Thread 2 passou da barreira 2
Thread 1 passou da barreira 2
Thread 0 passou da barreira 2
Programa finalizado!
```
- Todas as threads são liberadas
- Programa termina com todas as fases completas

### Análise dos Resultados

1. **Sincronização por Fase**
   - Cada fase é completamente isolada
   - Nenhuma thread inicia fase 2 antes que todas terminem fase 1
   - Garante consistência na execução das fases

2. **Ordem de Execução**
   - Ordem de início pode ser diferente em cada fase
   - Ordem de término também pode variar
   - Apenas a sincronização nas barreiras é garantida

3. **Comportamento da Barreira**
   - Bloqueia threads até que todas cheguem
   - Libera todas simultaneamente
   - Reinicia para próxima fase

### Comportamentos Importantes Observados

1. **Independência na Execução**
   - Dentro de cada fase, threads executam independentemente
   - Tempo de execução pode variar entre threads
   - Ordem de chegada na barreira é não determinística

2. **Ponto de Sincronização**
   - Barreiras funcionam como pontos de encontro
   - Garantem que todas as threads completem cada fase
   - Previnem que threads avancem prematuramente

3. **Coordenação de Fases**
   - Divisão clara entre fases do programa
   - Todas as threads devem completar fase atual
   - Início sincronizado da próxima fase

### Características do Programa

1. **Estrutura**
   - Duas fases distintas de execução
   - Duas barreiras de sincronização
   - Controle preciso do fluxo de execução

2. **Sincronização**
   - Uso de mutex e variável de condição
   - Contador de threads na barreira
   - Reset automático para próxima fase

3. **Robustez**
   - Funciona com diferentes velocidades de thread
   - Garante execução correta independente da ordem
   - Previne condições de corrida entre fases