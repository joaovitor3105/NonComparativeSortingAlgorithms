#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ratings_reader.h"
#include "data_structures.h"
#include "config.h"

// ========== LEITURA PARA ESTRUTURAS LINEARES ==========

int lerDados_LinearList(LinearList **list, int maxLines, TipoDado tipoDado)
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

    const char *tipoStr = (tipoDado == MOVIE_IDS) ? "Movie IDs" : "Ratings";
    printf("Lendo %s para Lista Linear...\n", tipoStr);

    while (fgets(linha, sizeof(linha), file) && contador < maxLines)
    {
        if (sscanf(linha, "%d,%d,%f,%ld", &userId, &movieId, &rating, &timestamp) == 4)
        {
            int valor;
            if (tipoDado == MOVIE_IDS)
            {
                valor = movieId;
            }
            else // RATINGS
            {
                valor = (int)(rating * 2); // Multiplicar por 2 para converter para int
            }

            appendLinearList(*list, valor);
            contador++;
        }
    }

    fclose(file);
    printf("Total de %d %s lidos para Lista Linear.\n", contador, tipoStr);
    return contador;
}

int lerDados_LinearStack(LinearStack **stack, int maxLines, TipoDado tipoDado)
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

    const char *tipoStr = (tipoDado == MOVIE_IDS) ? "Movie IDs" : "Ratings";
    printf("Lendo %s para Pilha Linear...\n", tipoStr);

    while (fgets(linha, sizeof(linha), file) && contador < maxLines)
    {
        if (sscanf(linha, "%d,%d,%f,%ld", &userId, &movieId, &rating, &timestamp) == 4)
        {
            int valor;
            if (tipoDado == MOVIE_IDS)
            {
                valor = movieId;
            }
            else // RATINGS
            {
                valor = (int)(rating * 2);
            }

            pushLinear(*stack, valor);
            contador++;
        }
    }

    fclose(file);
    printf("Total de %d %s lidos para Pilha Linear.\n", contador, tipoStr);
    return contador;
}

int lerDados_LinearQueue(LinearQueue **queue, int maxLines, TipoDado tipoDado)
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

    const char *tipoStr = (tipoDado == MOVIE_IDS) ? "Movie IDs" : "Ratings";
    printf("Lendo %s para Fila Linear...\n", tipoStr);

    while (fgets(linha, sizeof(linha), file) && contador < maxLines)
    {
        if (sscanf(linha, "%d,%d,%f,%ld", &userId, &movieId, &rating, &timestamp) == 4)
        {
            int valor;
            if (tipoDado == MOVIE_IDS)
            {
                valor = movieId;
            }
            else // RATINGS
            {
                valor = (int)(rating * 2);
            }

            enqueueLinear(*queue, valor);
            contador++;
        }
    }

    fclose(file);
    printf("Total de %d %s lidos para Fila Linear.\n", contador, tipoStr);
    return contador;
}

// ========== LEITURA PARA ESTRUTURAS DINÂMICAS ==========

int lerDados_LinkedList(LinkedList **list, int maxLines, TipoDado tipoDado)
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

    const char *tipoStr = (tipoDado == MOVIE_IDS) ? "Movie IDs" : "Ratings";
    printf("Lendo %s para Lista Ligada...\n", tipoStr);

    // Ler todos os dados primeiro em um array temporário
    int *tempArray = (int *)malloc(maxLines * sizeof(int));

    while (fgets(linha, sizeof(linha), file) && contador < maxLines)
    {
        if (sscanf(linha, "%d,%d,%f,%ld", &userId, &movieId, &rating, &timestamp) == 4)
        {
            int valor;
            if (tipoDado == MOVIE_IDS)
            {
                valor = movieId;
            }
            else // RATINGS
            {
                valor = (int)(rating * 2);
            }

            tempArray[contador] = valor;
            contador++;
        }
    }

    // Inserir na lista ligada em ordem reversa para manter ordem original
    for (int i = contador - 1; i >= 0; i--)
    {
        insertList(*list, tempArray[i]);
    }

    free(tempArray);
    fclose(file);
    printf("Total de %d %s lidos para Lista Ligada.\n", contador, tipoStr);
    return contador;
}

int lerDados_Stack(Stack **stack, int maxLines, TipoDado tipoDado)
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

    const char *tipoStr = (tipoDado == MOVIE_IDS) ? "Movie IDs" : "Ratings";
    printf("Lendo %s para Pilha Dinâmica...\n", tipoStr);

    while (fgets(linha, sizeof(linha), file) && contador < maxLines)
    {
        if (sscanf(linha, "%d,%d,%f,%ld", &userId, &movieId, &rating, &timestamp) == 4)
        {
            int valor;
            if (tipoDado == MOVIE_IDS)
            {
                valor = movieId;
            }
            else // RATINGS
            {
                valor = (int)(rating * 2);
            }

            push(*stack, valor);
            contador++;
        }
    }

    fclose(file);
    printf("Total de %d %s lidos para Pilha Dinâmica.\n", contador, tipoStr);
    return contador;
}

int lerDados_Queue(Queue **queue, int maxLines, TipoDado tipoDado)
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

    const char *tipoStr = (tipoDado == MOVIE_IDS) ? "Movie IDs" : "Ratings";
    printf("Lendo %s para Fila Dinâmica...\n", tipoStr);

    while (fgets(linha, sizeof(linha), file) && contador < maxLines)
    {
        if (sscanf(linha, "%d,%d,%f,%ld", &userId, &movieId, &rating, &timestamp) == 4)
        {
            int valor;
            if (tipoDado == MOVIE_IDS)
            {
                valor = movieId;
            }
            else // RATINGS
            {
                valor = (int)(rating * 2);
            }

            enqueue(*queue, valor);
            contador++;
        }
    }

    fclose(file);
    printf("Total de %d %s lidos para Fila Dinâmica.\n", contador, tipoStr);
    return contador;
}

// ========== FUNÇÃO PRINCIPAL PARA ESCOLHER O TIPO DE LEITURA ==========

int lerDados_PorTipo(void **estrutura, TipoEstrutura tipo, TipoDado tipoDado, int maxLines)
{
    switch (tipo)
    {
    case LISTA_LINEAR:
        return lerDados_LinearList((LinearList **)estrutura, maxLines, tipoDado);

    case LISTA_DINAMICA:
        return lerDados_LinkedList((LinkedList **)estrutura, maxLines, tipoDado);

    case PILHA_LINEAR:
        return lerDados_LinearStack((LinearStack **)estrutura, maxLines, tipoDado);

    case PILHA_DINAMICA:
        return lerDados_Stack((Stack **)estrutura, maxLines, tipoDado);

    case FILA_LINEAR:
        return lerDados_LinearQueue((LinearQueue **)estrutura, maxLines, tipoDado);

    case FILA_DINAMICA:
        return lerDados_Queue((Queue **)estrutura, maxLines, tipoDado);

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