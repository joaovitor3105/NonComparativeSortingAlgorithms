#ifndef LISTSTRUCTURE_HPP
#define LISTSTRUCTURE_HPP

#include "DataStructure.hpp"
#include <list>

/**
 * Implementação de estrutura baseada em lista
 * Suporta tanto versão linear quanto dinâmica (lista ligada)
 */
class ListStructure : public DataStructure
{
private:
    // Para versão dinâmica - lista ligada simples
    struct Node
    {
        int data;
        Node *next;
        Node(int value) : data(value), next(nullptr) {}
    };

    Node *head;
    Node *tail;
    size_t currentSize;

    // Para versão linear - usando std::list
    std::list<int> linearList;

public:
    explicit ListStructure(bool dynamic = false);
    ~ListStructure() override;

    size_t size() const override;
    bool empty() const override;
    void insert(int value) override;
    void clear() override;
    std::vector<int> toVector() const override;
    void fromVector(const std::vector<int> &vec) override;
    std::string getType() const override;

private:
    void clearDynamicList();
};

#endif // LISTSTRUCTURE_HPP