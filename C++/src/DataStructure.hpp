#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

#include <vector>
#include <string>

/**
 * Classe base abstrata para diferentes estruturas de dados
 * Define interface comum para operações básicas
 */
class DataStructure
{
protected:
    std::vector<int> data;
    bool isDynamic;

public:
    DataStructure(bool dynamic = false) : isDynamic(dynamic) {}
    virtual ~DataStructure() = default;

    // Métodos virtuais puros que devem ser implementados pelas classes filhas
    virtual void insert(int value) = 0;
    virtual void clear() = 0;
    virtual std::vector<int> toVector() const = 0;
    virtual void fromVector(const std::vector<int> &vec) = 0;
    virtual std::string getType() const = 0;

    // Métodos comuns
    virtual size_t size() const { return data.size(); }
    virtual bool empty() const { return data.empty(); }
    virtual bool getDynamic() const { return isDynamic; }

    // Operador de stream para facilitar impressão
    friend std::ostream &operator<<(std::ostream &os, const DataStructure &ds);
};

#endif