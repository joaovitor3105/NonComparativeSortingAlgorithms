// benchmark_runner.go
package main

import (
    "fmt"
    "log"
    "os"
    "runtime"
    "time"
    "ordenacao-go/Algorithms"
    "ordenacao-go/Structures"
    "ordenacao-go/Utils"
)

const NUM_EXECUTIONS = 10

type BenchmarkRun struct {
    ExecutionNumber int
    TimeNs         int64
    TimeMicros     float64
    TimeMs         float64
    MemoryUsedKB   float64
    MemoryUsedMB   float64
}

type BenchmarkResult struct {
    StructureName  string
    StructureType  string
    DataSize       int
    Runs           []BenchmarkRun
    AvgTimeMs      float64
    AvgMemoryMB    float64
    MinTimeMs      float64
    MaxTimeMs      float64
    MinMemoryMB    float64
    MaxMemoryMB    float64
}

type SystemInfo struct {
    Timestamp  string
    OS         string
    Arch       string
    CPUs       int
    GoVersion  string
    TotalMemGB float64
}

func getMemStats() runtime.MemStats {
    var m runtime.MemStats
    runtime.ReadMemStats(&m)
    return m
}

func forceGC() {
    runtime.GC()
    runtime.GC()
    time.Sleep(100 * time.Millisecond)
}

func runSingleBenchmark(ds Utils.DataStructure, data []int) (timeNs int64, memoryBytes uint64) {
    forceGC()
    
    memBefore := getMemStats()
    startTime := time.Now()
    
    // Processo de ordenação
    ds.FromArray(data)
    arr := ds.ToArray()
    sorted := Algorithms.CountingSort(arr)
    ds.FromArray(sorted)
    
    duration := time.Since(startTime)
    memAfter := getMemStats()
    
    timeNs = duration.Nanoseconds()
    memoryBytes = memAfter.TotalAlloc - memBefore.TotalAlloc
    
    return
}

func benchmarkStructure(structName, structType string, createStructure func(int) Utils.DataStructure, data []int) BenchmarkResult {
    result := BenchmarkResult{
        StructureName: structName,
        StructureType: structType,
        DataSize:      len(data),
        Runs:          make([]BenchmarkRun, 0, NUM_EXECUTIONS),
    }
    
    fmt.Printf("  %s: ", structName)
    
    var totalTime float64
    var totalMemory float64
    minTime := float64(^uint64(0) >> 1)
    maxTime := 0.0
    minMemory := float64(^uint64(0) >> 1)
    maxMemory := 0.0
    
    for i := 0; i < NUM_EXECUTIONS; i++ {
        ds := createStructure(len(data))
        timeNs, memoryBytes := runSingleBenchmark(ds, data)
        
        run := BenchmarkRun{
            ExecutionNumber: i + 1,
            TimeNs:         timeNs,
            TimeMicros:     float64(timeNs) / 1000.0,
            TimeMs:         float64(timeNs) / 1e6,
            MemoryUsedKB:   float64(memoryBytes) / 1024.0,
            MemoryUsedMB:   float64(memoryBytes) / (1024.0 * 1024.0),
        }
        
        result.Runs = append(result.Runs, run)
        
        totalTime += run.TimeMs
        totalMemory += run.MemoryUsedMB
        
        if run.TimeMs < minTime {
            minTime = run.TimeMs
        }
        if run.TimeMs > maxTime {
            maxTime = run.TimeMs
        }
        if run.MemoryUsedMB < minMemory {
            minMemory = run.MemoryUsedMB
        }
        if run.MemoryUsedMB > maxMemory {
            maxMemory = run.MemoryUsedMB
        }
        
        fmt.Print(".")
    }
    
    result.AvgTimeMs = totalTime / float64(NUM_EXECUTIONS)
    result.AvgMemoryMB = totalMemory / float64(NUM_EXECUTIONS)
    result.MinTimeMs = minTime
    result.MaxTimeMs = maxTime
    result.MinMemoryMB = minMemory
    result.MaxMemoryMB = maxMemory
    
    fmt.Printf(" Concluído (Média: %.2fms, %.2fMB)\n", result.AvgTimeMs, result.AvgMemoryMB)
    
    return result
}

func runBenchmarksForSize(data []int, logFile *os.File) []BenchmarkResult {
    results := make([]BenchmarkResult, 0)
    
    fmt.Fprintf(logFile, "\n=== TAMANHO DO DATASET: %d elementos ===\n", len(data))
    fmt.Printf("\n--- Testando com %d elementos ---\n", len(data))
    
    // Lista Linear
    result := benchmarkStructure("Lista Linear", "linear", 
        func(size int) Utils.DataStructure { 
            return Structures.NewListLinear(size + 100) 
        }, data)
    results = append(results, result)
    logResult(logFile, result)
    
    // Lista Dinâmica
    result = benchmarkStructure("Lista Dinâmica", "dynamic",
        func(size int) Utils.DataStructure { 
            return Structures.NewListDynamic() 
        }, data)
    results = append(results, result)
    logResult(logFile, result)
    
    // Fila Linear
    result = benchmarkStructure("Fila Linear", "linear",
        func(size int) Utils.DataStructure { 
            return Structures.NewQueueLinear(size + 100) 
        }, data)
    results = append(results, result)
    logResult(logFile, result)
    
    // Fila Dinâmica
    result = benchmarkStructure("Fila Dinâmica", "dynamic",
        func(size int) Utils.DataStructure { 
            return Structures.NewQueueDynamic() 
        }, data)
    results = append(results, result)
    logResult(logFile, result)
    
    // Pilha Linear
    result = benchmarkStructure("Pilha Linear", "linear",
        func(size int) Utils.DataStructure { 
            return Structures.NewStackLinear(size + 100) 
        }, data)
    results = append(results, result)
    logResult(logFile, result)
    
    // Pilha Dinâmica
    result = benchmarkStructure("Pilha Dinâmica", "dynamic",
        func(size int) Utils.DataStructure { 
            return Structures.NewStackDynamic() 
        }, data)
    results = append(results, result)
    logResult(logFile, result)
    
    return results
}

func logResult(logFile *os.File, result BenchmarkResult) {
    fmt.Fprintf(logFile, "\n%s (%s) - %d elementos:\n", 
        result.StructureName, result.StructureType, result.DataSize)
    fmt.Fprintf(logFile, "----------------------------------------\n")
    
    // Cabeçalho da tabela
    fmt.Fprintf(logFile, "Execução | Tempo (ms) | Memória (MB)\n")
    fmt.Fprintf(logFile, "---------|------------|-------------\n")
    
    // Dados de cada execução
    for _, run := range result.Runs {
        fmt.Fprintf(logFile, "%8d | %10.2f | %11.2f\n", 
            run.ExecutionNumber, run.TimeMs, run.MemoryUsedMB)
    }
    
    fmt.Fprintf(logFile, "---------|------------|-------------\n")
    fmt.Fprintf(logFile, "MÉDIA    | %10.2f | %11.2f\n", 
        result.AvgTimeMs, result.AvgMemoryMB)
    fmt.Fprintf(logFile, "MÍNIMO   | %10.2f | %11.2f\n", 
        result.MinTimeMs, result.MinMemoryMB)
    fmt.Fprintf(logFile, "MÁXIMO   | %10.2f | %11.2f\n", 
        result.MaxTimeMs, result.MaxMemoryMB)
    fmt.Fprintf(logFile, "\n")
}

func getSystemInfo() SystemInfo {
    var m runtime.MemStats
    runtime.ReadMemStats(&m)
    
    return SystemInfo{
        Timestamp:  time.Now().Format("02/01/2006 15:04:05"),
        OS:         runtime.GOOS,
        Arch:       runtime.GOARCH,
        CPUs:       runtime.NumCPU(),
        GoVersion:  runtime.Version(),
        TotalMemGB: float64(m.Sys) / (1024 * 1024 * 1024),
    }
}

func logSystemInfo(logFile *os.File, info SystemInfo) {
    fmt.Fprintf(logFile, "==========================================\n")
    fmt.Fprintf(logFile, "     BENCHMARK - COUNTING SORT EM GO     \n")
    fmt.Fprintf(logFile, "==========================================\n")
    fmt.Fprintf(logFile, "Data/Hora: %s\n", info.Timestamp)
    fmt.Fprintf(logFile, "Sistema: %s/%s\n", info.OS, info.Arch)
    fmt.Fprintf(logFile, "CPUs: %d\n", info.CPUs)
    fmt.Fprintf(logFile, "Go Version: %s\n", info.GoVersion)
    fmt.Fprintf(logFile, "Memória Total Alocada: %.2f GB\n", info.TotalMemGB)
    fmt.Fprintf(logFile, "Algoritmo: Counting Sort\n")
    fmt.Fprintf(logFile, "Execuções por teste: %d\n", NUM_EXECUTIONS)
    fmt.Fprintf(logFile, "==========================================\n")
}

func createSummaryTable(logFile *os.File, allResults [][]BenchmarkResult) {
    fmt.Fprintf(logFile, "\n==========================================\n")
    fmt.Fprintf(logFile, "           TABELA RESUMO FINAL           \n")
    fmt.Fprintf(logFile, "==========================================\n\n")
    
    // Cabeçalho
    fmt.Fprintf(logFile, "%-20s | %-8s | ", "Estrutura", "Tipo")
    sizes := []int{100, 1000, 10000, 100000, 1000000}
    for _, size := range sizes {
        fmt.Fprintf(logFile, "%10d | ", size)
    }
    fmt.Fprintf(logFile, "\n")
    
    // Linha separadora
    fmt.Fprintf(logFile, "%-20s-+-%-8s-+-", "--------------------", "--------")
    for range sizes {
        fmt.Fprintf(logFile, "-----------+-")
    }
    fmt.Fprintf(logFile, "\n")
    
    // Estruturas na ordem
    Structures := []string{
        "Lista Linear", "Lista Dinâmica", 
        "Fila Linear", "Fila Dinâmica",
        "Pilha Linear", "Pilha Dinâmica",
    }
    
    // Dados de tempo
    fmt.Fprintf(logFile, "\nTEMPO MÉDIO (ms):\n")
    for _, structName := range Structures {
        for sizeIdx, results := range allResults {
            for _, result := range results {
                if result.StructureName == structName && sizeIdx == 0 {
                    fmt.Fprintf(logFile, "%-20s | %-8s | ", 
                        result.StructureName, result.StructureType)
                    break
                }
            }
        }
        
        for sizeIdx := range sizes {
            for _, result := range allResults[sizeIdx] {
                if result.StructureName == structName {
                    fmt.Fprintf(logFile, "%10.2f | ", result.AvgTimeMs)
                    break
                }
            }
        }
        fmt.Fprintf(logFile, "\n")
    }
    
    // Dados de memória
    fmt.Fprintf(logFile, "\nMEMÓRIA MÉDIA (MB):\n")
    for _, structName := range Structures {
        for sizeIdx, results := range allResults {
            for _, result := range results {
                if result.StructureName == structName && sizeIdx == 0 {
                    fmt.Fprintf(logFile, "%-20s | %-8s | ", 
                        result.StructureName, result.StructureType)
                    break
                }
            }
        }
        
        for sizeIdx := range sizes {
            for _, result := range allResults[sizeIdx] {
                if result.StructureName == structName {
                    fmt.Fprintf(logFile, "%10.2f | ", result.AvgMemoryMB)
                    break
                }
            }
        }
        fmt.Fprintf(logFile, "\n")
    }
}

func main() {
    // Criar arquivo de log
    logFileName := fmt.Sprintf("benchmark_%s.log", 
        time.Now().Format("20060102_150405"))
    logFile, err := os.Create(logFileName)
    if err != nil {
        log.Fatal("Erro ao criar arquivo de log:", err)
    }
    defer logFile.Close()
    
    // Log system info
    sysInfo := getSystemInfo()
    logSystemInfo(logFile, sysInfo)
    
    fmt.Println("=== BENCHMARK COUNTING SORT ===")
    fmt.Printf("Executando %d testes para cada estrutura...\n", NUM_EXECUTIONS)
    fmt.Printf("Salvando resultados em: %s\n", logFileName)
    
    // Tamanhos para testar
    sizes := []int{100, 1000, 10000, 100000, 1000000}
    allResults := make([][]BenchmarkResult, 0)
    
    for _, size := range sizes {
        // Carregar dados
        data, err := Utils.LoadRatingsCSV("ratings.csv", size)
        if err != nil {
            // Se não conseguir ler o arquivo, criar dados de teste
            fmt.Printf("Aviso: Usando dados aleatórios para tamanho %d\n", size)
            data = make([]int, size)
            for i := range data {
                // Gerar ratings aleatórios de 1 a 10 (equivalente a 0.5 a 5.0)
                data[i] = (i % 10) + 1
            }
        }
        
        results := runBenchmarksForSize(data, logFile)
        allResults = append(allResults, results)
    }
    
    // Criar tabela resumo
    createSummaryTable(logFile, allResults)
    
    fmt.Fprintf(logFile, "\n==========================================\n")
    fmt.Fprintf(logFile, "         BENCHMARK FINALIZADO            \n")
    fmt.Fprintf(logFile, "==========================================\n")
    
    fmt.Printf("\n✅ Benchmark concluído! Resultados salvos em: %s\n", logFileName)
}