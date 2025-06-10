#ifndef CONVERTERS_H
#define CONVERTERS_H

#include "data_structures.h"

// ========== CONVERSÕES - ESTRUTURAS DINÂMICAS ==========

// Conversões Lista Ligada
int *listToArray(LinkedList *list);
LinkedList *arrayToList(int *array, int size);

// Conversões Pilha
int *stackToArray(Stack *stack);
Stack *arrayToStack(int *array, int size);

// Conversões Fila
int *queueToArray(Queue *queue);
Queue *arrayToQueue(int *array, int size);

// ========== CONVERSÕES - ESTRUTURAS LINEARES ==========

// Conversões Lista Linear
int *linearListToArray(LinearList *list);
LinearList *arrayToLinearList(int *array, int size);

// Conversões Pilha Linear
int *linearStackToArray(LinearStack *stack);
LinearStack *arrayToLinearStack(int *array, int size);

// Conversões Fila Linear
int *linearQueueToArray(LinearQueue *queue);
LinearQueue *arrayToLinearQueue(int *array, int size);

// ========== FUNÇÕES AUXILIARES ==========

// Função para copiar array
int *copyArray(int *source, int size);

// Função para obter tamanho das estruturas
int getStackSize(Stack *stack);
int getLinearStackSize(LinearStack *stack);

#endif