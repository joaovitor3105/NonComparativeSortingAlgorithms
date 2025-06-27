#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <map>
#include <functional>

#include "DataStructure.hpp"
#include "VectorStructure.hpp"
#include "ListStructure.hpp"
#include "QueueStructure.hpp"
#include "StackStructure.hpp"
#include "CountingSort.hpp"
#include "CSVReader.hpp"
#include "PerformanceAnalyzer.hpp"

#define ARQUIVO_ENTRADA "/home/joao-vitor/Área de trabalho/programacao/NonComparativeSortingAlgorithms/C/datasets/ratings.csv"

const std::vector<size_t> VOLUMES_TESTE = {100, 1000, 10000, 100000, 1000000};
const int NUM_REPETICOES = 10;

void exibirTabelaResumoFinal(
    const std::map<std::string, std::map<size_t, double>> &temposMedios,
    const std::map<std::string, std::map<size_t, size_t>> &memoriasEstimadas)
{
    std::cout << "\n\n";
    std::cout << "                                         TABELA RESUMO FINAL\n";
    std::cout << "============================================================================================================\n";
    std::cout << std::left << std::setw(22) << "Estrutura" << " | "
              << std::left << std::setw(10) << "Tipo" << " |";
    for (size_t volume : VOLUMES_TESTE)
    {
        std::cout << std::right << std::setw(10) << volume << " |";
    }
    std::cout << "\n------------------------------------------------------------------------------------------------------------\n";
    std::cout << "\nTEMPO (ms):\n";
    std::vector<std::string> structureNames = {
        "Linear Vector", "Dynamic Vector",
        "Linear List", "Dynamic List",
        "Linear Queue", "Dynamic Queue",
        "Linear Stack", "Dynamic Stack"};

    for (const std::string &name : structureNames)
    {
        if (temposMedios.count(name) == 0)
            continue;
        std::string type = (name.find("Linear") != std::string::npos) ? "linear" : "dynamic";
        std::cout << std::left << std::setw(22) << name << " | "
                  << std::left << std::setw(10) << type << " |";
        for (size_t volume : VOLUMES_TESTE)
        {
            if (temposMedios.at(name).count(volume) && temposMedios.at(name).at(volume) >= 0)
            {
                std::cout << std::fixed << std::setprecision(2)
                          << std::right << std::setw(10) << temposMedios.at(name).at(volume) << " |";
            }
            else
            {
                std::cout << std::right << std::setw(10) << "FALHA" << " |";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\nMEMORIA (MB):\n";
    for (const std::string &name : structureNames)
    {
        if (memoriasEstimadas.count(name) == 0)
            continue;
        std::string type = (name.find("Linear") != std::string::npos) ? "linear" : "dynamic";
        std::cout << std::left << std::setw(22) << name << " | "
                  << std::left << std::setw(10) << type << " |";
        for (size_t volume : VOLUMES_TESTE)
        {
            if (memoriasEstimadas.at(name).count(volume) && memoriasEstimadas.at(name).at(volume) > 0)
            {
                double memoria_mb = static_cast<double>(memoriasEstimadas.at(name).at(volume)) / (1024.0 * 1024.0);
                std::cout << std::fixed << std::setprecision(2)
                          << std::right << std::setw(10) << memoria_mb << " |";
            }
            else
            {
                std::cout << std::right << std::setw(10) << "N/A" << " |";
            }
        }
        std::cout << "\n";
    }
    std::cout << "============================================================================================================\n";
}

int main()
{
    std::cout << "\n";
    std::cout << "╔═══════════════════════════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║                 ANÁLISE DE DESEMPENHO - ESTRUTURAS DE DADOS (LINGUAGEM C++)               ║\n";
    std::cout << "║                                     COUNTING SORT                                     ║\n";
    std::cout << "╚═══════════════════════════════════════════════════════════════════════════════════════╝\n";
    std::cout << "📁 Arquivo: " << ARQUIVO_ENTRADA << std::endl;
    std::cout << "📊 Volumes de teste: ";
    for (size_t volume : VOLUMES_TESTE)
        std::cout << volume << " ";
    std::cout << "\n";
    std::cout << "🔄 Repetições por teste: " << NUM_REPETICOES << "\n\n";

    CSVReader reader(ARQUIVO_ENTRADA);
    if (!reader.isValidFile())
    {
        std::cerr << "Erro: Arquivo de entrada '" << ARQUIVO_ENTRADA << "' não encontrado ou inválido.\n";
        return 1;
    }

    std::vector<int> allRatings = reader.readMovieIds(0);

    if (allRatings.empty())
    {
        std::cerr << "Nenhum dado foi lido do arquivo. Saindo.\n";
        return 1;
    }
    std::cout << "Total de ratings lidos: " << allRatings.size() << std::endl;

    std::map<std::string, std::map<size_t, double>> resultadosTempoMedio;
    std::map<std::string, std::map<size_t, size_t>> resultadosMemoriaEstimada;

    PerformanceAnalyzer analyzer;
    analyzer.setTestSizes(VOLUMES_TESTE);

    auto structureFactories = analyzer.createStructureFactories();

    for (size_t currentVolume : VOLUMES_TESTE)
    {
        if (currentVolume > allRatings.size())
        {
            std::cout << "Pulando volume de " << currentVolume << " elementos, pois é maior que os dados disponíveis (" << allRatings.size() << ").\n";
            continue;
        }

        std::cout << "⏳ Testando com " << currentVolume << " elementos (" << NUM_REPETICOES << " repetições):\n";

        for (const auto &factoryInfo : structureFactories)
        {
            double somaTemposMs = 0.0;
            int testesBemSucedidos = 0;
            size_t memoriaAmostra = 0;
            std::string structureName = factoryInfo.typeName;

            std::cout << "   " << structureName << "... " << std::flush;

            for (int k = 0; k < NUM_REPETICOES; ++k)
            {
                std::unique_ptr<DataStructure> currentStructure = factoryInfo.factory();

                PerformanceAnalyzer::PerformanceResult res =
                    analyzer.runPerformanceTest(allRatings, currentStructure, currentVolume);

                if (res.success)
                {
                    somaTemposMs += res.totalTime.count() / 1000000.0;
                    testesBemSucedidos++;
                    if (k == 0)
                    {
                        memoriaAmostra = res.memoryUsage;
                    }
                }
                else
                {
                    std::cerr << "❌ Erro ou falha na ordenação em uma das repetições para "
                              << structureName << " com " << currentVolume << " elementos!\n";
                    somaTemposMs = -1.0;
                    memoriaAmostra = 0;
                    break;
                }
            }

            if (somaTemposMs != -1.0 && testesBemSucedidos > 0)
            {
                resultadosTempoMedio[structureName][currentVolume] = somaTemposMs / testesBemSucedidos;
                resultadosMemoriaEstimada[structureName][currentVolume] = memoriaAmostra;
                std::cout << "✅ Concluído! Média: ("
                          << std::fixed << std::setprecision(2) << resultadosTempoMedio[structureName][currentVolume] << " ms)\n";
            }
            else
            {
                resultadosTempoMedio[structureName][currentVolume] = -1.0;
                resultadosMemoriaEstimada[structureName][currentVolume] = 0;
                if (somaTemposMs != -1.0)
                {
                    std::cerr << "❌ Nenhuma repetição bem-sucedida para "
                              << structureName << " com " << currentVolume << " elementos.\n";
                }
            }
        }
        std::cout << std::endl;
    }

    exibirTabelaResumoFinal(resultadosTempoMedio, resultadosMemoriaEstimada);

    return 0;
}
