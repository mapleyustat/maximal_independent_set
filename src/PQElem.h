#pragma once
#include "Vertex.h"

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