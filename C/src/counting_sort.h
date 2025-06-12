#ifndef COUNTING_SORT_H
#define COUNTING_SORT_H

// Algoritmo básico Counting Sort
void countingSort(int *array, int size);

// Versão estável do Counting Sort
void countingSortStable(int *array, int size);

// Função para encontrar valor máximo
int findMax(int *array, int size);

// Função para verificar se array está ordenado
int isArraySorted(int *array, int size);

#endif