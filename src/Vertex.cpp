#include "Vertex.h"

Vertex::Vertex() {}

Vertex::Vertex(uint32_t _vid) : vid(_vid) {}

bool Vertex::operator < (const Vertex& right) const
{
	return vid < right.vid;
}

Vertex Vertex::Min()
{
	static Vertex v(std::numeric_limits< uint32_t >::min());
	return v;
}

Vertex Vertex::Max()
{
	static Vertex v(std::numeric_limits< uint32_t >::max());
	return v;
}
