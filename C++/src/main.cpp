#include <iostream>
#include <vector>
#include <memory>
#include <chrono>

// Inclui todos os headers
#include "CSVReader.hpp"
#include "CountingSort.hpp"
#include "PerformanceAnalyzer.hpp"
#include "VectorStructure.hpp"
#include "ListStructure.hpp"
#include "QueueStructure.hpp"
#include "StackStructure.hpp"

void printHeader()
{
    std::cout << "================================================================" << std::endl;
    std::cout << "         ANÁLISE DE PERFORMANCE - COUNTING SORT" << std::endl;
    std::cout << "    Comparação entre Diferentes Estruturas de Dados" << std::endl;
    std::cout << "================================================================" << std::endl;
    std::cout << std::endl;
}

void demonstrateCountingSort(const std::vector<int> &sample)
{
    std::cout << "Testando algoritmo Counting Sort... ";

    // Pega uma amostra pequena para demonstração
    std::vector<int> demo(sample.begin(), sample.begin() + std::min(static_cast<size_t>(20), sample.size()));

    auto sorted = CountingSort::sort(demo);
    bool isCorrect = CountingSort::isSorted(sorted);

    std::cout << (isCorrect ? "✓ Funcionando corretamente" : "✗ Erro detectado") << std::endl;
}

void demonstrateStructures(const std::vector<int> &sample)
{
    std::cout << "Testando estruturas de dados... ";

    // Amostra pequena para demonstração
    std::vector<int> demo(sample.begin(), sample.begin() + std::min(static_cast<size_t>(10), sample.size()));

    // Testa cada tipo de estrutura
    std::vector<std::unique_ptr<DataStructure>> structures;
    structures.push_back(std::make_unique<VectorStructure>(false));
    structures.push_back(std::make_unique<VectorStructure>(true));
    structures.push_back(std::make_unique<ListStructure>(false));
    structures.push_back(std::make_unique<ListStructure>(true));

    int successCount = 0;
    for (auto &structure : structures)
    {
        // Carrega dados
        for (int val : demo)
        {
            structure->insert(val);
        }

        // Converte para vetor
        auto vectorData = structure->toVector();

        // Ordena
        auto sortedData = CountingSort::sort(vectorData);

        // Converte de volta
        structure->fromVector(sortedData);

        // Verifica resultado
        auto finalData = structure->toVector();
        if (CountingSort::isSorted(finalData))
        {
            successCount++;
        }
    }

    std::cout << successCount << "/" << structures.size() << " estruturas funcionando corretamente" << std::endl;
}

void runInteractiveMode()
{
    std::cout << "=== MODO INTERATIVO ===" << std::endl;
    std::cout << "Digite o caminho para o arquivo ratings.csv: ";

    std::string filename;
    std::getline(std::cin, filename);

    CSVReader reader(filename);

    if (!reader.isValidFile())
    {
        std::cout << "Arquivo não encontrado ou inválido. Usando arquivo padrão 'ratings.csv'" << std::endl;
        reader = CSVReader("ratings.csv");
    }

    std::cout << "Quantos registros deseja carregar? (0 = todos): ";
    size_t maxRecords;
    std::cin >> maxRecords;

    auto movieIds = reader.readMovieIds(maxRecords);

    if (movieIds.empty())
    {
        std::cout << "Nenhum dado carregado. Encerrando." << std::endl;
        return;
    }

    // Demonstrações
    demonstrateCountingSort(movieIds);
    demonstrateStructures(movieIds);

    // Análise de performance
    PerformanceAnalyzer analyzer;
    analyzer.runFullAnalysis(movieIds);

    // Salvar resultados
    analyzer.saveResultsToFile("output.dat");
    analyzer.saveResultsToCSV("performance_results.csv");

    std::cout << "Resultados salvos em 'output.dat' e 'performance_results.csv'" << std::endl;
}

int main(int argc, char *argv[])
{
    printHeader();

    try
    {
        if (argc > 1)
        {
            // Modo linha de comando
            std::string filename = argv[1];
            size_t maxRecords = 0;

            if (argc > 2)
            {
                maxRecords = std::stoul(argv[2]);
            }

            std::cout << "Carregando dados de: " << filename << std::endl;
            if (maxRecords > 0)
            {
                std::cout << "Limitando a " << maxRecords << " registros" << std::endl;
            }
            std::cout << std::endl;

            CSVReader reader(filename);
            auto movieIds = reader.readMovieIds(maxRecords);

            if (movieIds.empty())
            {
                std::cout << "Nenhum dado carregado. Verifique o arquivo." << std::endl;
                return 1;
            }

            // Demonstrações rápidas
            demonstrateCountingSort(movieIds);
            demonstrateStructures(movieIds);

            // Análise completa
            PerformanceAnalyzer analyzer;
            analyzer.runFullAnalysis(movieIds);
            analyzer.saveResultsToFile("output.dat");
            analyzer.saveResultsToCSV("performance_results.csv");
        }
        else
        {
            // Modo interativo
            runInteractiveMode();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    std::cout << std::endl;
    std::cout << "=== ANÁLISE FINALIZADA ===" << std::endl;
    std::cout << "Resultados detalhados salvos em 'output.dat'" << std::endl;
    std::cout << "Dados para análise salvos em 'performance_results.csv'" << std::endl;

    return 0;
}