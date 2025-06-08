#include <stdio.h>
#include <stdlib.h>
#include "tests.h"
#include "data_structures.h"
#include "converters.h"
#include "counting_sort.h"
#include "utils.h"

void testCountingSortWithDifferentStructures()
{
    printf("=== TESTE DO COUNTING SORT COM DIFERENTES ESTRUTURAS ===\n\n");

    // Dados de teste
    int testData[] = {4, 2, 2, 8, 3, 3, 1};
    int size = sizeof(testData) / sizeof(testData[0]);

    printf("Dados originais: ");
    printArray(testData, size, "Array");

    // 1. TESTE COM LISTA LIGADA
    printf("\n--- Teste com Lista Ligada ---\n");
    LinkedList *list = createList();
    for (int i = 0; i < size; i++)
    {
        insertList(list, testData[i]);
    }
    printList(list, "Lista original");

    int *arrayFromList = listToArray(list);
    countingSort(arrayFromList, size);

    LinkedList *sortedList = arrayToList(arrayFromList, size);
    printList(sortedList, "Lista ordenada");

    free(arrayFromList);
    destroyList(list);
    destroyList(sortedList);

    // 2. TESTE COM PILHA
    printf("\n--- Teste com Pilha ---\n");
    Stack *stack = createStack(size);
    for (int i = 0; i < size; i++)
    {
        push(stack, testData[i]);
    }

    int *arrayFromStack = stackToArray(stack);
    printf("Pilha original: ");
    printArray(arrayFromStack, stack->top + 1, "");

    countingSort(arrayFromStack, stack->top + 1);

    Stack *sortedStack = arrayToStack(arrayFromStack, stack->top + 1);
    int *sortedStackArray = stackToArray(sortedStack);
    printf("Pilha ordenada: ");
    printArray(sortedStackArray, sortedStack->top + 1, "");

    free(arrayFromStack);
    free(sortedStackArray);
    destroyStack(stack);
    destroyStack(sortedStack);

    // 3. TESTE COM FILA
    printf("\n--- Teste com Fila ---\n");
    Queue *queue = createQueue(size);
    for (int i = 0; i < size; i++)
    {
        enqueue(queue, testData[i]);
    }

    int *arrayFromQueue = queueToArray(queue);
    printf("Fila original: ");
    printArray(arrayFromQueue, queue->size, "");

    countingSort(arrayFromQueue, queue->size);

    Queue *sortedQueue = arrayToQueue(arrayFromQueue, queue->size);
    int *sortedQueueArray = queueToArray(sortedQueue);
    printf("Fila ordenada: ");
    printArray(sortedQueueArray, sortedQueue->size, "");

    free(arrayFromQueue);
    free(sortedQueueArray);
    destroyQueue(queue);
    destroyQueue(sortedQueue);
}

void testCountingSortCorrectnessSmall()
{
    printf("\n=== TESTE DE CORREÇÃO - CASOS PEQUENOS ===\n");

    // Teste 1: Array vazio
    int *empty = NULL;
    countingSort(empty, 0);
    printf("Array vazio: OK\n");

    // Teste 2: Array com um elemento
    int single[] = {5};
    countingSort(single, 1);
    printf("Array unitário: %d (OK)\n", single[0]);

    // Teste 3: Array já ordenado
    int sorted[] = {1, 2, 3, 4, 5};
    countingSort(sorted, 5);
    printf("Array já ordenado: ");
    printArray(sorted, 5, "");
    printf("Está ordenado: %s\n", isArraySorted(sorted, 5) ? "Sim" : "Não");

    // Teste 4: Array com elementos repetidos
    int duplicates[] = {3, 1, 3, 1, 2, 2};
    countingSort(duplicates, 6);
    printf("Array com duplicatas: ");
    printArray(duplicates, 6, "");
    printf("Está ordenado: %s\n", isArraySorted(duplicates, 6) ? "Sim" : "Não");
}

void performanceTest(int size)
{
    printf("\n=== TESTE DE PERFORMANCE (Size: %d) ===\n", size);

    // Teste com dados aleatórios
    int *randomData = generateRandomArray(size, 1000);
    double timeRandom = measureTime(countingSort, randomData, size);
    printf("Dados aleatórios: %.6f segundos\n", timeRandom);
    printf("Está ordenado: %s\n", isArraySorted(randomData, size) ? "Sim" : "Não");

    free(randomData);
}

void performanceTestAllCases(int size)
{
    printf("\n=== TESTE DE PERFORMANCE COMPLETO (Size: %d) ===\n", size);

    // Caso 1: Dados aleatórios
    int *randomData = generateRandomArray(size, size / 10);
    double timeRandom = measureTime(countingSort, randomData, size);
    printf("Aleatório: %.6f s", timeRandom);

    // Caso 2: Dados já ordenados
    int *sortedData = generateSortedArray(size);
    double timeSorted = measureTime(countingSort, sortedData, size);
    printf(" | Ordenado: %.6f s", timeSorted);

    // Caso 3: Dados inversamente ordenados
    int *reverseData = generateReverseSortedArray(size);
    double timeReverse = measureTime(countingSort, reverseData, size);
    printf(" | Reverso: %.6f s\n", timeReverse);

    free(randomData);
    free(sortedData);
    free(reverseData);
}

void runAllTests()
{
    printf("COUNTING SORT - TESTES COMPLETOS\n");
    printf("=================================\n");

    // Testes funcionais
    testCountingSortWithDifferentStructures();
    testCountingSortCorrectnessSmall();

    // Testes de performance
    performanceTest(1000);
    performanceTestAllCases(10000);
    performanceTestAllCases(100000);

    printf("\n=== ANÁLISE DE COMPLEXIDADE ===\n");
    printf("Complexidade de Tempo: O(n + k), onde k é o range dos valores\n");
    printf("Complexidade de Espaço: O(k) para o array auxiliar\n");
    printf("Estabilidade: Implementação estável disponível\n");
    printf("Tipo: Algoritmo não-comparativo\n");
    printf("Limitação: Funciona apenas com inteiros não-negativos\n");
}
