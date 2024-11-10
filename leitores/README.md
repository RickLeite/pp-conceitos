# Implementação de Leitores com Acesso Simultâneo

Este programa implementa um sistema de leitores que podem acessar simultaneamente um recurso compartilhado (banco de dados), demonstrando o conceito de leitura concorrente.

## Análise da Execução

### Configuração Inicial
- Banco de dados: Um valor inteiro (100)
- 3 threads leitoras (ids: 1, 2, 3)
- Contador de leitores ativos inicializado em 0

### Sequência de Execução

#### 1. Primeira Leitura (Leitor 1)
```
Leitor 1 iniciando leitura. Leitores ativos: 1
Leitor 1 leu o valor: 100
```
- Primeiro leitor inicia
- Incrementa contador para 1
- Lê o valor do banco

#### 2. Segunda Leitura (Leitor 2)
```
Leitor 2 iniciando leitura. Leitores ativos: 2
Leitor 2 leu o valor: 100
```
- Segundo leitor inicia enquanto primeiro ainda está ativo
- Incrementa contador para 2
- Lê o mesmo valor

#### 3. Terceira Leitura (Leitor 3)
```
Leitor 3 iniciando leitura. Leitores ativos: 3
Leitor 3 leu o valor: 100
```
- Terceiro leitor inicia com outros dois ativos
- Incrementa contador para 3
- Lê o mesmo valor

#### 4. Finalização das Leituras
```
Leitor 1 finalizando leitura. Leitores ativos: 2
Leitor 3 finalizando leitura. Leitores ativos: 1
Leitor 2 finalizando leitura. Leitores ativos: 0
```
- Leitores finalizam em ordem diferente da inicialização
- Cada um decrementa o contador ao sair
- Último leitor deixa contador em 0

### Análise dos Resultados

1. **Leitura Simultânea**
   - Múltiplos leitores podem ler ao mesmo tempo
   - O contador de leitores ativos aumenta e diminui corretamente
   - Todos os leitores veem o mesmo valor (100)

2. **Controle de Acesso**
   - Cada leitor registra sua entrada e saída
   - O sistema mantém controle preciso do número de leitores ativos
   - Não há bloqueio entre leitores

3. **Consistência**
   - Todos os leitores acessam o mesmo valor
   - O valor permanece constante durante todas as leituras
   - Ordem de finalização pode ser diferente da ordem de início

### Comportamentos Importantes Observados

1. **Concorrência**
   - Leitores não precisam esperar outros leitores terminarem
   - Podem haver múltiplos leitores ativos simultaneamente
   - O contador de leitores ativos reflete isso claramente

2. **Rastreamento**
   - O programa registra claramente entrada e saída de cada leitor
   - Mostra o número atual de leitores ativos em cada momento
   - Permite verificar a corretude da sincronização

3. **Ordem de Execução**
   - Início: 1 → 2 → 3
   - Fim: 1 → 3 → 2
   - Demonstra a natureza assíncrona da execução

### Características do Programa

1. **Simplicidade**
   - Implementação direta do conceito de leitores concorrentes
   - Fácil visualização do estado do sistema através dos logs

2. **Controle**
   - Uso de mutex para proteger o contador de leitores
   - Manutenção consistente do número de leitores ativos

3. **Demonstração**
   - Ilustra claramente o conceito de leitura simultânea
   - Mostra como múltiplos leitores podem coexistir
   - Evidencia a não necessidade de exclusão mútua entre leitores