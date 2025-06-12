#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils.h"
#include "counting_sort.h"

void printArray(int *array, int size, const char *label)
{
    printf("%s: ", label);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void printList(LinkedList *list, const char *label)
{
    printf("%s: ", label);
    Node *current = list->head;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int *generateRandomArray(int size, int maxValue)
{
    int *array = (int *)malloc(size * sizeof(int));
    srand(time(NULL));

    for (int i = 0; i < size; i++)
    {
        array[i] = rand() % (maxValue + 1);
    }

    return array;
}

int *generateSortedArray(int size)
{
    int *array = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        array[i] = i;
    }

    return array;
}

int *generateReverseSortedArray(int size)
{
    int *array = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        array[i] = size - i - 1;
    }

    return array;
}

double measureTime(void (*sortFunction)(int *, int), int *array, int size)
{
    // Criar cópia do array para não alterar o original
    int *arrayCopy = (int *)malloc(size * sizeof(int));
    memcpy(arrayCopy, array, size * sizeof(int));

    clock_t start = clock();
    sortFunction(arrayCopy, size);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    free(arrayCopy);
    return time_taken;
}