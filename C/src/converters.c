#include <stdlib.h>
#include "converters.h"
#include "data_structures.h"
#include "utils.h"
#include <string.h>
#include <stdio.h>

// ========== CONVERSÕES - ESTRUTURAS DINÂMICAS ==========

// === CONVERSÕES LISTA LIGADA ===
int *listToArray(LinkedList *list)
{
    if (list->size == 0)
        return NULL;

    int *array = (int *)malloc(list->size * sizeof(int));
    if (!array)
        return NULL;

    Node *current = list->head;

    // Como a lista insere no início, os elementos estão em ordem reversa
    // Precisamos colocar no array na ordem correta (primeiro inserido = primeiro no array)
    for (int i = list->size - 1; i >= 0; i--)
    {
        array[i] = current->data;
        current = current->next;
    }

    return array;
}

LinkedList *arrayToList(int *array, int size)
{
    LinkedList *list = createList();
    if (!list)
        return NULL;

    // Inserir em ordem reversa para que o primeiro elemento do array
    // seja o primeiro da lista (já que insertList insere no início)
    for (int i = size - 1; i >= 0; i--)
    {
        insertList(list, array[i]);
    }

    return list;
}

// === CONVERSÕES PILHA ===
int *stackToArray(Stack *stack)
{
    if (stack->top < 0)
        return NULL;

    int size = stack->top + 1;
    int *array = (int *)malloc(size * sizeof(int));
    if (!array)
        return NULL;

    // Copiar dados da pilha mantendo a ordem de inserção
    for (int i = 0; i < size; i++)
    {
        array[i] = stack->data[i];
    }

    return array;
}

Stack *arrayToStack(int *array, int size)
{
    Stack *stack = createStack(size);
    if (!stack)
        return NULL;

    for (int i = 0; i < size; i++)
    {
        push(stack, array[i]);
    }

    return stack;
}

// === CONVERSÕES FILA ===
int *queueToArray(Queue *queue)
{
    if (queue->size == 0)
        return NULL;

    int *array = (int *)malloc(queue->size * sizeof(int));
    if (!array)
        return NULL;

    int index = queue->front;

    // Percorrer a fila circular
    for (int i = 0; i < queue->size; i++)
    {
        array[i] = queue->data[index];
        index = (index + 1) % queue->capacity;
    }

    return array;
}

Queue *arrayToQueue(int *array, int size)
{
    Queue *queue = createQueue(size);
    if (!queue)
        return NULL;

    for (int i = 0; i < size; i++)
    {
        enqueue(queue, array[i]);
    }

    return queue;
}

// ========== CONVERSÕES - ESTRUTURAS LINEARES ==========

// === CONVERSÕES LISTA LINEAR ===
int *linearListToArray(LinearList *list)
{
    if (list->size == 0)
        return NULL;

    int *array = (int *)malloc(list->size * sizeof(int));
    if (!array)
        return NULL;

    // Copiar dados diretamente - já estão na ordem correta
    memcpy(array, list->data, list->size * sizeof(int));

    return array;
}

LinearList *arrayToLinearList(int *array, int size)
{
    LinearList *list = createLinearList(size);
    if (!list)
        return NULL;

    // Usar memcpy para eficiência
    memcpy(list->data, array, size * sizeof(int));
    list->size = size;

    return list;
}

// === CONVERSÕES PILHA LINEAR ===
int *linearStackToArray(LinearStack *stack)
{
    if (stack->top < 0)
        return NULL;

    int size = stack->top + 1;
    int *array = (int *)malloc(size * sizeof(int));
    if (!array)
        return NULL;

    // Copiar dados da pilha mantendo ordem de inserção
    memcpy(array, stack->data, size * sizeof(int));

    return array;
}

LinearStack *arrayToLinearStack(int *array, int size)
{
    LinearStack *stack = createLinearStack(size);
    if (!stack)
        return NULL;

    // Copiar todos os elementos de uma vez
    memcpy(stack->data, array, size * sizeof(int));
    stack->top = size - 1;

    return stack;
}

// === CONVERSÕES FILA LINEAR ===
int *linearQueueToArray(LinearQueue *queue)
{
    if (queue->size == 0)
        return NULL;

    int *array = (int *)malloc(queue->size * sizeof(int));
    if (!array)
        return NULL;

    int index = queue->front;

    // Percorrer a fila circular
    for (int i = 0; i < queue->size; i++)
    {
        array[i] = queue->data[index];
        index = (index + 1) % queue->capacity;
    }

    return array;
}

LinearQueue *arrayToLinearQueue(int *array, int size)
{
    LinearQueue *queue = createLinearQueue(size);
    if (!queue)
        return NULL;

    // Para fila, precisamos respeitar a ordem FIFO
    // Copiar elementos mantendo a estrutura circular
    memcpy(queue->data, array, size * sizeof(int));
    queue->front = 0;
    queue->rear = size - 1;
    queue->size = size;

    return queue;
}

// ========== FUNÇÕES AUXILIARES ==========

int *copyArray(int *source, int size)
{
    if (!source || size <= 0)
        return NULL;

    int *copy = (int *)malloc(size * sizeof(int));
    if (!copy)
        return NULL;

    memcpy(copy, source, size * sizeof(int));
    return copy;
}

int getStackSize(Stack *stack)
{
    if (!stack)
        return 0;
    return stack->top + 1;
}

int getLinearStackSize(LinearStack *stack)
{
    if (!stack)
        return 0;
    return stack->top + 1;
}

// Funções adicionais para verificação de integridade
int verifyArrayIntegrity(int *array, int size)
{
    if (!array || size <= 0)
        return 0;

    // Verificar se todos os elementos são válidos (não negativos para ratings)
    for (int i = 0; i < size; i++)
    {
        if (array[i] < 0)
            return 0;
    }
    return 1;
}

void printArraySample(int *array, int size, const char *label)
{
    if (!array || size <= 0)
        return;

    printf("%s (primeiros 10): ", label);
    int limit = (size < 10) ? size : 10;
    for (int i = 0; i < limit; i++)
    {
        printf("%d ", array[i]);
    }
    if (size > 10)
        printf("...");
    printf("\n");
}