#pragma once
#include <stdint.h>
#include <limits>

struct Vertex
{
	uint32_t vid;

	Vertex();
	Vertex(uint32_t vid);

	bool operator < (const Vertex& right) const;

	static Vertex Min();
	static Vertex Max();
};