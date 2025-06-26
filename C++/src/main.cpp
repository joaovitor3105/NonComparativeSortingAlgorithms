#include <iostream>   // Para operações de entrada/saída (e.g., std::cout, std::endl)
#include <vector>     // Para std::vector
#include <string>     // Para std::string
#include <memory>     // Para std::unique_ptr
#include <chrono>     // Para medição de tempo
#include <algorithm>  // Para std::min (usado implicitamente por std::vector na construção)
#include <iomanip>    // Para std::fixed e std::setprecision
#include <map>        // Para std::map, usado para armazenar resultados agregados
#include <functional> // Para std::function, usado para as fábricas de estruturas

// Inclui os cabeçalhos para todas as estruturas de dados e utilitários
#include "DataStructure.hpp"
#include "VectorStructure.hpp"
#include "ListStructure.hpp"
#include "QueueStructure.hpp"
#include "StackStructure.hpp"
#include "CountingSort.hpp" // Embora o sort seja chamado pelo PerformanceAnalyzer
#include "CSVReader.hpp"
#include "PerformanceAnalyzer.hpp" // Para a classe PerformanceAnalyzer

// Define o nome do arquivo de entrada de dados
#define ARQUIVO_ENTRADA "/home/joao-vitor/Área de trabalho/programacao/NonComparativeSortingAlgorithms/C/datasets/ratings.csv" // Assumindo que ratings.csv está no mesmo diretório

// Volumes de teste a serem executados automaticamente
const std::vector<size_t> VOLUMES_TESTE = {100, 1000, 10000, 100000, 1000000};
// Número de repetições para cada teste para calcular a média
const int NUM_REPETICOES = 10;

// Função para imprimir a tabela de resumo final
// Recebe mapas para os tempos médios e as memórias estimadas, indexados pelo nome da estrutura e pelo volume de dados.
void exibirTabelaResumoFinal(
    const std::map<std::string, std::map<size_t, double>> &temposMedios,
    const std::map<std::string, std::map<size_t, size_t>> &memoriasEstimadas)
{
    std::cout << "\n\n";
    std::cout << "                                         TABELA RESUMO FINAL\n";
    std::cout << "============================================================================================================\n";

    // Cabeçalho da tabela: Estrutura, Tipo, e os Volumes de Teste
    std::cout << std::left << std::setw(22) << "Estrutura" << " | "
              << std::left << std::setw(10) << "Tipo" << " |";
    for (size_t volume : VOLUMES_TESTE)
    {
        std::cout << std::right << std::setw(10) << volume << " |"; // Imprime cada volume de teste
    }
    std::cout << "\n------------------------------------------------------------------------------------------------------------\n";

    // Seção de Tempo: Exibe os tempos médios de execução
    std::cout << "\nTEMPO (ms):\n";
    // Define a ordem das estruturas para a exibição, garantindo consistência
    // Esta lista deve corresponder aos nomes retornados pelas fábricas em PerformanceAnalyzer::createStructureFactories()
    std::vector<std::string> structureNames = {
        "Linear Vector", "Dynamic Vector",
        "Linear List", "Dynamic List",
        "Linear Queue", "Dynamic Queue",
        "Linear Stack", "Dynamic Stack"};

    for (const std::string &name : structureNames)
    {
        // Verifica se existem resultados para a estrutura atual
        if (temposMedios.count(name) == 0)
            continue;

        // Determina se a estrutura é linear ou dinâmica para exibição
        std::string type = (name.find("Linear") != std::string::npos) ? "linear" : "dynamic";
        std::cout << std::left << std::setw(22) << name << " | "
                  << std::left << std::setw(10) << type << " |";
        for (size_t volume : VOLUMES_TESTE)
        {
            // Verifica se há um resultado para o volume atual e se não é um sinal de falha (-1.0)
            if (temposMedios.at(name).count(volume) && temposMedios.at(name).at(volume) >= 0)
            {
                std::cout << std::fixed << std::setprecision(2) // Formata a saída para 2 casas decimais
                          << std::right << std::setw(10) << temposMedios.at(name).at(volume) << " |";
            }
            else
            {
                std::cout << std::right << std::setw(10) << "FALHA" << " |"; // Indica falha no teste
            }
        }
        std::cout << "\n";
    }

    // Seção de Memória: Exibe o uso estimado de memória
    std::cout << "\nMEMORIA (MB):\n";
    for (const std::string &name : structureNames)
    {
        // Verifica se existem resultados para a estrutura atual
        if (memoriasEstimadas.count(name) == 0)
            continue;

        // Determina se a estrutura é linear ou dinâmica para exibição
        std::string type = (name.find("Linear") != std::string::npos) ? "linear" : "dynamic";
        std::cout << std::left << std::setw(22) << name << " | "
                  << std::left << std::setw(10) << type << " |";
        for (size_t volume : VOLUMES_TESTE)
        {
            // Verifica se há um resultado para o volume atual e se o uso de memória é maior que 0 (não N/A)
            if (memoriasEstimadas.at(name).count(volume) && memoriasEstimadas.at(name).at(volume) > 0)
            {
                // Converte bytes para megabytes para exibição
                double memoria_mb = static_cast<double>(memoriasEstimadas.at(name).at(volume)) / (1024.0 * 1024.0);
                std::cout << std::fixed << std::setprecision(2)
                          << std::right << std::setw(10) << memoria_mb << " |";
            }
            else
            {
                std::cout << std::right << std::setw(10) << "N/A" << " |"; // Indica que a memória não está disponível
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

    // Cria um objeto CSVReader para ler os dados do arquivo
    CSVReader reader(ARQUIVO_ENTRADA);
    if (!reader.isValidFile())
    {
        std::cerr << "Erro: Arquivo de entrada '" << ARQUIVO_ENTRADA << "' não encontrado ou inválido.\n";
        return 1; // Retorna com código de erro se o arquivo não puder ser aberto
    }

    // Lê todos os IDs de filmes (ratings) do arquivo de uma vez para evitar múltiplas leituras
    // O parâmetro 0 significa ler todas as linhas disponíveis.
    std::vector<int> allRatings = reader.readMovieIds(0);

    if (allRatings.empty())
    {
        std::cerr << "Nenhum dado foi lido do arquivo. Saindo.\n";
        return 1; // Retorna com código de erro se nenhum dado for lido
    }
    std::cout << "Total de ratings lidos: " << allRatings.size() << std::endl;

    // Mapas para armazenar os resultados agregados de tempo e memória.
    // A chave externa é o nome da estrutura (e.g., "Linear List"), a chave interna é o volume de dados (size_t).
    std::map<std::string, std::map<size_t, double>> resultadosTempoMedio;
    std::map<std::string, std::map<size_t, size_t>> resultadosMemoriaEstimada;

    // Inicializa o objeto PerformanceAnalyzer
    PerformanceAnalyzer analyzer;
    // Define os tamanhos de teste que a análise de desempenho deve usar
    analyzer.setTestSizes(VOLUMES_TESTE); // Chama o novo método setTestSizes

    // Obtém uma lista de informações de fábrica de estruturas do PerformanceAnalyzer.
    // Agora, cada elemento em 'structureFactories' é um struct que contém o nome,
    // se é dinâmica, e uma lambda para criar a estrutura.
    auto structureFactories = analyzer.createStructureFactories(); // Chama o novo método createStructureFactories

    // Loop principal: Itera sobre cada volume de teste pré-definido
    for (size_t currentVolume : VOLUMES_TESTE)
    {
        // Pula o volume de teste se for maior que o número total de dados disponíveis
        if (currentVolume > allRatings.size())
        {
            std::cout << "Pulando volume de " << currentVolume << " elementos, pois é maior que os dados disponíveis (" << allRatings.size() << ").\n";
            continue;
        }

        std::cout << "⏳ Testando com " << currentVolume << " elementos (" << NUM_REPETICOES << " repetições):\n";

        // Loop interno: Itera sobre cada tipo de estrutura de dados a ser testada
        // 'factoryInfo' agora é uma instância de PerformanceAnalyzer::StructureFactoryInfo
        for (const auto &factoryInfo : structureFactories)
        {
            double somaTemposMs = 0.0;                        // Acumulador para a soma dos tempos de execução em milissegundos
            int testesBemSucedidos = 0;                       // Contador de repetições de teste bem-sucedidas
            size_t memoriaAmostra = 0;                        // Armazena a estimativa de memória de uma das execuções (geralmente a primeira bem-sucedida)
            std::string structureName = factoryInfo.typeName; // Obtém o nome da estrutura da fábrica

            std::cout << "   " << structureName << "... " << std::flush; // Imprime o nome da estrutura e força a saída para o console

            // Loop de repetições: Executa o teste NUM_REPETICOES vezes para obter uma média
            for (int k = 0; k < NUM_REPETICOES; ++k)
            {
                // Cria uma nova instância da estrutura usando a lambda da fábrica.
                // Isso garante que cada teste comece com um estado limpo.
                std::unique_ptr<DataStructure> currentStructure = factoryInfo.factory();

                // Executa o teste de desempenho para a estrutura e o volume de dados atual
                PerformanceAnalyzer::PerformanceResult res =
                    analyzer.runPerformanceTest(allRatings, currentStructure, currentVolume);

                if (res.success)
                {
                    // Converte o tempo total de nanosegundos para milissegundos e adiciona ao acumulador
                    somaTemposMs += res.totalTime.count() / 1000000.0;
                    testesBemSucedidos++; // Incrementa o contador de testes bem-sucedidos
                    if (k == 0)           // Na primeira execução bem-sucedida, armazena o uso de memória
                    {
                        memoriaAmostra = res.memoryUsage;
                    }
                }
                else
                {
                    // Se houver falha, imprime um erro e sinaliza que o teste falhou para esta combinação
                    std::cerr << "❌ Erro ou falha na ordenação em uma das repetições para "
                              << structureName << " com " << currentVolume << " elementos!\n";
                    somaTemposMs = -1.0; // Sinaliza falha geral para esta combinação de estrutura/volume
                    memoriaAmostra = 0;
                    break; // Sai do loop de repetições se uma falha ocorrer
                }
            }

            // Calcula a média dos tempos se houve testes bem-sucedidos, ou registra como falha
            if (somaTemposMs != -1.0 && testesBemSucedidos > 0)
            {
                resultadosTempoMedio[structureName][currentVolume] = somaTemposMs / testesBemSucedidos;
                resultadosMemoriaEstimada[structureName][currentVolume] = memoriaAmostra;
                std::cout << "✅ Concluído! Média: ("
                          << std::fixed << std::setprecision(2) << resultadosTempoMedio[structureName][currentVolume] << " ms)\n";
            }
            else
            {
                // Se não houve testes bem-sucedidos ou houve falha sinalizada
                resultadosTempoMedio[structureName][currentVolume] = -1.0; // Sinaliza falha
                resultadosMemoriaEstimada[structureName][currentVolume] = 0;
                if (somaTemposMs != -1.0) // Se não foi uma falha por erro de ordenação, mas por nenhum teste bem-sucedido
                {
                    std::cerr << "❌ Nenhuma repetição bem-sucedida para "
                              << structureName << " com " << currentVolume << " elementos.\n";
                }
            }
        }
        std::cout << std::endl; // Adiciona uma linha em branco após cada volume de teste
    }

    // Exibe a tabela de resumo final com todos os resultados coletados
    exibirTabelaResumoFinal(resultadosTempoMedio, resultadosMemoriaEstimada);

    // Opcionalmente, você pode chamar métodos do analyzer para salvar resultados detalhados em arquivos
    // analyzer.saveResultsToFile("performance_report.txt");
    // analyzer.saveResultsToCSV("performance_results.csv");

    return 0; // Indica que o programa terminou com sucesso
}
