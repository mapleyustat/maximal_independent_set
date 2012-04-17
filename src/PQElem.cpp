#include "PQElem.h"

PQElem::PQElem() : priority(0), vid(0), inIndependentSet(false) {}

PQElem::PQElem(VertexId prio, VertexId _vid, bool inIndep)
	: priority(prio), vid(_vid), inIndependentSet(inIndep) {}

bool MorePrio::operator () (const PQElem& left, const PQElem& right) const
{
	return left.priority > right.priority;
}

PQElem MorePrio::min_value ()
{
	static PQElem pqe(std::numeric_limits< VertexId >::max(), 0, false);
	return pqe;
}

PQElem MorePrio::max_value ()
{
	static PQElem pqe(std::numeric_limits< VertexId >::min(), 0, false);
	return pqe;
}