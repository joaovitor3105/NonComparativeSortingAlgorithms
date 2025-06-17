#include "CountingSort.hpp"
#include <algorithm>
#include <iostream>
#include <iomanip>

int CountingSort::findMax(const std::vector<int> &arr)
{
    if (arr.empty())
        return 0;
    return *std::max_element(arr.begin(), arr.end());
}

int CountingSort::findMin(const std::vector<int> &arr)
{
    if (arr.empty())
        return 0;
    return *std::min_element(arr.begin(), arr.end());
}

std::vector<int> CountingSort::sort(const std::vector<int> &arr)
{
    if (arr.empty())
    {
        return arr;
    }

    // Encontra o valor mínimo e máximo
    int minVal = findMin(arr);
    int maxVal = findMax(arr);
    int range = maxVal - minVal + 1;

    // Array de contagem
    std::vector<int> count(range, 0);

    // Conta as ocorrências de cada elemento
    for (int num : arr)
    {
        count[num - minVal]++;
    }

    // Modifica count[i] para conter a posição real de cada elemento
    for (int i = 1; i < range; i++)
    {
        count[i] += count[i - 1];
    }

    // Array de saída
    std::vector<int> output(arr.size());

    // Constroi o array de saída
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }

    return output;
}

std::vector<int> CountingSort::sortWithTiming(const std::vector<int> &arr,
                                              std::chrono::milliseconds &executionTime)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> result = sort(arr);

    auto end = std::chrono::high_resolution_clock::now();
    executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    return result;
}

bool CountingSort::isSorted(const std::vector<int> &arr)
{
    for (size_t i = 1; i < arr.size(); i++)
    {
        if (arr[i] < arr[i - 1])
        {
            return false;
        }
    }
    return true;
}

void CountingSort::printStatistics(const std::vector<int> &arr, const std::string &label)
{
    if (arr.empty())
    {
        std::cout << label << ": Array vazio" << std::endl;
        return;
    }

    int minVal = findMin(arr);
    int maxVal = findMax(arr);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "=== " << label << " ===" << std::endl;
    std::cout << "Tamanho: " << arr.size() << std::endl;
    std::cout << "Mínimo: " << minVal << std::endl;
    std::cout << "Máximo: " << maxVal << std::endl;
    std::cout << "Range: " << (maxVal - minVal) << std::endl;
    std::cout << "Ordenado: " << (isSorted(arr) ? "Sim" : "Não") << std::endl;

    // Mostra alguns elementos do início e fim
    std::cout << "Primeiros 10 elementos: ";
    for (size_t i = 0; i < std::min(static_cast<size_t>(10), arr.size()); i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    if (arr.size() > 10)
    {
        std::cout << "Últimos 10 elementos: ";
        for (size_t i = std::max(static_cast<size_t>(0), arr.size() - 10); i < arr.size(); i++)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}