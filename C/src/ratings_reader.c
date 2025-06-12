#include <stdio.h>
#include <stdlib.h>
#include "ratings_reader.h"
#include "data_structures.h"
#include "config.h"

// ========== LEITURA PARA ESTRUTURAS LINEARES ==========

int lerMovieIds_LinearList(LinearList **list, int maxLines)
{
    FILE *file = fopen(ARQUIVO_ENTRADA, "r");
    if (!file)
    {
        printf("Erro ao abrir arquivo: %s\n", ARQUIVO_ENTRADA);
        return -1;
    }

    *list = createLinearList(maxLines);
    char linha[256];
    int contador = 0;
    int userId, movieId;
    float rating;
    long timestamp;

    // Pular cabeçalho
    if (!fgets(linha, sizeof(linha), file))
    {
        fclose(file);
        return -1;
    }

    printf("Lendo dados para Lista Linear...\n");
    while (fgets(linha, sizeof(linha), file) && contador < maxLines)
    {
        if (sscanf(linha, "%d,%d,%f,%ld", &userId, &movieId, &rating, &timestamp) == 4)
        {
            appendLinearList(*list, movieId);
            contador++;

            // Mostrar progresso a cada 10000 linhas
            if (contador % 10000 == 0)
            {
                printf("Lidas %d linhas...\n", contador);
            }
        }
    }

    fclose(file);
    printf("Total de %d movieIds lidos para Lista Linear.\n", contador);
    return contador;
}

int lerMovieIds_LinearStack(LinearStack **stack, int maxLines)
{
    FILE *file = fopen(ARQUIVO_ENTRADA, "r");
    if (!file)
    {
        printf("Erro ao abrir arquivo: %s\n", ARQUIVO_ENTRADA);
        return -1;
    }

    *stack = createLinearStack(maxLines);
    char linha[256];
    int contador = 0;
    int userId, movieId;
    float rating;
    long timestamp;

    // Pular cabeçalho
    if (!fgets(linha, sizeof(linha), file))
    {
        fclose(file);
        return -1;
    }

    printf("Lendo dados para Pilha Linear...\n");
    while (fgets(linha, sizeof(linha), file) && contador < maxLines)
    {
        if (sscanf(linha, "%d,%d,%f,%ld", &userId, &movieId, &rating, &timestamp) == 4)
        {
            pushLinear(*stack, movieId);
            contador++;

            if (contador % 10000 == 0)
            {
                printf("Lidas %d linhas...\n", contador);
            }
        }
    }

    fclose(file);
    printf("Total de %d movieIds lidos para Pilha Linear.\n", contador);
    return contador;
}

int lerMovieIds_LinearQueue(LinearQueue **queue, int maxLines)
{
    FILE *file = fopen(ARQUIVO_ENTRADA, "r");
    if (!file)
    {
        printf("Erro ao abrir arquivo: %s\n", ARQUIVO_ENTRADA);
        return -1;
    }

    *queue = createLinearQueue(maxLines);
    char linha[256];
    int contador = 0;
    int userId, movieId;
    float rating;
    long timestamp;

    // Pular cabeçalho
    if (!fgets(linha, sizeof(linha), file))
    {
        fclose(file);
        return -1;
    }

    printf("Lendo dados para Fila Linear...\n");
    while (fgets(linha, sizeof(linha), file) && contador < maxLines)
    {
        if (sscanf(linha, "%d,%d,%f,%ld", &userId, &movieId, &rating, &timestamp) == 4)
        {
            enqueueLinear(*queue, movieId);
            contador++;

            if (contador % 10000 == 0)
            {
                printf("Lidas %d linhas...\n", contador);
            }
        }
    }

    fclose(file);
    printf("Total de %d movieIds lidos para Fila Linear.\n", contador);
    return contador;
}

// ========== LEITURA PARA ESTRUTURAS DINÂMICAS ==========

int lerMovieIds_LinkedList(LinkedList **list, int maxLines)
{
    FILE *file = fopen(ARQUIVO_ENTRADA, "r");
    if (!file)
    {
        printf("Erro ao abrir arquivo: %s\n", ARQUIVO_ENTRADA);
        return -1;
    }

    *list = createList();
    char linha[256];
    int contador = 0;
    int userId, movieId;
    float rating;
    long timestamp;

    // Pular cabeçalho
    if (!fgets(linha, sizeof(linha), file))
    {
        fclose(file);
        return -1;
    }

    printf("Lendo dados para Lista Ligada...\n");

    // Ler todos os dados primeiro em um array temporário
    // para manter a ordem original na lista ligada
    int *tempArray = (int *)malloc(maxLines * sizeof(int));

    while (fgets(linha, sizeof(linha), file) && contador < maxLines)
    {
        if (sscanf(linha, "%d,%d,%f,%ld", &userId, &movieId, &rating, &timestamp) == 4)
        {
            tempArray[contador] = movieId;
            contador++;

            if (contador % 10000 == 0)
            {
                printf("Lidas %d linhas...\n", contador);
            }
        }
    }

    // Inserir na lista ligada em ordem reversa para manter ordem original
    for (int i = contador - 1; i >= 0; i--)
    {
        insertList(*list, tempArray[i]);
    }

    free(tempArray);
    fclose(file);
    printf("Total de %d movieIds lidos para Lista Ligada.\n", contador);
    return contador;
}

int lerMovieIds_Stack(Stack **stack, int maxLines)
{
    FILE *file = fopen(ARQUIVO_ENTRADA, "r");
    if (!file)
    {
        printf("Erro ao abrir arquivo: %s\n", ARQUIVO_ENTRADA);
        return -1;
    }

    *stack = createStack(maxLines);
    char linha[256];
    int contador = 0;
    int userId, movieId;
    float rating;
    long timestamp;

    // Pular cabeçalho
    if (!fgets(linha, sizeof(linha), file))
    {
        fclose(file);
        return -1;
    }

    printf("Lendo dados para Pilha Dinâmica...\n");
    while (fgets(linha, sizeof(linha), file) && contador < maxLines)
    {
        if (sscanf(linha, "%d,%d,%f,%ld", &userId, &movieId, &rating, &timestamp) == 4)
        {
            push(*stack, movieId);
            contador++;

            if (contador % 10000 == 0)
            {
                printf("Lidas %d linhas...\n", contador);
            }
        }
    }

    fclose(file);
    printf("Total de %d movieIds lidos para Pilha Dinâmica.\n", contador);
    return contador;
}

int lerMovieIds_Queue(Queue **queue, int maxLines)
{
    FILE *file = fopen(ARQUIVO_ENTRADA, "r");
    if (!file)
    {
        printf("Erro ao abrir arquivo: %s\n", ARQUIVO_ENTRADA);
        return -1;
    }

    *queue = createQueue(maxLines);
    char linha[256];
    int contador = 0;
    int userId, movieId;
    float rating;
    long timestamp;

    // Pular cabeçalho
    if (!fgets(linha, sizeof(linha), file))
    {
        fclose(file);
        return -1;
    }

    printf("Lendo dados para Fila Dinâmica...\n");
    while (fgets(linha, sizeof(linha), file) && contador < maxLines)
    {
        if (sscanf(linha, "%d,%d,%f,%ld", &userId, &movieId, &rating, &timestamp) == 4)
        {
            enqueue(*queue, movieId);
            contador++;

            if (contador % 10000 == 0)
            {
                printf("Lidas %d linhas...\n", contador);
            }
        }
    }

    fclose(file);
    printf("Total de %d movieIds lidos para Fila Dinâmica.\n", contador);
    return contador;
}

// ========== FUNÇÃO PRINCIPAL PARA ESCOLHER O TIPO DE LEITURA ==========

int lerMovieIds_PorTipo(void **estrutura, TipoEstrutura tipo, int maxLines)
{
    switch (tipo)
    {
    case LISTA_LINEAR:
        return lerMovieIds_LinearList((LinearList **)estrutura, maxLines);

    case LISTA_DINAMICA:
        return lerMovieIds_LinkedList((LinkedList **)estrutura, maxLines);

    case PILHA_LINEAR:
        return lerMovieIds_LinearStack((LinearStack **)estrutura, maxLines);

    case PILHA_DINAMICA:
        return lerMovieIds_Stack((Stack **)estrutura, maxLines);

    case FILA_LINEAR:
        return lerMovieIds_LinearQueue((LinearQueue **)estrutura, maxLines);

    case FILA_DINAMICA:
        return lerMovieIds_Queue((Queue **)estrutura, maxLines);

    default:
        printf("Tipo de estrutura inválido!\n");
        return -1;
    }
}

// ========== FUNÇÃO PARA OBTER NOME DA ESTRUTURA ==========

const char *getNomeEstrutura(TipoEstrutura tipo)
{
    switch (tipo)
    {
    case LISTA_LINEAR:
        return "Lista Linear";
    case LISTA_DINAMICA:
        return "Lista Ligada";
    case PILHA_LINEAR:
        return "Pilha Linear";
    case PILHA_DINAMICA:
        return "Pilha Dinâmica";
    case FILA_LINEAR:
        return "Fila Linear";
    case FILA_DINAMICA:
        return "Fila Dinâmica";
    default:
        return "Desconhecida";
    }
}