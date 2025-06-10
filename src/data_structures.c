#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

// ========== IMPLEMENTAÇÕES - ESTRUTURAS DINÂMICAS ==========
// === IMPLEMENTAÇÕES DA LISTA ===
LinkedList *createList()
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

void insertList(LinkedList *list, int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

void destroyList(LinkedList *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

// === IMPLEMENTAÇÕES DA PILHA ===
Stack *createStack(int capacity)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->data = (int *)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push(Stack *stack, int value)
{
    if (stack->top < stack->capacity - 1)
    {
        stack->data[++stack->top] = value;
    }
}

int pop(Stack *stack)
{
    if (stack->top >= 0)
    {
        return stack->data[stack->top--];
    }
    return -1;
}

void destroyStack(Stack *stack)
{
    free(stack->data);
    free(stack);
}

// === IMPLEMENTAÇÕES DA FILA ===
Queue *createQueue(int capacity)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->data = (int *)malloc(capacity * sizeof(int));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

void enqueue(Queue *queue, int value)
{
    if (queue->size < queue->capacity)
    {
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->data[queue->rear] = value;
        queue->size++;
    }
}

int dequeue(Queue *queue)
{
    if (queue->size > 0)
    {
        int value = queue->data[queue->front];
        queue->front = (queue->front + 1) % queue->capacity;
        queue->size--;
        return value;
    }
    return -1;
}

void destroyQueue(Queue *queue)
{
    free(queue->data);
    free(queue);
}

// ========== IMPLEMENTAÇÕES - ESTRUTURAS LINEARES ==========

// === LISTA LINEAR ===
LinearList *createLinearList(int capacity)
{
    LinearList *list = (LinearList *)malloc(sizeof(LinearList));
    list->data = (int *)malloc(capacity * sizeof(int));
    list->size = 0;
    list->capacity = capacity;
    return list;
}

void insertLinearList(LinearList *list, int value)
{
    if (list->size < list->capacity)
    {
        // Inserir no início (similar à lista ligada)
        for (int i = list->size; i > 0; i--)
        {
            list->data[i] = list->data[i - 1];
        }
        list->data[0] = value;
        list->size++;
    }
}

void appendLinearList(LinearList *list, int value)
{
    if (list->size < list->capacity)
    {
        list->data[list->size++] = value;
    }
}

int getLinearList(LinearList *list, int index)
{
    if (index >= 0 && index < list->size)
    {
        return list->data[index];
    }
    return -1;
}

void destroyLinearList(LinearList *list)
{
    free(list->data);
    free(list);
}

// === PILHA LINEAR ===
LinearStack *createLinearStack(int capacity)
{
    LinearStack *stack = (LinearStack *)malloc(sizeof(LinearStack));
    stack->data = (int *)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void pushLinear(LinearStack *stack, int value)
{
    if (stack->top < stack->capacity - 1)
    {
        stack->data[++stack->top] = value;
    }
}

int popLinear(LinearStack *stack)
{
    if (stack->top >= 0)
    {
        return stack->data[stack->top--];
    }
    return -1;
}

int isLinearStackEmpty(LinearStack *stack)
{
    return stack->top == -1;
}

void destroyLinearStack(LinearStack *stack)
{
    free(stack->data);
    free(stack);
}

// === FILA LINEAR ===
LinearQueue *createLinearQueue(int capacity)
{
    LinearQueue *queue = (LinearQueue *)malloc(sizeof(LinearQueue));
    queue->data = (int *)malloc(capacity * sizeof(int));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

void enqueueLinear(LinearQueue *queue, int value)
{
    if (queue->size < queue->capacity)
    {
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->data[queue->rear] = value;
        queue->size++;
    }
}

int dequeueLinear(LinearQueue *queue)
{
    if (queue->size > 0)
    {
        int value = queue->data[queue->front];
        queue->front = (queue->front + 1) % queue->capacity;
        queue->size--;
        return value;
    }
    return -1;
}

int isLinearQueueEmpty(LinearQueue *queue)
{
    return queue->size == 0;
}

void destroyLinearQueue(LinearQueue *queue)
{
    free(queue->data);
    free(queue);
}