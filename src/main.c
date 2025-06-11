#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "data_structures.h"
#include "ratings_reader.h"
#include "converters.h"
#include "counting_sort.h"
#include "config.h"

// Função para medir tempo de execução
double measureExecutionTime(clock_t start, clock_t end)
{
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

// Função para testar uma estrutura específica
void testarEstrutura(TipoEstrutura tipo, int maxLines)
{
    printf("\n========== TESTANDO %s ==========\n", getNomeEstrutura(tipo));

    void *estrutura = NULL;
    clock_t inicio, fim;
    double tempoLeitura, tempoConversao, tempoOrdenacao, tempoReconversao;

    // 1. LEITURA
    printf("1. Lendo dados do CSV...\n");
    inicio = clock();
    int numElementos = lerMovieIds_PorTipo(&estrutura, tipo, maxLines);
    fim = clock();
    tempoLeitura = measureExecutionTime(inicio, fim);

    if (numElementos <= 0)
    {
        printf("Erro na leitura dos dados!\n");
        return;
    }

    printf("   -> %d elementos lidos em %.6f segundos\n", numElementos, tempoLeitura);

    // 2. CONVERSÃO PARA ARRAY
    printf("2. Convertendo para array...\n");
    inicio = clock();
    int *array = NULL;

    switch (tipo)
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
    tempoConversao = measureExecutionTime(inicio, fim);

    if (!array)
    {
        printf("Erro na conversão para array!\n");
        return;
    }

    printf("   -> Conversão concluída em %.6f segundos\n", tempoConversao);

    // 3. ORDENAÇÃO
    printf("3. Executando Counting Sort...\n");
    inicio = clock();
    countingSort(array, numElementos);
    fim = clock();
    tempoOrdenacao = measureExecutionTime(inicio, fim);

    printf("   -> Ordenação concluída em %.6f segundos\n", tempoOrdenacao);

    // Verificar se está ordenado
    if (isArraySorted(array, numElementos))
    {
        printf("   -> ✓ Array está ordenado corretamente!\n");
    }
    else
    {
        printf("   -> ✗ ERRO: Array não está ordenado!\n");
    }

    // 4. RECONVERSÃO PARA ESTRUTURA ORIGINAL
    printf("4. Convertendo de volta para a estrutura original...\n");
    inicio = clock();

    // Liberar estrutura original
    switch (tipo)
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
    tempoReconversao = measureExecutionTime(inicio, fim);

    printf("   -> Reconversão concluída em %.6f segundos\n", tempoReconversao);

    // 5. RESULTADOS FINAIS
    double tempoTotal = tempoLeitura + tempoConversao + tempoOrdenacao + tempoReconversao;

    printf("\n--- RESUMO DOS TEMPOS ---\n");
    printf("Leitura:      %.6f s (%.2f%%)\n", tempoLeitura, (tempoLeitura / tempoTotal) * 100);
    printf("Conversão:    %.6f s (%.2f%%)\n", tempoConversao, (tempoConversao / tempoTotal) * 100);
    printf("Ordenação:    %.6f s (%.2f%%)\n", tempoOrdenacao, (tempoOrdenacao / tempoTotal) * 100);
    printf("Reconversão:  %.6f s (%.2f%%)\n", tempoReconversao, (tempoReconversao / tempoTotal) * 100);
    printf("TOTAL:        %.6f s\n", tempoTotal);

    // Limpar memória
    free(array);

    switch (tipo)
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
}

int main()
{
    printf("=== TESTE DE COUNTING SORT COM DIFERENTES ESTRUTURAS ===\n");
    printf("Arquivo: %s\n", ARQUIVO_ENTRADA);
    printf("Máximo de linhas: %d\n", maxlinhas);

    // Testar estrutura ativa definida no config.h
    printf("\nTestando estrutura ativa: %s\n", getNomeEstrutura(ESTRUTURA_ATIVA));
    testarEstrutura(ESTRUTURA_ATIVA, maxlinhas);

    // Para testar todas as estruturas, descomente as linhas abaixo:
    /*
    printf("\n=== TESTANDO TODAS AS ESTRUTURAS ===\n");

    testarEstrutura(LISTA_LINEAR, maxlinhas);
    testarEstrutura(LISTA_DINAMICA, maxlinhas);
    testarEstrutura(PILHA_LINEAR, maxlinhas);
    testarEstrutura(PILHA_DINAMICA, maxlinhas);
    testarEstrutura(FILA_LINEAR, maxlinhas);
    testarEstrutura(FILA_DINAMICA, maxlinhas);
    */

    return 0;
}