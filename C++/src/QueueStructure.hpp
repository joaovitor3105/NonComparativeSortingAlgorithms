#ifndef QUEUESTRUCTURE_HPP
#define QUEUESTRUCTURE_HPP

#include "DataStructure.hpp"
#include <queue>

/**
 * Implementação de estrutura baseada em fila
 * Suporta tanto versão linear quanto dinâmica
 */
class QueueStructure : public DataStructure
{
private:
    // Para versão dinâmica - fila ligada
    struct Node
    {
        int data;
        Node *next;
        Node(int value) : data(value), next(nullptr) {}
    };

    Node *front;
    Node *rear;
    size_t currentSize;

    // Para versão linear - usando std::queue
    std::queue<int> linearQueue;

public:
    explicit QueueStructure(bool dynamic = false);
    ~QueueStructure() override;

    void insert(int value) override;
    void clear() override;
    std::vector<int> toVector() const override;
    void fromVector(const std::vector<int> &vec) override;
    std::string getType() const override;

    size_t size() ;  
    bool empty() ;   

private:
    void clearDynamicQueue();
    void enqueue(int value);
    int dequeue();
    bool isEmpty() const;
};

#endif // QUEUESTRUCTURE_HPP