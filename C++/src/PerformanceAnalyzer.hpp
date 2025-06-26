#ifndef PERFORMANCEANALYZER_HPP
#define PERFORMANCEANALYZER_HPP

#include "DataStructure.hpp"
#include <chrono>
#include <vector>
#include <memory>
#include <map>
#include <functional>
/**
 * Classe responsável por analisar performance dos algoritmos
 * em diferentes estruturas de dados e volumes de entrada
 */
class PerformanceAnalyzer
{
public:
    struct PerformanceResult
    {
        std::string structureType;
        size_t dataSize;
        std::chrono::nanoseconds loadTime;
        std::chrono::nanoseconds convertToVectorTime;
        std::chrono::nanoseconds sortTime;
        std::chrono::nanoseconds convertBackTime;
        std::chrono::nanoseconds totalTime;
        size_t memoryUsage; // Em bytes (estimativa)
        bool success;
    };

private:
    std::vector<PerformanceResult> results;
    std::vector<size_t> testSizes;

public:
    PerformanceAnalyzer();
    // Nova estrutura para encapsular a fábrica e seus metadados
    struct StructureFactoryInfo
    {
        std::string typeName; // Nome da estrutura (e.g., "Linear Vector")
        bool isDynamic;       // Indica se é dinâmica (true) ou linear (false)
        // A função lambda que cria uma nova instância da estrutura
        std::function<std::unique_ptr<DataStructure>()> factory;
    };

    // Novo método que retorna uma lista de informações de fábrica
    std::vector<StructureFactoryInfo> createStructureFactories() const;

    // Novo método para definir os tamanhos de teste
    void setTestSizes(const std::vector<size_t> &sizes);
    /**
     * Executa teste de performance completo
     * @param ratings Dados de entrada
     * @param structure Estrutura de dados a testar
     * @param dataSize Tamanho dos dados para este teste
     * @return Resultado da análise
     */
    PerformanceResult runPerformanceTest(const std::vector<int> &ratings,
                                         std::unique_ptr<DataStructure> &structure,
                                         size_t dataSize);

    /**
     * Executa bateria completa de testes
     * @param ratings Dados completos de entrada
     */
    void runFullAnalysis(const std::vector<int> &ratings);

    /**
     * Imprime resultados detalhados
     */
    void printDetailedResults() const;

    /**
     * Imprime resumo comparativo
     */
    void printSummary() const;

    /**
     * Salva resultados em arquivo CSV
     * @param filename Nome do arquivo de saída
     */
    void saveResultsToCSV(const std::string &filename) const;

    /**
     * Salva resultados completos em arquivo output.dat
     * @param filename Nome do arquivo de saída (padrão: output.dat)
     */
    void saveResultsToFile(const std::string &filename = "output.dat") const;

    /**
     * Calcula estatísticas básicas dos resultados
     */
    void calculateStatistics() const;

private:
    /**
     * Estima uso de memória da estrutura
     * @param structure Estrutura de dados
     * @param dataSize Tamanho dos dados
     * @return Estimativa de memória em bytes
     */
    size_t estimateMemoryUsage(const DataStructure &structure, size_t dataSize) const;

    /**
     * Formata tempo para impressão (nanossegundos)
     * @param time Tempo em nanoseconds
     * @return String formatada
     */
    std::string formatTimeNano(const std::chrono::nanoseconds &time) const;

    /**
     * Formata tempo para impressão (milliseconds) - mantido para compatibilidade
     * @param time Tempo em milliseconds
     * @return String formatada
     */
    std::string formatTime(const std::chrono::milliseconds &time) const;

    /**
     * Formata tamanho de memória para impressão
     * @param bytes Tamanho em bytes
     * @return String formatada
     */
    std::string formatMemory(size_t bytes) const;

    /**
     * Cria todas as estruturas de dados para teste
     * @return Vetor com todas as estruturas
     */
    std::vector<std::unique_ptr<DataStructure>> createAllStructures() const;
};

#endif // PERFORMANCEANALYZER_HPP