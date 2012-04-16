#include "Edge.h"
#include <stxxl.h>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Vertex& v)
{
    os << v.vid;
    return os;
};

std::ostream& operator<<(std::ostream& os, const Edge& e)
{
    os << "(" << e.u << ", " << e.v << ")";
    return os;
};

template <class T>
std::ostream& operator<<(std::ostream& os, const stxxl::vector<T>& v)
{
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, ", "));
    os << std::endl;

    return os;
};

void Populate(stxxl::vector< Edge >& v)
{
	v.push_back( Edge(5, 3) );
	v.push_back( Edge(4, 4) );
	v.push_back( Edge(3, 5) );
	v.push_back( Edge(2, 1) );
	v.push_back( Edge(1, 2) );
}

int main(int argc, char const *argv[])
{
	/* STXXL Parameters. */
	const uint B = 2; // Block size is 2 MB (default)
	const uint M = 50 * B; // Main memory use limit

    stxxl::vector< Edge > edgeList;
    Populate(edgeList);

    // Edge list before sorting
    std::cout << edgeList;

    // Sort list by edge source
    stxxl::sort(edgeList.begin(), edgeList.end(), LessEdgeSrc(), M);

    // Edge list after sorting by source
    std::cout << edgeList;

    // Sort list by edge destination
    stxxl::sort(edgeList.begin(), edgeList.end(), LessEdgeDest(), M);

    // Edge list after sorting by destination
    std::cout << edgeList;

    return 0;
}