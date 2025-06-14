#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "data_structures.h"
#include "ratings_reader.h"
#include "radix_sort.h"
#include "converters.h"
#include "counting_sort.h"
#include "config.h"

// Função para medir tempo de execução
double measureExecutionTime(clock_t start, clock_t end)
{
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

// Função para testar uma estrutura específica
void testarEstrutura(TipoEstrutura tipo_estrutura, int maxLines)
{
    printf("\n========== TESTANDO %s ==========\n", getNomeEstrutura(tipo_estrutura));

    void *estrutura = NULL;
    clock_t inicio, fim;
    double tempoLeitura, tempoConversao, tempoOrdenacao, tempoReconversao;

    // 1. LEITURA
    inicio = clock();
    int numElementos = lerDados_PorTipo(&estrutura, tipo_estrutura, TIPO_DADO, maxLines);
    fim = clock();
    tempoLeitura = measureExecutionTime(inicio, fim);

    if (numElementos <= 0)
    {
        printf("Erro na leitura dos dados!\n");
        return;
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
    tempoConversao = measureExecutionTime(inicio, fim);

    if (!array)
    {
        printf("Erro na conversão para array!\n");
        return;
    }

    // 3. ORDENAÇÃO
    inicio = clock();
    // Escolher o método de ordenação
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
        return;
    }
    fim = clock();
    tempoOrdenacao = measureExecutionTime(inicio, fim);

    // Verificar se está ordenado
    if (isArraySorted(array, numElementos))
    {
        printf("-> ✓ Array foi ordenado corretamente!\n");
    }
    else
    {
        printf("-> ✗ ERRO: Array não foi ordenado!\n");
    }

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
    tempoReconversao = measureExecutionTime(inicio, fim);

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
}

int main()
{
    printf("\n\n\n\n=== TESTE DE %s COM DIFERENTES ESTRUTURAS ===\n", METODO_ORDENACAO == COUNTING_SORT ? "COUNTING SORT" : "RADIX SORT");
    printf("Arquivo: %s\n", ARQUIVO_ENTRADA);
    printf("Máximo de linhas: %d\n", maxlinhas);

    // Testar estrutura ativa definida no config.h
    /*printf("\nTestando estrutura ativa: %s\n", getNomeEstrutura(ESTRUTURA_ATIVA));
    testarEstrutura(ESTRUTURA_ATIVA, maxlinhas);*/

    // Para testar todas as estruturas, descomente as linhas abaixo:

    printf("\n=== TESTANDO TODAS AS ESTRUTURAS ===\n");

    testarEstrutura(LISTA_LINEAR, maxlinhas);
    testarEstrutura(LISTA_DINAMICA, maxlinhas);
    testarEstrutura(PILHA_LINEAR, maxlinhas);
    testarEstrutura(PILHA_DINAMICA, maxlinhas);
    testarEstrutura(FILA_LINEAR, maxlinhas);
    testarEstrutura(FILA_DINAMICA, maxlinhas);

    return 0;
}