#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#include "radix_sort.h"
#include "counting_sort.h" // Para usar findMax

void radixSort(int *array, int size)
{
    if (!array || size <= 1)
        return;

    // Encontrar o valor máximo usando a função do counting_sort
    int max = findMax(array, size);
    if (max <= 0)
        return; // Proteção contra valores inválidos

    // Aplicar counting sort para cada dígito
    // exp é 10^i onde i é o dígito atual (1, 10, 100, ...)
    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        countingSortByDigit(array, size, exp);
    }
}

// Função auxiliar para counting sort baseado em um dígito específico
void countingSortByDigit(int *array, int size, int exp)
{
    if (!array || size <= 1)
        return;

    int *output = (int *)malloc(size * sizeof(int));
    if (!output)
    {
        printf("Erro: falha na alocação de memória em countingSortByDigit\n");
        return;
    }

    int count[10] = {0}; // Array para contar dígitos 0-9

    // Contar occorrências de cada dígito na posição exp
    for (int i = 0; i < size; i++)
    {
        int digit = (array[i] / exp) % 10;
        count[digit]++;
    }

    // Modificar count[i] para que contenha a posição atual
    // deste dígito no array output (soma cumulativa)
    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    // Construir o array output
    // Processar de trás para frente para manter estabilidade
    for (int i = size - 1; i >= 0; i--)
    {
        int digit = (array[i] / exp) % 10;
        output[count[digit] - 1] = array[i];
        count[digit]--;
    }

    // Copiar o array output de volta para o array original
    for (int i = 0; i < size; i++)
    {
        array[i] = output[i];
    }

    free(output);
}

// Função adicional para verificar se o radix sort funcionou corretamente
int verifyRadixSort(int *array, int size)
{
    if (!array || size <= 1)
        return 1;

    for (int i = 1; i < size; i++)
    {
        if (array[i] < array[i - 1])
        {
            return 0; // Não está ordenado
        }
    }
    return 1; // Está ordenado
}

// Função para imprimir estatísticas do radix sort
void printRadixSortStats(int *array, int size)
{
    if (!array || size <= 0)
        return;

    int max = findMax(array, size);
    int numDigits = 0;
    int temp = max;

    // Contar número de dígitos
    while (temp > 0)
    {
        numDigits++;
        temp /= 10;
    }

    printf("Radix Sort Stats - Max: %d, Dígitos: %d, Passes: %d\n",
           max, numDigits, numDigits);
}