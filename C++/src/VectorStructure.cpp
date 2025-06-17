#include "VectorStructure.hpp"
#include <algorithm>

VectorStructure::VectorStructure(bool dynamic) : DataStructure(dynamic) {
    if (isDynamic) {
        capacity = 1; // Começa pequeno para forçar redimensionamentos
        currentSize = 0;
        initializeDynamicArray();
    }
}

VectorStructure::~VectorStructure() {
    if (isDynamic && dynamicArray) {
        delete[] dynamicArray;
    }
}

void VectorStructure::initializeDynamicArray() {
    dynamicArray = new int[capacity];
}

void VectorStructure::resize() {
    size_t newCapacity = capacity * 2;
    int* newArray = new int[newCapacity];
    
    for (size_t i = 0; i < currentSize; ++i) {
        newArray[i] = dynamicArray[i];
    }
    
    delete[] dynamicArray;
    dynamicArray = newArray;
    capacity = newCapacity;
}

void VectorStructure::insert(int value) {
    if (isDynamic) {
        if (currentSize >= capacity) {
            resize();
        }
        dynamicArray[currentSize++] = value;
    } else {
        data.push_back(value);
    }
}

void VectorStructure::clear() {
    if (isDynamic) {
        currentSize = 0;
        // Não deletamos o array, apenas resetamos o tamanho
    } else {
        data.clear();
    }
}

std::vector<int> VectorStructure::toVector() const {
    if (isDynamic) {
        return std::vector<int>(dynamicArray, dynamicArray + currentSize);
    } else {
        return data;
    }
}

void VectorStructure::fromVector(const std::vector<int>& vec) {
    clear();
    
    if (isDynamic) {
        // Ajusta capacidade se necessário
        while (capacity < vec.size()) {
            resize();
        }
        
        for (size_t i = 0; i < vec.size(); ++i) {
            dynamicArray[i] = vec[i];
        }
        currentSize = vec.size();
    } else {
        data = vec;
    }
}

std::string VectorStructure::getType() const {
    return isDynamic ? "Dynamic Vector" : "Linear Vector";
}

size_t VectorStructure::size() const {
    return data.size();
}

bool VectorStructure::empty() const {
    return data.empty();
}
