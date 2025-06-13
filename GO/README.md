# 📊 Resumo do Projeto: Counting Sort com Estruturas de Dados

## 🎯 Objetivo do Projeto

Implementar o algoritmo **Counting Sort** (ordenação não comparativa) trabalhando com diferentes estruturas de dados (listas, filas e pilhas) em suas versões lineares e dinâmicas, usando dados reais do dataset MovieLens 25M.

## 📁 Dados Utilizados

- **Arquivo**: `ratings.csv` do MovieLens 25M
- **Campo ordenado**: Ratings (avaliações dos filmes)
- **Valores**: 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0 (11 valores possíveis)
- **Conversão**: Multiplicados por 2 para trabalhar com inteiros (1 a 10)

## 🔄 Processo de Ordenação: Estrutura → Vetor → Ordenar → Estrutura

### 1️⃣ **Onde acontece a conversão?**

O processo ocorre na função `benchmarkStructure` em `benchmarks/benchmark.go`:

```go
func benchmarkStructure(name string, ds utils.DataStructure, data []int) BenchmarkResult {
    // 1. ESTRUTURA: Carregar dados na estrutura
    ds.FromArray(data)
    
    // 2. ESTRUTURA → VETOR: Converter para array
    arr := ds.ToArray()
    
    // 3. ORDENAR NO VETOR: Aplicar Counting Sort
    sorted := algorithms.CountingSort(arr)
    
    // 4. VETOR → ESTRUTURA: Converter de volta
    ds.FromArray(sorted)
}
```

### 2️⃣ **Por que essa abordagem?**

- **Simplicidade**: Algoritmos de ordenação trabalham melhor com arrays contíguos
- **Performance**: Acesso direto por índice é O(1) em vetores
- **Reutilização**: Um único algoritmo funciona para todas as estruturas
- **Flexibilidade**: Cada estrutura implementa sua própria conversão

## 🏗️ Estruturas de Dados Implementadas

### **1. Lista Linear** (`structures/list_linear.go`)
```go
type ListLinear struct {
    data     []int    // Array fixo
    size     int      // Elementos atuais
    capacity int      // Capacidade máxima
}
```
- **ToArray()**: Copia elementos do array interno
- **FromArray()**: Sobrescreve array interno com novos dados

### **2. Lista Dinâmica** (`structures/list_dynamic.go`)
```go
type ListDynamic struct {
    head *NodeList   // Primeiro nó
    tail *NodeList   // Último nó (otimização)
    size int
}
```
- **ToArray()**: Percorre nós e copia valores para array
- **FromArray()**: Cria novos nós para cada elemento

### **3. Fila Linear** (`structures/queue_linear.go`)
```go
type QueueLinear struct {
    data     []int    // Array circular
    front    int      // Índice do primeiro
    rear     int      // Índice do último
    size     int
    capacity int
}
```
- **ToArray()**: Copia respeitando ordem circular
- **FromArray()**: Reinsere elementos na fila

### **4. Fila Dinâmica** (`structures/queue_dynamic.go`)
```go
type QueueDynamic struct {
    front *NodeQueue  // Primeiro da fila
    rear  *NodeQueue  // Último da fila
    size  int
}
```
- **ToArray()**: Percorre do front ao rear
- **FromArray()**: Enfileira cada elemento

### **5. Pilha Linear** (`structures/stack_linear.go`)
```go
type StackLinear struct {
    data     []int    // Array
    top      int      // Índice do topo
    capacity int
}
```
- **ToArray()**: Copia do índice 0 até top
- **FromArray()**: Empilha cada elemento

### **6. Pilha Dinâmica** (`structures/stack_dynamic.go`)
```go
type StackDynamic struct {
    top  *NodeStack   // Topo da pilha
    size int
}
```
- **ToArray()**: Percorre do topo até a base
- **FromArray()**: Empilha cada elemento

## 🔢 Algoritmo Counting Sort

### Como funciona:
1. **Contagem**: Conta quantas vezes cada valor (1-10) aparece
2. **Acumulação**: Soma as contagens para determinar posições
3. **Reconstrução**: Coloca cada elemento em sua posição final

### Implementação otimizada para ratings:
```go
func CountingSort(arr []int) []int {
    const MIN_RATING = 1   // 0.5★ convertido
    const MAX_RATING = 10  // 5.0★ convertido
    const RANGE_SIZE = 10
    
    // Array de contagem (tamanho fixo 10)
    count := make([]int, RANGE_SIZE)
    
    // Contar ocorrências
    for _, v := range arr {
        count[v-MIN_RATING]++
    }
    
    // ... resto do algoritmo
}
```

### Vantagens para este caso:
- **Range fixo**: Apenas 10 valores possíveis
- **Memória constante**: O(10) = O(1)
- **Complexidade**: O(n + 10) = O(n)

## 📊 Sistema de Benchmark

### **Coleta de Dados** (`benchmark_runner.go`):
- Executa cada teste **10 vezes**
- Mede **tempo** (nanosegundos → milissegundos)
- Mede **memória** (bytes → megabytes)
- Calcula **média, mínimo e máximo**

### **Tamanhos testados**:
- 100 elementos
- 1.000 elementos
- 10.000 elementos
- 100.000 elementos
- 1.000.000 elementos

### **Saída** (arquivo `.log`):
```
Lista Linear (linear) - 1000 elementos:
----------------------------------------
Execução | Tempo (ms) | Memória (MB)
---------|------------|-------------
       1 |       1.23 |        0.08
       2 |       1.21 |        0.08
...
MÉDIA    |       1.22 |        0.08
```

## 🚀 Como Executar

### 1. **Preparação**:
```bash
# Baixar dataset
wget https://files.grouplens.org/datasets/movielens/ml-25m.zip
unzip ml-25m.zip
cp ml-25m/ratings.csv .
```

### 2. **Execução**:
```bash
# Compilar e executar benchmark
make benchmark

# Ou manualmente
go build benchmark_runner.go
./benchmark_runner
```

### 3. **Resultados**:
- Arquivo gerado: `benchmark_YYYYMMDD_HHMMSS.log`
- Contém todas as execuções e estatísticas

## 📈 Análise de Performance Esperada

### **Estruturas Lineares vs Dinâmicas**:
- **Lineares**: Mais rápidas (cache locality)
- **Dinâmicas**: Mais lentas (ponteiros dispersos)

### **Complexidade Total**:
1. **FromArray**: O(n) para todas estruturas
2. **ToArray**: O(n) para todas estruturas
3. **CountingSort**: O(n + 10) = O(n)
4. **Total**: O(n) + O(n) + O(n) = **O(n)**

### **Gargalos**:
- **Memória**: Estruturas dinâmicas alocam nó por nó
- **Cache**: Arrays contíguos são ~3-5x mais rápidos
- **Conversão**: Overhead de criar/destruir estruturas

## 🎯 Conclusão

O projeto demonstra como diferentes estruturas de dados impactam a performance de algoritmos, mesmo quando o algoritmo principal (Counting Sort) tem complexidade linear. A conversão estrutura ↔ vetor permite reutilizar o mesmo algoritmo para todas as estruturas, facilitando comparações justas entre implementações.