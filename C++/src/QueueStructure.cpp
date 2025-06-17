#include "QueueStructure.hpp"
#include <stdexcept>


QueueStructure::QueueStructure(bool dynamic) : DataStructure(dynamic)
{
    if (isDynamic)
    {
        front = nullptr;
        rear = nullptr;
        currentSize = 0;
    }
}

QueueStructure::~QueueStructure()
{
    if (isDynamic)
    {
        clearDynamicQueue();
    }
}

void QueueStructure::clearDynamicQueue()
{
    while (!isEmpty())
    {
        dequeue();
    }
    currentSize = 0;
}

void QueueStructure::enqueue(int value)
{
    Node *newNode = new Node(value);

    if (rear == nullptr)
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
    currentSize++;
}

int QueueStructure::dequeue()
{
    if (isEmpty())
    {
        throw std::runtime_error("Queue is empty");
    }

    Node *temp = front;
    int value = temp->data;
    front = front->next;

    if (front == nullptr)
    {
        rear = nullptr;
    }

    delete temp;
    currentSize--;
    return value;
}

bool QueueStructure::isEmpty() const
{
    return front == nullptr;
}

void QueueStructure::insert(int value)
{
    if (isDynamic)
    {
        enqueue(value);
    }
    else
    {
        linearQueue.push(value);
    }
}

void QueueStructure::clear()
{
    if (isDynamic)
    {
        clearDynamicQueue();
    }
    else
    {
        // std::queue não tem método clear(), então criamos uma nova
        linearQueue = std::queue<int>();
    }
}

std::vector<int> QueueStructure::toVector() const
{
    std::vector<int> result;

    if (isDynamic)
    {
        Node *current = front;
        while (current != nullptr)
        {
            result.push_back(current->data);
            current = current->next;
        }
    }
    else
    {
        // Como std::queue não permite iteração, precisamos fazer uma cópia
        std::queue<int> tempQueue = linearQueue;
        while (!tempQueue.empty())
        {
            result.push_back(tempQueue.front());
            tempQueue.pop();
        }
    }

    return result;
}

void QueueStructure::fromVector(const std::vector<int> &vec)
{
    clear();

    for (const auto &value : vec)
    {
        insert(value);
    }
}

std::string QueueStructure::getType() const
{
    return isDynamic ? "Dynamic Queue" : "Linear Queue";
}


size_t QueueStructure::size() {
    if (isDynamic) {
        return currentSize;
    } else {
        return linearQueue.size();
    }
}

bool QueueStructure::empty() {
    if (isDynamic) {
        return currentSize == 0;
    } else {
        return linearQueue.empty();
    }
}
