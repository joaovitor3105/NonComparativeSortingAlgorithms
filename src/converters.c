#include <stdlib.h>
#include "converters.h"

// === CONVERSÕES LISTA LIGADA ===
int *listToArray(LinkedList *list)
{
    if (list->size == 0)
        return NULL;

    int *array = (int *)malloc(list->size * sizeof(int));
    Node *current = list->head;

    // Inserir em ordem reversa para manter ordem original
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

    // Inserir em ordem reversa para manter ordem
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

    // Copiar dados da pilha
    for (int i = 0; i < size; i++)
    {
        array[i] = stack->data[i];
    }

    return array;
}

Stack *arrayToStack(int *array, int size)
{
    Stack *stack = createStack(size);

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
    int index = queue->front;

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

    for (int i = 0; i < size; i++)
    {
        enqueue(queue, array[i]);
    }

    return queue;
}