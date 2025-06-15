#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "data_structures.h"
#include "ratings_reader.h"
#include "radix_sort.h"
#include "converters.h"
#include "counting_sort.h"
#include "config.h"

// Estrutura para armazenar resultados de cada teste
typedef struct
{
    char nome[30];
    double tempoLeitura;
    double tempoConversao;
    double tempoOrdenacao;
    double tempoReconversao;
    double tempoTotal;
    size_t memoriaUsada;
    int numElementos;
    int ordenadoCorretamente;
} ResultadoTeste;

// Variáveis globais para tracking de memória
static size_t memoriaAtual = 0;
static size_t memoriaMaxima = 0;
static size_t memoriaInicial = 0;

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>

// Função para obter uso de memória no Windows
size_t getMemoryUsage()
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc)))
    {
        return pmc.WorkingSetSize;
    }
    return 0;
}

#elif defined(__linux__)
#include <unistd.h>

// Função para obter uso de memória no Linux
size_t getMemoryUsage()
{
    FILE *file = fopen("/proc/self/status", "r");
    if (!file)
        return 0;

    char line[128];
    size_t vmrss = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "VmRSS: %zu kB", &vmrss) == 1)
        {
            break;
        }
    }
    fclose(file);
    return vmrss * 1024; // Converter de KB para bytes
}

#endif

// Função para resetar contadores de memória
void resetMemoryTracking()
{
    memoriaAtual = 0;
    memoriaMaxima = 0;
    memoriaInicial = getMemoryUsage();
}

// Função para estimar uso de memória por tipo de estrutura
size_t estimateMemoryUsage(TipoEstrutura tipo, int numElementos)
{
    size_t baseSize = 0;

    switch (tipo)
    {
    case LISTA_LINEAR:
        // Array estático + estrutura de controle
        baseSize = sizeof(int) * numElementos + sizeof(LinearList);
        break;
    case LISTA_DINAMICA:
        // Nós da lista ligada (cada nó tem dados + ponteiro)
        baseSize = (sizeof(int) + sizeof(void *)) * numElementos + sizeof(LinkedList);
        break;
    case PILHA_LINEAR:
        // Array estático + estrutura de controle
        baseSize = sizeof(int) * numElementos + sizeof(LinearStack);
        break;
    case PILHA_DINAMICA:
        // Nós da pilha (cada nó tem dados + ponteiro)
        baseSize = (sizeof(int) + sizeof(void *)) * numElementos + sizeof(Stack);
        break;
    case FILA_LINEAR:
        // Array circular + estrutura de controle
        baseSize = sizeof(int) * numElementos + sizeof(LinearQueue);
        break;
    case FILA_DINAMICA:
        // Nós da fila (cada nó tem dados + ponteiro)
        baseSize = (sizeof(int) + sizeof(void *)) * numElementos + sizeof(Queue);
        break;
    }

    // Adicionar overhead do array temporário para conversão/ordenação
    baseSize += sizeof(int) * numElementos;

    return baseSize;
}

// Função para obter uso atual de memória
size_t getCurrentMemoryUsage()
{
    size_t atual = getMemoryUsage();
    if (atual > memoriaInicial)
    {
        return atual - memoriaInicial;
    }
    return 0;
}

// Função para medir tempo de execução
double measureExecutionTime(clock_t start, clock_t end)
{
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

// Função para formatar bytes em unidades legíveis
void formatBytes(size_t bytes, char *buffer)
{
    if (bytes < 1024)
    {
        sprintf(buffer, "%zu B", bytes);
    }
    else if (bytes < 1024 * 1024)
    {
        sprintf(buffer, "%.2f KB", bytes / 1024.0);
    }
    else if (bytes < 1024 * 1024 * 1024)
    {
        sprintf(buffer, "%.2f MB", bytes / (1024.0 * 1024.0));
    }
    else
    {
        sprintf(buffer, "%.2f GB", bytes / (1024.0 * 1024.0 * 1024.0));
    }
}

// Função para testar uma estrutura específica
ResultadoTeste testarEstrutura(TipoEstrutura tipo_estrutura, int maxLines)
{
    ResultadoTeste resultado;
    strcpy(resultado.nome, getNomeEstrutura(tipo_estrutura));
    resultado.ordenadoCorretamente = 0;

    // Reset memory tracking e medir memória inicial
    resetMemoryTracking();
    size_t memoriaAntes = getMemoryUsage();

    void *estrutura = NULL;
    clock_t inicio, fim;

    // 1. LEITURA
    inicio = clock();
    int numElementos = lerDados_PorTipo(&estrutura, tipo_estrutura, TIPO_DADO, maxLines);
    fim = clock();
    resultado.tempoLeitura = measureExecutionTime(inicio, fim);
    resultado.numElementos = numElementos;

    if (numElementos <= 0)
    {
        printf("Erro na leitura dos dados para %s!\n", resultado.nome);
        resultado.tempoConversao = resultado.tempoOrdenacao = resultado.tempoReconversao = resultado.tempoTotal = 0;
        resultado.memoriaUsada = 0;
        return resultado;
    }

    // 2. CONVERSÃO PARA ARRAY
    inicio = clock();
    int *array = NULL;

    switch (tipo_estrutura)
    {
    case LISTA_LINEAR:
        array = linearListToArray((LinearList *)estrutura);
        break;
    case LISTA_DINAMICA:
        array = listToArray((LinkedList *)estrutura);
        break;
    case PILHA_LINEAR:
        array = linearStackToArray((LinearStack *)estrutura);
        break;
    case PILHA_DINAMICA:
        array = stackToArray((Stack *)estrutura);
        break;
    case FILA_LINEAR:
        array = linearQueueToArray((LinearQueue *)estrutura);
        break;
    case FILA_DINAMICA:
        array = queueToArray((Queue *)estrutura);
        break;
    }
    fim = clock();
    resultado.tempoConversao = measureExecutionTime(inicio, fim);

    if (!array)
    {
        printf("Erro na conversão para array para %s!\n", resultado.nome);
        resultado.tempoOrdenacao = resultado.tempoReconversao = resultado.tempoTotal = 0;
        resultado.memoriaUsada = 0;
        return resultado;
    }

    // 3. ORDENAÇÃO
    inicio = clock();
    switch (METODO_ORDENACAO)
    {
    case COUNTING_SORT:
        countingSort(array, numElementos);
        break;
    case RADIX_SORT:
        radixSort(array, numElementos);
        break;
    default:
        printf("Método de ordenação desconhecido!\n");
        free(array);
        resultado.tempoOrdenacao = resultado.tempoReconversao = resultado.tempoTotal = 0;
        resultado.memoriaUsada = 0;
        return resultado;
    }
    fim = clock();
    resultado.tempoOrdenacao = measureExecutionTime(inicio, fim);

    // Medir memória máxima durante processamento
    size_t memoriaMaximaProcessamento = getMemoryUsage();

    // Verificar se está ordenado
    resultado.ordenadoCorretamente = isArraySorted(array, numElementos);

    // 4. RECONVERSÃO PARA ESTRUTURA ORIGINAL
    inicio = clock();

    // Liberar estrutura original
    switch (tipo_estrutura)
    {
    case LISTA_LINEAR:
        destroyLinearList((LinearList *)estrutura);
        estrutura = arrayToLinearList(array, numElementos);
        break;
    case LISTA_DINAMICA:
        destroyList((LinkedList *)estrutura);
        estrutura = arrayToList(array, numElementos);
        break;
    case PILHA_LINEAR:
        destroyLinearStack((LinearStack *)estrutura);
        estrutura = arrayToLinearStack(array, numElementos);
        break;
    case PILHA_DINAMICA:
        destroyStack((Stack *)estrutura);
        estrutura = arrayToStack(array, numElementos);
        break;
    case FILA_LINEAR:
        destroyLinearQueue((LinearQueue *)estrutura);
        estrutura = arrayToLinearQueue(array, numElementos);
        break;
    case FILA_DINAMICA:
        destroyQueue((Queue *)estrutura);
        estrutura = arrayToQueue(array, numElementos);
        break;
    }

    fim = clock();
    resultado.tempoReconversao = measureExecutionTime(inicio, fim);

    // Calcular tempo total e memória usada
    resultado.tempoTotal = resultado.tempoLeitura + resultado.tempoConversao +
                           resultado.tempoOrdenacao + resultado.tempoReconversao;

    // Calcular uso de memória (diferença entre máxima e inicial, ou estimativa)
    if (memoriaMaximaProcessamento > memoriaAntes)
    {
        resultado.memoriaUsada = memoriaMaximaProcessamento - memoriaAntes;
    }
    else
    {
        // Fallback: usar estimativa baseada no tipo de estrutura
        resultado.memoriaUsada = estimateMemoryUsage(tipo_estrutura, numElementos);
    }

    // Limpar memória
    free(array);

    switch (tipo_estrutura)
    {
    case LISTA_LINEAR:
        destroyLinearList((LinearList *)estrutura);
        break;
    case LISTA_DINAMICA:
        destroyList((LinkedList *)estrutura);
        break;
    case PILHA_LINEAR:
        destroyLinearStack((LinearStack *)estrutura);
        break;
    case PILHA_DINAMICA:
        destroyStack((Stack *)estrutura);
        break;
    case FILA_LINEAR:
        destroyLinearQueue((LinearQueue *)estrutura);
        break;
    case FILA_DINAMICA:
        destroyQueue((Queue *)estrutura);
        break;
    }

    return resultado;
}

// Função para imprimir linha separadora
void printSeparator(int width)
{
    for (int i = 0; i < width; i++)
    {
        printf("-");
    }
    printf("\n");
}

// Função para imprimir tabela de resultados
void printResultsTable(ResultadoTeste resultados[], int numResultados)
{
    const int TABLE_WIDTH = 140;

    printf("\n");
    printSeparator(TABLE_WIDTH);
    printf("| %-18s | %-10s | %-10s | %-10s | %-10s | %-10s | %-12s | %-8s | %-8s |\n",
           "ESTRUTURA", "LEITURA", "CONVERSAO", "ORDENACAO", "RECONVER", "TOTAL", "MEMORIA", "ELEMENTOS", "STATUS");
    printSeparator(TABLE_WIDTH);

    for (int i = 0; i < numResultados; i++)
    {
        char memStr[20];
        formatBytes(resultados[i].memoriaUsada, memStr);

        printf("| %-18s | %8.4fs | %8.4fs | %8.4fs | %8.4fs | %8.4fs | %12s | %8d | %8s |\n",
               resultados[i].nome,
               resultados[i].tempoLeitura,
               resultados[i].tempoConversao,
               resultados[i].tempoOrdenacao,
               resultados[i].tempoReconversao,
               resultados[i].tempoTotal,
               memStr,
               resultados[i].numElementos,
               resultados[i].ordenadoCorretamente ? "OK" : "ERRO");
    }

    printSeparator(TABLE_WIDTH);
}

// Função para imprimir estatísticas resumidas
void printSummaryStats(ResultadoTeste resultados[], int numResultados)
{
    if (numResultados == 0)
        return;

    // Encontrar melhor e pior desempenho
    int melhorTempo = 0, piorTempo = 0;
    int melhorMemoria = 0, piorMemoria = 0;

    for (int i = 1; i < numResultados; i++)
    {
        if (resultados[i].tempoTotal < resultados[melhorTempo].tempoTotal)
        {
            melhorTempo = i;
        }
        if (resultados[i].tempoTotal > resultados[piorTempo].tempoTotal)
        {
            piorTempo = i;
        }
        if (resultados[i].memoriaUsada < resultados[melhorMemoria].memoriaUsada)
        {
            melhorMemoria = i;
        }
        if (resultados[i].memoriaUsada > resultados[piorMemoria].memoriaUsada)
        {
            piorMemoria = i;
        }
    }

    printf("\n╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════\n");
    printf("║                                                                                          RESUMO ESTATÍSTICO                                                                                         ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════\n");

    char memMelhor[20], memPior[20];
    formatBytes(resultados[melhorMemoria].memoriaUsada, memMelhor);
    formatBytes(resultados[piorMemoria].memoriaUsada, memPior);

    printf("║ 🏆 MELHOR TEMPO:     %-20s (%.6f s)                                                                                                                                                                    ║\n",
           resultados[melhorTempo].nome, resultados[melhorTempo].tempoTotal);
    printf("║ 🐌 PIOR TEMPO:       %-20s (%.6f s)                                                                                                                                                                    ║\n",
           resultados[piorTempo].nome, resultados[piorTempo].tempoTotal);
    printf("║ 💾 MENOR MEMÓRIA:    %-20s (%s)                                                                                                                                                                        ║\n",
           resultados[melhorMemoria].nome, memMelhor);
    printf("║ 🔥 MAIOR MEMÓRIA:    %-20s (%s)                                                                                                                                                                        ║\n",
           resultados[piorMemoria].nome, memPior);

    // Calcular médias
    double tempoMedio = 0;
    size_t memoriaMedia = 0;
    for (int i = 0; i < numResultados; i++)
    {
        tempoMedio += resultados[i].tempoTotal;
        memoriaMedia += resultados[i].memoriaUsada;
    }
    tempoMedio /= numResultados;
    memoriaMedia /= numResultados;

    char memMedia[20];
    formatBytes(memoriaMedia, memMedia);

    printf("║ 📊 TEMPO MÉDIO:      %.6f s                                                                                                                                                                            ║\n", tempoMedio);
    printf("║ 📊 MEMÓRIA MÉDIA:    %s                                                                                                                                                                               ║\n", memMedia);
    printf("\n");
}

int main()
{
    printf("\n");
    printf("║                                                                                  ANÁLISE DE DESEMPENHO - ESTRUTURAS DE DADOS                                                                                  ║\n");
    printf("║                                                                                         %s                                                                                        ║\n",
           METODO_ORDENACAO == COUNTING_SORT ? "COUNTING SORT" : "RADIX SORT");
    printf("\n");

    printf("📁 Arquivo: %s\n", ARQUIVO_ENTRADA);
    printf("📊 Máximo de linhas: %d\n", maxlinhas);
    printf("🔄 Testando todas as estruturas de dados...\n");

    // Array para armazenar resultados
    ResultadoTeste resultados[6];
    int numResultados = 0;

    // Testar todas as estruturas
    TipoEstrutura estruturas[] = {LISTA_LINEAR, LISTA_DINAMICA, PILHA_LINEAR, PILHA_DINAMICA, FILA_LINEAR, FILA_DINAMICA};
    int numEstruturas = sizeof(estruturas) / sizeof(estruturas[0]);

    for (int i = 0; i < numEstruturas; i++)
    {
        printf("\n⏳ Testando %s...", getNomeEstrutura(estruturas[i]));
        fflush(stdout);

        resultados[numResultados] = testarEstrutura(estruturas[i], maxlinhas);
        numResultados++;

        if (resultados[numResultados - 1].ordenadoCorretamente)
        {
            printf(" ✅ Concluído!");
        }
        else
        {
            printf(" ❌ Erro na ordenação!");
        }
    }

    // Imprimir tabela de resultados
    printResultsTable(resultados, numResultados);

    // Imprimir estatísticas resumidas
    printSummaryStats(resultados, numResultados);

    return 0;
}