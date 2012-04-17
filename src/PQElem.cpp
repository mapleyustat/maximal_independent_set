#include "PQElem.h"

PQElem::PQElem() : priority(0), inIndependentSet(false) {}

PQElem::PQElem(VertexId prio, bool inIndep)
	: priority(prio), inIndependentSet(inIndep) {}

bool MorePrio::operator () (const PQElem& left, const PQElem& right) const
{
	return left.priority > right.priority;
}

PQElem MorePrio::min_value ()
{
	static PQElem pqe(std::numeric_limits< VertexId >::max(), false);
	return pqe;
}

PQElem MorePrio::max_value ()
{
	static PQElem pqe(std::numeric_limits< VertexId >::min(), false);
	return pqe;
}