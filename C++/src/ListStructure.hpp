#ifndef LISTSTRUCTURE_HPP
#define LISTSTRUCTURE_HPP

#include "DataStructure.hpp"
#include <list>

class ListStructure : public DataStructure
{
private:
    struct Node
    {
        int data;
        Node *next;
        Node(int value) : data(value), next(nullptr) {}
    };

    Node *head;
    Node *tail;
    size_t currentSize;

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

#endif