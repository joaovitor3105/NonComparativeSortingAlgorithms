#ifndef CONFIG_H
#define CONFIG_H

// Tamanho da entrada para leitura
#define maxlinhas 25000000

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
#define TIPO_DADO RATINGS // Escolha do tipo de dado a ser lido

// Escolha da estrutura a ser testada
#define ESTRUTURA_ATIVA LISTA_DINAMICA
// Escolha do método de ordenação
#define METODO_ORDENACAO RADIX_SORT

// CONFIGURAÇÕES DE ARQUIVO
#define ARQUIVO_ENTRADA "datasets/ratings.csv"

#endif