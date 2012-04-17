#include "Vertex.h"

Vertex::Vertex() {}

Vertex::Vertex(VertexId _vid) : vid(_vid) {}

bool Vertex::operator < (const Vertex& right) const
{
	return vid < right.vid;
}

Vertex Vertex::Min()
{
	static Vertex v(std::numeric_limits< VertexId >::min());
	return v;
}

Vertex Vertex::Max()
{
	static Vertex v(std::numeric_limits< VertexId >::max());
	return v;
}
