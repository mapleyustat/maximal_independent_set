#pragma once
#include "Vertex.h"
#include "Edge.h"
#include "PQElem.h"
#include <stxxl.h>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Vertex& v);

std::ostream& operator<<(std::ostream& os, const Edge& e);

template <class T>
std::ostream& operator<<(std::ostream& os, const stxxl::vector<T>& v)
{
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, ", "));
    os << std::endl;

    return os;
}

std::ostream& operator<<(std::ostream& os, const PQElem& e);