#pragma once
#include "Vertex.h"

struct PQElem
{
	VertexId priority;
	VertexId vid;
	bool inIndependentSet;

	PQElem();
	PQElem(VertexId prio, VertexId vid, bool inIndep);
};

class MorePrio
{
public:
	bool operator () (const PQElem& left, const PQElem& right) const;

	static PQElem min_value ();
	static PQElem max_value ();
};