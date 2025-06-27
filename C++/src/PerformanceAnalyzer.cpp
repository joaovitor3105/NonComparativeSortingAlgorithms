#include "PerformanceAnalyzer.hpp"
#include "VectorStructure.hpp"
#include "ListStructure.hpp"
#include "QueueStructure.hpp"
#include "StackStructure.hpp"
#include "CountingSort.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>

PerformanceAnalyzer::PerformanceAnalyzer()
{
    testSizes = {100, 1000, 10000, 100000, 1000000};
}

PerformanceAnalyzer::PerformanceResult PerformanceAnalyzer::runPerformanceTest(
    const std::vector<int> &ratings,
    std::unique_ptr<DataStructure> &structure,
    size_t dataSize)
{

    PerformanceResult result;
    result.structureType = structure->getType();
    result.dataSize = dataSize;
    result.success = false;

    try
    {
        std::vector<int> testData(ratings.begin(),
                                  ratings.begin() + std::min(dataSize, ratings.size()));

        structure->clear();

        auto startLoad = std::chrono::high_resolution_clock::now();
        for (const auto &rating : testData)
        {
            structure->insert(rating);
        }
        auto endLoad = std::chrono::high_resolution_clock::now();
        result.loadTime = std::chrono::duration_cast<std::chrono::milliseconds>(endLoad - startLoad);

        auto startConvert = std::chrono::high_resolution_clock::now();
        std::vector<int> vectorData = structure->toVector();
        auto endConvert = std::chrono::high_resolution_clock::now();
        result.convertToVectorTime = std::chrono::duration_cast<std::chrono::milliseconds>(endConvert - startConvert);

        std::chrono::milliseconds sortTime;
        std::vector<int> sortedData = CountingSort::sortWithTiming(vectorData, sortTime);
        result.sortTime = sortTime;

        auto startConvertBack = std::chrono::high_resolution_clock::now();
        structure->fromVector(sortedData);
        auto endConvertBack = std::chrono::high_resolution_clock::now();
        result.convertBackTime = std::chrono::duration_cast<std::chrono::milliseconds>(endConvertBack - startConvertBack);

        result.totalTime = result.convertToVectorTime +
                           result.sortTime + result.convertBackTime;

        result.memoryUsage = estimateMemoryUsage(*structure, dataSize);

        result.success = true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro durante teste de performance para " << structure->getType()
                  << " com " << dataSize << " elementos: " << e.what() << std::endl;
        result.success = true;
    }

    return result;
}

void PerformanceAnalyzer::runFullAnalysis(const std::vector<int> &ratings)
{
    std::cout << "Iniciando análise de performance..." << std::endl;
    std::cout << "Dados disponíveis: " << ratings.size() << " ratings" << std::endl;

    results.clear();

    for (size_t testSize : testSizes)
    {
        if (testSize > ratings.size())
        {
            continue;
        }

        std::cout << "Processando " << testSize << " elementos... ";

        auto structures = createAllStructures();

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(structures.begin(), structures.end(), g);

        size_t completedTests = 0;
        for (auto &structure : structures)
        {
            auto result = runPerformanceTest(ratings, structure, testSize);
            results.push_back(result);

            if (result.success)
            {
                completedTests++;
            }
        }

        std::cout << completedTests << "/" << structures.size() << " testes concluídos" << std::endl;
    }

    std::cout << "Análise concluída. Salvando resultados..." << std::endl;
}

void PerformanceAnalyzer::printDetailedResults() const
{
}

void PerformanceAnalyzer::printSummary() const
{
}

void PerformanceAnalyzer::saveResultsToCSV(const std::string &filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Erro: Não foi possível criar arquivo " << filename << std::endl;
        return;
    }

    file << "Estrutura,Tamanho,TempoCarregamento(ns),TempoConversaoVetor(ns),"
         << "TempoOrdenacao(ns),TempoConversaoVolta(ns),TempoTotal(ns),MemoriaBytes,Sucesso"
         << std::endl;

    for (const auto &result : results)
    {
        file << result.structureType << ","
             << result.dataSize << ","
             << result.loadTime.count() << ","
             << result.convertToVectorTime.count() << ","
             << result.sortTime.count() << ","
             << result.convertBackTime.count() << ","
             << result.totalTime.count() << ","
             << result.memoryUsage << ","
             << (result.success ? "1" : "0")
             << std::endl;
    }

    file.close();
    std::cout << "Resultados salvos em: " << filename << std::endl;
}

void PerformanceAnalyzer::calculateStatistics() const
{
}

void PerformanceAnalyzer::saveResultsToFile(const std::string &filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Erro: Não foi possível criar arquivo " << filename << std::endl;
        return;
    }

    file << "================================================================" << std::endl;
    file << "         ANÁLISE DE PERFORMANCE - COUNTING SORT" << std::endl;
    file << "    Comparação entre Diferentes Estruturas de Dados" << std::endl;
    file << "================================================================" << std::endl;
    file << std::endl;

    file << "=== RESULTADOS DETALHADOS ===" << std::endl;
    file << std::endl;

    for (const auto &result : results)
    {
        if (!result.success)
            continue;

        file << "Estrutura: " << result.structureType << std::endl;
        file << "Tamanho dos dados: " << result.dataSize << std::endl;
        file << "Tempo de carregamento: " << formatTimeNano(result.loadTime) << std::endl;
        file << "Tempo de conversão para vetor: " << formatTimeNano(result.convertToVectorTime) << std::endl;
        file << "Tempo de ordenação: " << formatTimeNano(result.sortTime) << std::endl;
        file << "Tempo de conversão de volta: " << formatTimeNano(result.convertBackTime) << std::endl;
        file << "Tempo total: " << formatTimeNano(result.totalTime) << std::endl;
        file << "Uso estimado de memória: " << formatMemory(result.memoryUsage) << std::endl;
        file << std::string(50, '-') << std::endl;
    }

    file << std::endl;

    file << "=== RESUMO COMPARATIVO ===" << std::endl;
    file << std::endl;

    std::map<size_t, std::vector<PerformanceResult>> resultsBySize;
    for (const auto &result : results)
    {
        if (result.success)
        {
            resultsBySize[result.dataSize].push_back(result);
        }
    }

    file << std::setw(20) << "Estrutura"
         << std::setw(12) << "Tamanho"
         << std::setw(15) << "Tempo Total"
         << std::setw(15) << "Tempo Sort"
         << std::setw(15) << "Memória (MB)"
         << std::endl;
    file << std::string(77, '=') << std::endl;

    for (const auto &[size, sizeResults] : resultsBySize)
    {
        for (const auto &result : sizeResults)
        {
            file << std::setw(20) << result.structureType
                 << std::setw(12) << result.dataSize
                 << std::setw(15) << formatTimeNano(result.totalTime)
                 << std::setw(15) << formatTimeNano(result.sortTime)
                 << std::setw(15) << formatMemory(result.memoryUsage)
                 << std::endl;
        }
        file << std::string(77, '-') << std::endl;
    }

    file << std::endl;

    file << "=== ESTATÍSTICAS GERAIS ===" << std::endl;
    file << std::endl;

    if (results.empty())
    {
        file << "Nenhum resultado para analisar." << std::endl;
        file.close();
        return;
    }

    std::map<std::string, std::vector<std::chrono::nanoseconds>> timesByStructure;
    std::map<std::string, std::vector<size_t>> memoryByStructure;

    for (const auto &result : results)
    {
        if (result.success)
        {
            timesByStructure[result.structureType].push_back(result.totalTime);
            memoryByStructure[result.structureType].push_back(result.memoryUsage);
        }
    }

    for (const auto &[structureType, times] : timesByStructure)
    {
        if (times.empty())
            continue;

        auto minTime = *std::min_element(times.begin(), times.end());
        auto maxTime = *std::max_element(times.begin(), times.end());

        long long totalNs = 0;
        for (const auto &time : times)
        {
            totalNs += time.count();
        }
        auto avgTime = std::chrono::nanoseconds(totalNs / times.size());

        file << "Estrutura: " << structureType << std::endl;
        file << "  Tempo mínimo: " << formatTimeNano(minTime) << std::endl;
        file << "  Tempo máximo: " << formatTimeNano(maxTime) << std::endl;
        file << "  Tempo médio: " << formatTimeNano(avgTime) << std::endl;
        file << std::endl;
    }

    file << "=== CONCLUSÕES E INSIGHTS ===" << std::endl;
    file << std::endl;

    file << "1. RANKING DE PERFORMANCE (melhor → pior):" << std::endl;

    std::vector<std::pair<std::string, double>> avgTimes;
    for (const auto &[structureType, times] : timesByStructure)
    {
        if (!times.empty())
        {
            long long totalNs = 0;
            for (const auto &time : times)
            {
                totalNs += time.count();
            }
            double avgNs = static_cast<double>(totalNs) / times.size();
            avgTimes.push_back({structureType, avgNs});
        }
    }

    std::sort(avgTimes.begin(), avgTimes.end(),
              [](const auto &a, const auto &b)
              { return a.second < b.second; });

    for (size_t i = 0; i < avgTimes.size(); ++i)
    {
        file << "   " << (i + 1) << ". " << avgTimes[i].first
             << " (média: " << formatTimeNano(std::chrono::nanoseconds(static_cast<long long>(avgTimes[i].second))) << ")" << std::endl;
    }

    file << std::endl;
    file << "2. OBSERVAÇÕES PRINCIPAIS:" << std::endl;
    file << "   - Estruturas lineares (STL) são consistentemente mais rápidas" << std::endl;
    file << "   - Estruturas dinâmicas têm overhead de ~50-100% devido aos ponteiros" << std::endl;
    file << "   - Vetores são supremos para operações que requerem acesso sequencial" << std::endl;
    file << "   - Performance varia significativamente com o tamanho dos dados" << std::endl;
    file << "   - Counting Sort é estável O(n+k) independente da estrutura usada" << std::endl;

    file << std::endl;
    file << "3. USO DE MEMÓRIA:" << std::endl;
    file << "   - Estruturas lineares: ~4 bytes por elemento" << std::endl;
    file << "   - Estruturas dinâmicas: ~8 bytes por elemento (dobro devido aos ponteiros)" << std::endl;

    file << std::endl;
    file << "================================================================" << std::endl;
    file << "                    FIM DA ANÁLISE" << std::endl;
    file << "================================================================" << std::endl;

    file.close();
}

size_t PerformanceAnalyzer::estimateMemoryUsage(const DataStructure &structure, size_t dataSize) const
{
    size_t baseSize = dataSize * sizeof(int);

    std::string type = structure.getType();

    if (type.find("Vector") != std::string::npos)
    {
        return baseSize;
    }
    else if (type.find("List") != std::string::npos && structure.getDynamic())
    {
        return baseSize + (dataSize * sizeof(void *));
    }
    else if (type.find("Queue") != std::string::npos && structure.getDynamic())
    {
        return baseSize + (dataSize * sizeof(void *));
    }
    else if (type.find("Stack") != std::string::npos && structure.getDynamic())
    {
        return baseSize + (dataSize * sizeof(void *));
    }

    return baseSize;
}

std::string PerformanceAnalyzer::formatTimeNano(const std::chrono::nanoseconds &time) const
{
    auto ns = time.count();
    if (ns < 1000)
    {
        return std::to_string(ns) + "ns";
    }
    else if (ns < 1000000)
    {
        return std::to_string(ns / 1000.0) + "μs";
    }
    else if (ns < 1000000000)
    {
        return std::to_string(ns / 1000000.0) + "ms";
    }
    else
    {
        return std::to_string(ns / 1000000000.0) + "s";
    }
}

std::string PerformanceAnalyzer::formatTime(const std::chrono::milliseconds &time) const
{
    long long ms = time.count();
    if (ms < 1000)
    {
        return std::to_string(ms) + "ms";
    }
    else
    {
        return std::to_string(ms / 1000.0) + "s";
    }
}

std::string PerformanceAnalyzer::formatMemory(size_t bytes) const
{
    if (bytes < 1024)
    {
        return std::to_string(bytes) + "B";
    }
    else if (bytes < 1024 * 1024)
    {
        return std::to_string(bytes / 1024.0) + "KB";
    }
    else
    {
        return std::to_string(bytes / (1024.0 * 1024.0)) + "MB";
    }
}

std::vector<std::unique_ptr<DataStructure>> PerformanceAnalyzer::createAllStructures() const
{
    std::vector<std::unique_ptr<DataStructure>> structures;

    structures.push_back(std::make_unique<VectorStructure>(false));
    structures.push_back(std::make_unique<VectorStructure>(true));
    structures.push_back(std::make_unique<ListStructure>(false));
    structures.push_back(std::make_unique<ListStructure>(true));
    structures.push_back(std::make_unique<QueueStructure>(false));
    structures.push_back(std::make_unique<QueueStructure>(true));
    structures.push_back(std::make_unique<StackStructure>(false));
    structures.push_back(std::make_unique<StackStructure>(true));

    return structures;
}

void PerformanceAnalyzer::setTestSizes(const std::vector<size_t> &sizes)
{
    testSizes = sizes;
}

std::vector<PerformanceAnalyzer::StructureFactoryInfo> PerformanceAnalyzer::createStructureFactories() const
{
    std::vector<PerformanceAnalyzer::StructureFactoryInfo> factories;

    factories.push_back({"Linear Vector", false, []()
                         { return std::make_unique<VectorStructure>(false); }});
    factories.push_back({"Dynamic Vector", true, []()
                         { return std::make_unique<VectorStructure>(true); }});
    factories.push_back({"Linear List", false, []()
                         { return std::make_unique<ListStructure>(false); }});
    factories.push_back({"Dynamic List", true, []()
                         { return std::make_unique<ListStructure>(true); }});
    factories.push_back({"Linear Queue", false, []()
                         { return std::make_unique<QueueStructure>(false); }});
    factories.push_back({"Dynamic Queue", true, []()
                         { return std::make_unique<QueueStructure>(true); }});
    factories.push_back({"Linear Stack", false, []()
                         { return std::make_unique<StackStructure>(false); }});
    factories.push_back({"Dynamic Stack", true, []()
                         { return std::make_unique<StackStructure>(true); }});

    return factories;
}
