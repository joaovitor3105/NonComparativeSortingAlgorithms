#ifndef PERFORMANCEANALYZER_HPP
#define PERFORMANCEANALYZER_HPP

#include "DataStructure.hpp"
#include <chrono>
#include <vector>
#include <memory>
#include <map>
#include <functional>

class PerformanceAnalyzer
{
public:
    struct PerformanceResult
    {
        std::string structureType;
        size_t dataSize;
        std::chrono::nanoseconds loadTime;
        std::chrono::nanoseconds convertToVectorTime;
        std::chrono::nanoseconds sortTime;
        std::chrono::nanoseconds convertBackTime;
        std::chrono::nanoseconds totalTime;
        size_t memoryUsage;
        bool success;
    };

private:
    std::vector<PerformanceResult> results;
    std::vector<size_t> testSizes;

public:
    PerformanceAnalyzer();

    struct StructureFactoryInfo
    {
        std::string typeName;
        bool isDynamic;
        std::function<std::unique_ptr<DataStructure>()> factory;
    };

    std::vector<StructureFactoryInfo> createStructureFactories() const;
    void setTestSizes(const std::vector<size_t> &sizes);
    PerformanceResult runPerformanceTest(const std::vector<int> &ratings,
                                         std::unique_ptr<DataStructure> &structure,
                                         size_t dataSize);
    void runFullAnalysis(const std::vector<int> &ratings);
    void printDetailedResults() const;
    void printSummary() const;
    void saveResultsToCSV(const std::string &filename) const;
    void saveResultsToFile(const std::string &filename = "output.dat") const;
    void calculateStatistics() const;

private:
    size_t estimateMemoryUsage(const DataStructure &structure, size_t dataSize) const;
    std::string formatTimeNano(const std::chrono::nanoseconds &time) const;
    std::string formatTime(const std::chrono::milliseconds &time) const;
    std::string formatMemory(size_t bytes) const;
    std::vector<std::unique_ptr<DataStructure>> createAllStructures() const;
};

#endif
