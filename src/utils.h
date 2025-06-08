#ifndef UTILS_H
#define UTILS_H

#include "data_structures.h"

// Funções de impressão
void printArray(int *array, int size, const char *label);
void printList(LinkedList *list, const char *label);

// Funções de geração de dados
int *generateRandomArray(int size, int maxValue);
int *generateSortedArray(int size);
int *generateReverseSortedArray(int size);

// Função de medição de tempo
double measureTime(void (*sortFunction)(int *, int), int *array, int size);

#endif