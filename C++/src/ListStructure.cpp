#include "ListStructure.hpp"

ListStructure::ListStructure(bool dynamic) : DataStructure(dynamic)
{
    if (isDynamic)
    {
        head = nullptr;
        tail = nullptr;
        currentSize = 0;
    }
}

ListStructure::~ListStructure()
{
    if (isDynamic)
    {
        clearDynamicList();
    }
}

void ListStructure::clearDynamicList()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    currentSize = 0;
}

void ListStructure::insert(int value)
{
    if (isDynamic)
    {
        Node *newNode = new Node(value);

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        currentSize++;
    }
    else
    {
        linearList.push_back(value);
    }
}

void ListStructure::clear()
{
    if (isDynamic)
    {
        clearDynamicList();
    }
    else
    {
        linearList.clear();
    }
}

std::vector<int> ListStructure::toVector() const
{
    std::vector<int> result;

    if (isDynamic)
    {
        Node *current = head;
        while (current != nullptr)
        {
            result.push_back(current->data);
            current = current->next;
        }
    }
    else
    {
        for (const auto &value : linearList)
        {
            result.push_back(value);
        }
    }

    return result;
}

void ListStructure::fromVector(const std::vector<int> &vec)
{
    clear();

    for (const auto &value : vec)
    {
        insert(value);
    }
}

std::string ListStructure::getType() const
{
    return isDynamic ? "Dynamic List" : "Linear List";
}

size_t ListStructure::size() const
{
    if (isDynamic)
    {
        return currentSize;
    }
    else
    {
        return linearList.size();
    }
}

bool ListStructure::empty() const
{
    if (isDynamic)
    {
        return currentSize == 0;
    }
    else
    {
        return linearList.empty();
    }
}