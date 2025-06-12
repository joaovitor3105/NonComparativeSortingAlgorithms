package main

import (
    "fmt"
    "log"
    "ordenacao-go/Benchmarks"
    "ordenacao-go/Utils"
)

func main() {
    fmt.Println("=== Ordenação Não Comparativa em Go ===")
    
    // Tamanhos para testar
    sizes := []int{100, 1000, 10000, 100000, 1000000}
    
    // Executar benchmarks com diferentes tamanhos
    Benchmarks.RunBenchmarkWithSizes("/home/john/Desktop/NonComparativeSortingAlgorithms/ml-25m/ratings.csv", sizes)
    
    // Exemplo de uso individual
    fmt.Println("\n=== Exemplo de Uso Individual ===")
    data, err := Utils.LoadRatingsCSV("/home/john/Desktop/NonComparativeSortingAlgorithms/ml-25m/ratings.csv", 100)
    if err != nil {
        log.Fatal("Erro ao carregar CSV:", err)
    }
    
    // Demonstrar ordenação com cada estrutura
    demonstrateUsage(data)
}

func demonstrateUsage(data []int) {
    // Código de demonstração aqui
    fmt.Println("Dados originais (primeiros 10):", data[:10])
    // ... mais demonstrações
}