#include <stdlib.h>
#include <string.h>
#include "counting_sort.h"

int findMax(int *array, int size)
{
    if (size <= 0)
        return 0;

    int max = array[0];
    for (int i = 1; i < size; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}

int isArraySorted(int *array, int size)
{
    for (int i = 1; i < size; i++)
    {
        if (array[i] < array[i - 1])
        {
            return 0; // Não está ordenado
        }
    }
    return 1; // Está ordenado
}

void countingSort(int *array, int size)
{
    if (size <= 1)
        return;

    // Encontrar o valor máximo
    int max = findMax(array, size);

    // Criar array de contagem
    int *count = (int *)calloc(max + 1, sizeof(int));

    // Contar occorrências
    for (int i = 0; i < size; i++)
    {
        count[array[i]]++;
    }

    // Reconstruir array ordenado
    int index = 0;
    for (int i = 0; i <= max; i++)
    {
        while (count[i] > 0)
        {
            array[index++] = i;
            count[i]--;
        }
    }

    free(count);
}

void countingSortStable(int *array, int size)
{
    if (size <= 1)
        return;

    // Encontrar valor máximo
    int max = findMax(array, size);

    // Criar arrays auxiliares
    int *count = (int *)calloc(max + 1, sizeof(int));
    int *output = (int *)malloc(size * sizeof(int));

    // Contar occorrências
    for (int i = 0; i < size; i++)
    {
        count[array[i]]++;
    }

    // Transformar count em posições cumulativas
    for (int i = 1; i <= max; i++)
    {
        count[i] += count[i - 1];
    }

    // Construir array de saída (de trás para frente para manter estabilidade)
    for (int i = size - 1; i >= 0; i--)
    {
        output[count[array[i]] - 1] = array[i];
        count[array[i]]--;
    }

    // Copiar de volta para o array original
    for (int i = 0; i < size; i++)
    {
        array[i] = output[i];
    }

    free(count);
    free(output);
}