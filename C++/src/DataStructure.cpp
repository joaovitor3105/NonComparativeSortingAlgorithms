#include "DataStructure.hpp"
#include <iostream>

std::ostream &operator<<(std::ostream &os, const DataStructure &ds)
{
    os << "DataStructure Type: " << ds.getType()
       << " | Size: " << ds.size()
       << " | Dynamic: " << (ds.getDynamic() ? "Yes" : "No");
    return os;
}