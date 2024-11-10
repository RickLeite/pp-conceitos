# Implementação do Problema dos Leitores e Escritores

## Análise da Execução

### Configuração Inicial
- 3 threads leitoras (ids: 1, 2, 3)
- 2 threads escritoras (ids: 1, 2)
- Valor inicial do banco de dados: 0

### Sequência de Execução

#### 1. Primeira Rodada de Leituras (Valor = 0)
```
Leitor 1 tentando ler
Leitor 140588128831040 está lendo valor 0
Leitor 2 tentando ler
Leitor 140588120438336 está lendo valor 0
Leitor 3 tentando ler
Leitor 140588112045632 está lendo valor 0
```
Observação: Os três leitores conseguem ler simultaneamente o valor inicial (0).

#### 2. Primeira Escrita (0 -> 1)
```
Escritor 140588095260224 está preparando dados
Escritor 140588095260224 atualizou valor para 1
```
- Escritor 1 obtém acesso exclusivo
- Incrementa o valor de 0 para 1

#### 3. Segunda Escrita (1 -> 2)
```
Escritor 140588103652928 atualizou valor para 2
```
- Escritor 2 obtém acesso exclusivo
- Incrementa o valor de 1 para 2

#### 4. Segunda Rodada de Leituras (Valor = 2)
```
Leitor 140588128831040 está lendo valor 2
Leitor 140588120438336 está lendo valor 2
Leitor 140588112045632 está lendo valor 2
```
- Novamente, os três leitores leem simultaneamente
- Todos veem o mesmo valor (2)

#### 5. Terceira e Quarta Escritas (2 -> 3 -> 4)
```
Escritor 140588095260224 atualizou valor para 3
Escritor 140588103652928 atualizou valor para 4
```
- Escritores alternadamente incrementam o valor

#### 6. Terceira Rodada de Leituras (Valor = 4)
```
Leitor 140588128831040 está lendo valor 4
Leitor 140588120438336 está lendo valor 4
Leitor 140588112045632 está lendo valor 4
```
- Leitores novamente acessam simultaneamente
- Todos leem o valor 4

#### 7. Escritas Finais (4 -> 5 -> 6)
```
Escritor 140588095260224 atualizou valor para 5
Escritor 140588103652928 atualizou valor para 6
```
- Últimas atualizações antes do término

### Análise dos Resultados

1. **Concorrência de Leitores**
   - Múltiplos leitores podem ler simultaneamente
   - Todos os leitores sempre veem o mesmo valor

2. **Exclusão Mútua de Escritores**
   - Apenas um escritor atualiza por vez
   - Cada escrita incrementa o valor em 1

3. **Consistência**
   - Não há leituras durante escritas
   - Não há escritas simultâneas
   - Valores são incrementados sequencialmente

4. **Término**
   - O programa termina quando o valor atinge 6
   - O valor final é maior que 5 devido à condição de corrida na verificação de parada

## Comportamentos Importantes Observados

1. **Leituras Simultâneas**
   - Quando um leitor está lendo, outros leitores podem se juntar
   - Isso é evidenciado pelos grupos de três leituras com o mesmo valor

2. **Escritas Exclusivas**
   - Escritores sempre operam sozinhos
   - Cada operação de escrita resulta em um incremento único

3. **Sincronização**
   - As threads alternam entre períodos de leitura e escrita
   - Não há sobreposição entre operações de escrita
   - Leitores sempre veem um estado consistente do dado

4. **Condição de Parada**
   - O programa ultrapassa levemente o valor 5
   - Isso demonstra a natureza das condições de corrida em sistemas concorrentes