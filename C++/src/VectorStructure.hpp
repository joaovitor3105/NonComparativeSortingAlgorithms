#ifndef VECTORSTRUCTURE_HPP
#define VECTORSTRUCTURE_HPP

#include "DataStructure.hpp"
#include <iostream>

/**
 * Implementação de estrutura baseada em vetor
 * Suporta tanto versão linear quanto dinâmica
 */
class VectorStructure : public DataStructure
{
private:
    int *dynamicArray;
    size_t capacity;
    size_t currentSize;

public:
    explicit VectorStructure(bool dynamic = false);
    ~VectorStructure() override;

    void insert(int value) override;
    void clear() override;
    std::vector<int> toVector() const override;
    void fromVector(const std::vector<int> &vec) override;
    std::string getType() const override;

    size_t size() const;
    bool empty() const;

private:
    void resize();
    void initializeDynamicArray();
};

#endif // VECTORSTRUCTURE_HPP