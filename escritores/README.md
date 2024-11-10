# Implementação de Escritores com Exclusão Mútua

Este programa implementa um sistema de escritores que acessam um banco de dados compartilhado de forma exclusiva, utilizando mutex para garantir a sincronização.

## Análise da Execução

### Configuração Inicial
- Banco de dados: Array de 5 posições
- Valores iniciais: [10, 20, 30, 40, 50]
- 3 threads escritoras (ids: 1, 2, 3)

### Sequência de Execução

#### 1. Estado Inicial
```
Estado inicial do banco: 10 20 30 40 50
```
O banco de dados começa com valores pré-definidos em cada posição.

#### 2. Primeira Escrita (Escritor 1)
```
Iniciando escrita - Acesso exclusivo garantido
Escritor 1: Valor atual na posição 1: 20
Escritor 1: Atualizou posição 1 para 100
Finalizando escrita - Liberando acesso
```
- Escritor 1 obtém acesso exclusivo
- Atualiza posição 1 de 20 para 100
- Libera o acesso

#### 3. Segunda Escrita (Escritor 3)
```
Iniciando escrita - Acesso exclusivo garantido
Escritor 3: Valor atual na posição 3: 40
Escritor 3: Atualizou posição 3 para 300
Finalizando escrita - Liberando acesso
```
- Escritor 3 obtém acesso exclusivo
- Atualiza posição 3 de 40 para 300
- Libera o acesso

#### 4. Terceira Escrita (Escritor 2)
```
Iniciando escrita - Acesso exclusivo garantido
Escritor 2: Valor atual na posição 2: 30
Escritor 2: Atualizou posição 2 para 200
Finalizando escrita - Liberando acesso
```
- Escritor 2 obtém acesso exclusivo
- Atualiza posição 2 de 30 para 200
- Libera o acesso

#### 5. Estado Final
```
Estado final do banco: 10 100 200 300 50
```
- Posição 0: Manteve 10 (não modificado)
- Posição 1: Alterado para 100 (Escritor 1)
- Posição 2: Alterado para 200 (Escritor 2)
- Posição 3: Alterado para 300 (Escritor 3)
- Posição 4: Manteve 50 (não modificado)

### Análise dos Resultados

1. **Exclusão Mútua**
   - Cada escritor obtém acesso exclusivo ao banco
   - Apenas um escritor pode escrever por vez
   - O mutex garante que não há escritas simultâneas

2. **Padrão de Escrita**
   - Cada escritor modifica uma posição específica
   - Valor escrito = id_escritor * 100
   - Posições não acessadas mantêm valores originais

3. **Consistência**
   - Todas as operações são atômicas
   - Estado final reflete exatamente as três operações de escrita
   - Não há interferência entre escritores

### Comportamentos Importantes Observados

1. **Acesso Sequencial**
   - As escritas acontecem uma após a outra
   - A ordem de execução pode variar
   - Cada escritor espera sua vez

2. **Rastreamento de Operações**
   - O programa mostra o valor antes e depois de cada escrita
   - Facilita a verificação da correção das operações

3. **Sincronização**
   - O mutex garante que apenas um escritor acessa o banco por vez
   - As mensagens de "Iniciando" e "Finalizando" mostram claramente o controle de acesso

### Características do Programa

1. **Simplicidade**
   - Implementação direta de exclusão mútua
   - Fácil verificação do estado antes e depois das operações

2. **Determinismo**
   - Cada escritor modifica uma posição específica
   - O resultado final é previsível, mesmo que a ordem de execução varie

3. **Segurança**
   - Não há possibilidade de condição de corrida
   - O mutex garante a integridade dos dados