#pragma once
#include <stdint.h>
#include <limits>

typedef uint32_t VertexId;

struct Vertex
{
	VertexId vid;

	Vertex();
	Vertex(VertexId vid);

	bool operator < (const Vertex& right) const;

	static Vertex Min();
	static Vertex Max();
};