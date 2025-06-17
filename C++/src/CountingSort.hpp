#ifndef COUNTINGSORT_HPP
#define COUNTINGSORT_HPP

#include <vector>
#include <chrono>
#include <string>

/**
 * Implementação do algoritmo Counting Sort
 * Algoritmo de ordenação não comparativo com complexidade O(n+k)
 */
class CountingSort
{
private:
    static int findMax(const std::vector<int> &arr);
    static int findMin(const std::vector<int> &arr);

public:
    /**
     * Ordena um vetor usando Counting Sort
     * @param arr Vetor a ser ordenado
     * @return Vetor ordenado
     */
    static std::vector<int> sort(const std::vector<int> &arr);

    /**
     * Ordena um vetor usando Counting Sort com medição de tempo
     * @param arr Vetor a ser ordenado
     * @param executionTime Referência para armazenar o tempo de execução
     * @return Vetor ordenado
     */
    static std::vector<int> sortWithTiming(const std::vector<int> &arr,
                                           std::chrono::milliseconds &executionTime);

    /**
     * Verifica se um vetor está ordenado
     * @param arr Vetor a ser verificado
     * @return true se estiver ordenado, false caso contrário
     */
    static bool isSorted(const std::vector<int> &arr);

    /**
     * Imprime estatísticas do vetor
     * @param arr Vetor para análise
     * @param label Rótulo para identificação
     */
    static void printStatistics(const std::vector<int> &arr, const std::string &label);
};

#endif // COUNTINGSORT_HPP