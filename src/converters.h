#ifndef CONVERTERS_H
#define CONVERTERS_H

#include "data_structures.h"

// Conversões Lista Ligada
int *listToArray(LinkedList *list);
LinkedList *arrayToList(int *array, int size);

// Conversões Pilha
int *stackToArray(Stack *stack);
Stack *arrayToStack(int *array, int size);

// Conversões Fila
int *queueToArray(Queue *queue);
Queue *arrayToQueue(int *array, int size);

#endif