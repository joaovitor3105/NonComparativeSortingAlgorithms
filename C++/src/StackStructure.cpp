#include "StackStructure.hpp"
#include <stdexcept>

StackStructure::StackStructure(bool dynamic) : DataStructure(dynamic)
{
    if (isDynamic)
    {
        top = nullptr;
        currentSize = 0;
    }
}

StackStructure::~StackStructure()
{
    if (isDynamic)
    {
        clearDynamicStack();
    }
}

void StackStructure::clearDynamicStack()
{
    while (!isEmpty())
    {
        pop();
    }
    currentSize = 0;
}

void StackStructure::push(int value)
{
    Node *newNode = new Node(value);
    newNode->next = top;
    top = newNode;
    currentSize++;
}

int StackStructure::pop()
{
    if (isEmpty())
    {
        throw std::runtime_error("Stack is empty");
    }

    Node *temp = top;
    int value = temp->data;
    top = top->next;
    delete temp;
    currentSize--;
    return value;
}

bool StackStructure::isEmpty() const
{
    return top == nullptr;
}

void StackStructure::insert(int value)
{
    if (isDynamic)
    {
        push(value);
    }
    else
    {
        linearStack.push(value);
    }
}

void StackStructure::clear()
{
    if (isDynamic)
    {
        clearDynamicStack();
    }
    else
    {
        // std::stack não tem método clear(), então criamos uma nova
        linearStack = std::stack<int>();
    }
}

std::vector<int> StackStructure::toVector() const
{
    std::vector<int> result;

    if (isDynamic)
    {
        // Para pilha, precisamos inverter a ordem para manter a ordem de inserção
        std::vector<int> temp;
        Node *current = top;
        while (current != nullptr)
        {
            temp.push_back(current->data);
            current = current->next;
        }
        // Inverte para manter ordem de inserção
        for (int i = temp.size() - 1; i >= 0; --i)
        {
            result.push_back(temp[i]);
        }
    }
    else
    {
        // Como std::stack não permite iteração, precisamos fazer uma cópia
        std::stack<int> tempStack = linearStack;
        std::vector<int> temp;
        while (!tempStack.empty())
        {
            temp.push_back(tempStack.top());
            tempStack.pop();
        }
        // Inverte para manter ordem de inserção
        for (int i = temp.size() - 1; i >= 0; --i)
        {
            result.push_back(temp[i]);
        }
    }

    return result;
}

void StackStructure::fromVector(const std::vector<int> &vec)
{
    clear();

    for (const auto &value : vec)
    {
        insert(value);
    }
}

std::string StackStructure::getType() const
{
    return isDynamic ? "Dynamic Stack" : "Linear Stack";
}

size_t StackStructure::size() const
{
    if (isDynamic)
    {
        return currentSize;
    }
    else
    {
        return linearStack.size();
    }
}

bool StackStructure::empty() const
{
    if (isDynamic)
    {
        return isEmpty();
    }
    else
    {
        return linearStack.empty();
    }
}