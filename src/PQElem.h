#pragma once
#include "stxxl_params.h"
#include "Vertex.h"
#include <stxxl.h>

struct PQElem
{
	VertexId priority;
	bool inIndependentSet;

	PQElem();
	PQElem(VertexId prio, bool inIndep);
};

class MorePrio
{
public:
	bool operator () (const PQElem& left, const PQElem& right) const;

	static PQElem min_value ();
	static PQElem max_value ();
};

typedef stxxl::PRIORITY_QUEUE_GENERATOR< PQElem, MorePrio,
    PQ_M, 1024 >::result PriorityQueue;
