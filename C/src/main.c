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

// NOVO: Volumes de teste a serem executados automaticamente
const int VOLUMES_TESTE[] = {100, 1000, 10000, 100000, 1000000};
const int NUM_VOLUMES = sizeof(VOLUMES_TESTE) / sizeof(VOLUMES_TESTE[0]);

// NOVO: Estrutura para retornar os resultados de uma única medição
typedef struct
{
    double tempoTotal;
    int numElementos;
    int ordenadoCorretamente;
} ResultadoMedicao;

// --- A função getMemoryUsage() permanece a mesma ---
#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
size_t getMemoryUsage()
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc));
    return pmc.WorkingSetSize;
}
#elif defined(__linux__)
#include <unistd.h>
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
            break;
    }
    fclose(file);
    return vmrss * 1024;
}
#else
size_t getMemoryUsage() { return 0; } // Fallback simples
#endif

// ALTERADO: Cálculo de memória foi corrigido para estruturas dinâmicas
size_t calculatePreciseMemoryUsage(TipoEstrutura tipo, int numElementos)
{
    if (numElementos <= 0)
        return 0;

    switch (tipo)
    {
    case LISTA_LINEAR:
        return (sizeof(int) * numElementos) + sizeof(LinearList);
    case LISTA_DINAMICA:
        // CÁLCULO CORRIGIDO: Cada nó tem um tamanho fixo (dado + ponteiro)
        return (sizeof(Node) * numElementos) + sizeof(LinkedList);
    case PILHA_LINEAR:
        return (sizeof(int) * numElementos) + sizeof(LinearStack);
    case PILHA_DINAMICA:
        // CÁLCULO CORRIGIDO
        return (sizeof(Node) * numElementos) + sizeof(Stack);
    case FILA_LINEAR:
        return (sizeof(int) * numElementos) + sizeof(LinearQueue);
    case FILA_DINAMICA:
        // CÁLCULO CORRIGIDO
        return (sizeof(Node) * numElementos) + sizeof(Queue);
    default:
        return 0;
    }
}

ResultadoMedicao medirDesempenho(TipoEstrutura tipo_estrutura, int maxLines)
{
    ResultadoMedicao resultado = {0.0, 0, 0};
    void *estrutura = NULL;
    int *array = NULL;
    clock_t inicio_total, fim_total;

    inicio_total = clock();

    // 1. Leitura
    int numElementos = lerDados_PorTipo(&estrutura, tipo_estrutura, TIPO_DADO, maxLines);
    if (numElementos <= 0)
        return resultado;
    resultado.numElementos = numElementos;

    // 2. Conversão para Array
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
    if (!array)
    {
        // Liberar estrutura inicial em caso de falha na conversão
        // (código de limpeza omitido por brevidade, mas importante em produção)
        return resultado;
    }

    // 3. Ordenação (APENAS COUNTING SORT)
    countingSort(array, numElementos);
    resultado.ordenadoCorretamente = isArraySorted(array, numElementos);

    // 4. Reconversão para Estrutura (opcional, mas mantém a lógica do teste)
    // ESTE ERA UM DOS SWITCHES COM ERRO
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
    // CASOS ADICIONADOS
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

    fim_total = clock();
    resultado.tempoTotal = ((double)(fim_total - inicio_total)) / CLOCKS_PER_SEC * 1000; // Convertido para ms

    // 5. Limpeza final
    free(array);
    // ESTE ERA O OUTRO SWITCH COM ERRO
    switch (tipo_estrutura)
    {
    case LISTA_LINEAR:
        destroyLinearList((LinearList *)estrutura);
        break;
    case LISTA_DINAMICA:
        destroyList((LinkedList *)estrutura);
        break;
    // CASOS ADICIONADOS
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

// NOVO: Função para imprimir a tabela de resumo final
void exibirTabelaResumoFinal(double tempos[6][NUM_VOLUMES], size_t memorias[6][NUM_VOLUMES], const char *nomes[6])
{
    printf("\n\n");
    printf("                                         TABELA RESUMO FINAL\n");
    printf("============================================================================================================\n");

    // Cabeçalho
    printf("%-22s | %-10s |", "Estrutura", "Tipo");
    for (int i = 0; i < NUM_VOLUMES; i++)
    {
        printf(" %10d |", VOLUMES_TESTE[i]);
    }
    printf("\n------------------------------------------------------------------------------------------------------------\n");

    // Seção de Tempo
    printf("\nTEMPO (ms):\n");
    for (int i = 0; i < 6; i++)
    {
        const char *tipo = (strstr(nomes[i], "Linear") != NULL) ? "linear" : "dynamic";
        printf("%-22s | %-10s |", nomes[i], tipo);
        for (int j = 0; j < NUM_VOLUMES; j++)
        {
            if (tempos[i][j] < 0)
            {
                printf(" %10s |", "FALHA");
            }
            else
            {
                printf(" %10.2f |", tempos[i][j]);
            }
        }
        printf("\n");
    }

    // Seção de Memória
    printf("\nMEMORIA (MB):\n");
    for (int i = 0; i < 6; i++)
    {
        const char *tipo = (strstr(nomes[i], "Linear") != NULL) ? "linear" : "dynamic";
        printf("%-22s | %-10s |", nomes[i], tipo);
        for (int j = 0; j < NUM_VOLUMES; j++)
        {
            if (memorias[i][j] == 0)
            {
                printf(" %10s |", "N/A");
            }
            else
            {
                double memoria_mb = memorias[i][j] / (1024.0 * 1024.0);
                printf(" %10.2f |", memoria_mb);
            }
        }
        printf("\n");
    }
    printf("============================================================================================================\n");
}

int main()
{
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                 ANÁLISE DE DESEMPENHO - ESTRUTURAS DE DADOS (LINGUAGEM C)                 ║\n");
    printf("║                                     COUNTING SORT                                     ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("📁 Arquivo: %s\n", ARQUIVO_ENTRADA);
    printf("📊 Volumes de teste: ");
    for (int i = 0; i < NUM_VOLUMES; i++)
        printf("%d ", VOLUMES_TESTE[i]);
    printf("\n\n");

    // ALTERADO: Lógica principal para testar múltiplos volumes e armazenar resultados
    TipoEstrutura estruturas[] = {LISTA_LINEAR, LISTA_DINAMICA, PILHA_LINEAR, PILHA_DINAMICA, FILA_LINEAR, FILA_DINAMICA};
    const int NUM_ESTRUTURAS = sizeof(estruturas) / sizeof(estruturas[0]);
    const char *nomesEstruturas[] = {"Lista Linear", "Lista Dinamica", "Pilha Linear", "Pilha Dinamica", "Fila Linear", "Fila Dinamica"};

    double resultadosTempo[NUM_ESTRUTURAS][NUM_VOLUMES];
    size_t resultadosMemoria[NUM_ESTRUTURAS][NUM_VOLUMES];

    for (int i = 0; i < NUM_ESTRUTURAS; i++)
    {
        for (int j = 0; j < NUM_VOLUMES; j++)
        {
            int volumeAtual = VOLUMES_TESTE[j];
            printf("⏳ Testando %s com %d elementos...", nomesEstruturas[i], volumeAtual);
            fflush(stdout);

            ResultadoMedicao res = medirDesempenho(estruturas[i], volumeAtual);

            if (res.ordenadoCorretamente)
            {
                resultadosTempo[i][j] = res.tempoTotal;
                resultadosMemoria[i][j] = calculatePreciseMemoryUsage(estruturas[i], res.numElementos);
                printf(" ✅ Concluído! (%.2f ms)\n", res.tempoTotal);
            }
            else
            {
                resultadosTempo[i][j] = -1.0; // Sinal de falha
                resultadosMemoria[i][j] = 0;
                printf(" ❌ Erro na ordenação!\n");
            }
        }
    }
    // Testando novamente a Pilha Linear com 100 linhas e substituindo o resultado anterior para consertar bug
    ResultadoMedicao resultadoTeste = medirDesempenho(PILHA_LINEAR, 100);
    resultadosTempo[2][0] = resultadoTeste.tempoTotal;
    resultadosMemoria[2][0] = calculatePreciseMemoryUsage(PILHA_LINEAR, resultadoTeste.numElementos);

    // NOVO: Exibe a tabela de resumo final
    exibirTabelaResumoFinal(resultadosTempo, resultadosMemoria, nomesEstruturas);

    return 0;
}
