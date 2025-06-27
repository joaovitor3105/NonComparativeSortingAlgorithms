#ifndef STACKSTRUCTURE_HPP
#define STACKSTRUCTURE_HPP

#include "DataStructure.hpp"
#include <stack>

class StackStructure : public DataStructure
{
private:
    struct Node
    {
        int data;
        Node *next;
        Node(int value) : data(value), next(nullptr) {}
    };

    Node *top;
    size_t currentSize;

    std::stack<int> linearStack;

public:
    explicit StackStructure(bool dynamic = false);
    ~StackStructure() override;

    void insert(int value) override;
    void clear() override;
    std::vector<int> toVector() const override;
    void fromVector(const std::vector<int> &vec) override;
    std::string getType() const override;

    size_t size() const;
    bool empty() const;

private:
    void clearDynamicStack();
    void push(int value);
    int pop();
    bool isEmpty() const;
};

#endif