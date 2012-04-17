#include "Edge.h"
#include "PQElem.h"
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

std::ostream& operator<<(std::ostream& os, const PQElem& e)
{
    os << "[" << e.priority << "](" << e.vid << ", "
        << (e.inIndependentSet ? "true" : "false") << ")";
    return os;
};

void Populate(stxxl::vector< Edge >& v)
{
    // Edge, Vertex contains no pointers
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
    const uint M = 64 * B; // Main memory use limit in MB
    
    const uint PQM          = 48 * B * 1024 * 1024; // In bytes
    const uint PrefetchM    = 8 * B * 1024 * 1024; // In bytes
	const uint WriteM       = 8 * B * 1024 * 1024; // In bytes

    typedef stxxl::PRIORITY_QUEUE_GENERATOR< PQElem, MorePrio,
        PQM, 1 >::result PriorityQueue;

    stxxl::vector< Edge > edgeList;
    Populate(edgeList);

    PriorityQueue pq(PrefetchM, WriteM);

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

    for (auto &e : edgeList)
    {
        pq.push(PQElem(e.u.vid, e.u.vid, true));
    }

    while (!pq.empty())
    {
        std::cout << pq.top() << ", ";
        pq.pop();
    }
    std::cout << std::endl;

    return 0;
}