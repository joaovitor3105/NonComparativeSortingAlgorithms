#ifndef CONFIG_H
#define CONFIG_H

// Tamanho da entrada para leitura
#define maxlinhas 100000

typedef enum
{
    LISTA_LINEAR = 1,
    LISTA_DINAMICA = 2,
    PILHA_LINEAR = 3,
    PILHA_DINAMICA = 4,
    FILA_LINEAR = 5,
    FILA_DINAMICA = 6
} TipoEstrutura;

// Escolha da estrutura a ser testada
#define ESTRUTURA_ATIVA LISTA_DINAMICA

// CONFIGURAÇÕES DE ARQUIVO
#define ARQUIVO_ENTRADA "dataset/ratings.csv"
#define ARQUIVO_SAIDA "dataset/resultados.csv"

#endif