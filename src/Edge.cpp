#include "Edge.h"

Edge::Edge() {}

Edge::Edge(Vertex _u, Vertex _v) : u(_u), v(_v) {}

bool Edge::LessSrc (const Edge& right) const
{
	return u < right.u;
}

bool Edge::LessDest (const Edge& right) const
{
	return v < right.v;
}

Edge Edge::Min()
{
	static Edge e(Vertex::Min(), Vertex::Min());
	return e;
}

Edge Edge::Max()
{
	static Edge e(Vertex::Max(), Vertex::Max());
	return e;
}

bool LessEdgeSrc::operator () (const Edge& left, const Edge& right) const
{
	return left.LessSrc(right);
}

Edge LessEdgeSrc::min_value ()
{
	return Edge::Min();
}

Edge LessEdgeSrc::max_value ()
{
	return Edge::Max();
}

bool LessEdgeDest::operator () (const Edge& left, const Edge& right) const
{
	return left.LessDest(right);
}

Edge LessEdgeDest::min_value ()
{
	return Edge::Min();
}

Edge LessEdgeDest::max_value ()
{
	return Edge::Max();
}
