#ifndef CONFIG_H
#define CONFIG_H

typedef enum
{
    LISTA_LINEAR = 1,
    LISTA_DINAMICA = 2,
    PILHA_LINEAR = 3,
    PILHA_DINAMICA = 4,
    FILA_LINEAR = 5,
    FILA_DINAMICA = 6
} TipoEstrutura;

typedef enum
{
    COUNTING_SORT = 1,
    RADIX_SORT = 2,
} MetodoOrdenacao;

// Tipos de dados a serem lidos
// MOVIE_IDS: IDs dos filmes
// RATINGS: Avaliações dos filmes
typedef enum
{
    MOVIE_IDS = 1,
    RATINGS = 2
} TipoDado;

//=================CONFIGURAÇÕES=================

#define TIPO_DADO RATINGS // Escolha do tipo de dado a ser lido

// CONFIGURAÇÕES DE ARQUIVO
#define ARQUIVO_ENTRADA "/home/john/Desktop/NonComparativeSortingAlgorithms/ml-25m/ratings.csv"

// Escolha da estrutura a ser testada
#define ESTRUTURA_ATIVA LISTA_DINAMICA

// Escolha do método de ordenação
#define METODO_ORDENACAO RADIX_SORT

// Tamanho da entrada para leitura
#define maxlinhas 1000000

#endif