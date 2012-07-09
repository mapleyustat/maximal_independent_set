#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <stxxl.h>

void FindMIS(stxxl::vector< Edge >& adjList,
    stxxl::vector< Vertex >& indSet);