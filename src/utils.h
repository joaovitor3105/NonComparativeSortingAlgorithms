#ifndef UTILS_H
#define UTILS_H

#include "data_structures.h"

// ========== ESTRUTURAS PARA MEDIÇÃO DE PERFORMANCE ==========

typedef struct
{
    double time_seconds;
    long memory_peak_kb;
    int comparisons;
    int swaps;
} PerformanceMetrics;

typedef struct
{
    char structure_name[50];
    char representation[20]; // "dynamic" ou "linear"
    int data_size;
    PerformanceMetrics metrics;
} BenchmarkResult;

// ========== FUNÇÕES DE IMPRESSÃO ==========

void printArray(int *array, int size, const char *label);
void printList(LinkedList *list, const char *label);
void printLinearList(LinearList *list, const char *label);

// ========== FUNÇÕES DE GERAÇÃO DE DADOS ==========

int *generateRandomArray(int size, int maxValue);
int *generateSortedArray(int size);
int *generateReverseSortedArray(int size);
int *generatePartiallyOrderedArray(int size, float orderPercentage);

// ========== FUNÇÕES DE MEDIÇÃO DE PERFORMANCE ==========

double measureTime(void (*sortFunction)(int *, int), int *array, int size);
long measureMemoryUsage();
PerformanceMetrics measurePerformanceComplete(void (*sortFunction)(int *, int), int *array, int size);

// ========== FUNÇÕES PARA ANÁLISE DE DADOS CSV ==========

typedef struct
{
    int *ratings;
    int count;
    int capacity;
} CSVData;

CSVData *loadCSVRatings(const char *filename, int max_records);
void destroyCSVData(CSVData *data);
int *getCSVSubset(CSVData *data, int size);

// ========== FUNÇÕES DE BENCHMARK SISTEMÁTICO ==========

void benchmarkAllStructures(int data_sizes[], int num_sizes, const char *output_file);
void benchmarkSingleStructure(const char *structure_name, int *test_data, int size, BenchmarkResult *result);
void exportBenchmarkResults(BenchmarkResult *results, int num_results, const char *filename);

// ========== FUNÇÕES DE VALIDAÇÃO ==========

int validateSortedArray(int *array, int size);
int compareArrays(int *array1, int *array2, int size);
#endif