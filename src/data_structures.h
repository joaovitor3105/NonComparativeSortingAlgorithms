#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

// Estrutura para Lista Ligada
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    int size;
} LinkedList;

// Estrutura para Pilha
typedef struct
{
    int *data;
    int top;
    int capacity;
} Stack;

// Estrutura para Fila
typedef struct
{
    int *data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

// Declarações das funções para Lista Ligada
LinkedList *createList();
void insertList(LinkedList *list, int value);
void destroyList(LinkedList *list);

// Declarações das funções para Pilha
Stack *createStack(int capacity);
void push(Stack *stack, int value);
int pop(Stack *stack);
void destroyStack(Stack *stack);

// Declarações das funções para Fila
Queue *createQueue(int capacity);
void enqueue(Queue *queue, int value);
int dequeue(Queue *queue);
void destroyQueue(Queue *queue);

#endif