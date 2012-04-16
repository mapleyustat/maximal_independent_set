#pragma once
#include "Vertex.h"
#include <functional>

struct Edge
{
	Vertex u;
	Vertex v;

	Edge();
	Edge(Vertex u, Vertex v);

	bool LessSrc (const Edge& right) const;
	bool LessDest (const Edge& right) const;

	static Edge Min();
	static Edge Max();
};

class LessEdgeSrc : public std::binary_function<Edge, Edge, bool>
{
public:
	bool operator () (const Edge& left, const Edge& right) const;

	static Edge min_value ();
	static Edge max_value ();
};

class LessEdgeDest : public std::binary_function<Edge, Edge, bool>
{
public:
	bool operator () (const Edge& left, const Edge& right) const;
	
	static Edge min_value ();
	static Edge max_value ();
};