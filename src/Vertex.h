#pragma once
#include <cstdint>
#include <limits>

typedef uint32_t VertexId;

struct Vertex
{
	VertexId vid;

	// Dummy satellite data
	// char dummy[1024 * 1024 - sizeof(VertexId)]; // Size 1 MB

	Vertex();
	Vertex(VertexId vid);

	bool operator < (const Vertex& right) const;

	static Vertex Min();
	static Vertex Max();
};
