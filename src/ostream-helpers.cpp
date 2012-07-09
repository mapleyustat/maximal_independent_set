#include "ostream-helpers.h"

std::ostream& operator<<(std::ostream& os, const Vertex& v)
{
    os << v.vid;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Edge& e)
{
    os << "(" << e.u << ", " << e.v << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const PQElem& e)
{
    os << "[" << e.priority << "]("
        << (e.inIndependentSet ? "true" : "false") << ")";
    return os;
}