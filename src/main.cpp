#include <stxxl.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "stxxl_params.h"
#include "Edge.h"
#include "PQElem.h"
#include "ostream-helpers.h"
#include "mis.h"


void Populate(stxxl::vector< Edge >& adjList, VertexId maxV, long p)
{
    srand ( static_cast<unsigned>( time(0) ) );

    for(uint i=1;i<maxV;i++)
        for(uint j=i+1;j<=maxV;j++)
        {
            if( rand() %p == 0 )
                adjList.push_back( Edge(i,j) );
        }
}

void Input(stxxl::vector< Edge >& adjList)
{
    VertexId a,b;

    while( std::cin>>a>>b )
        adjList.push_back( Edge(a,b) );
}

int main(int argc, char const *argv[])
{
    stxxl::stats_data stats_begin(*stxxl::stats::get_instance());

    /*
        Tp_ type of contained objects (POD with no references to internal memory)
        PgSz_ number of blocks in a page
        PgTp_ pager type, random_pager<x> or lru_pager<x>, where x is number of pages, default is lru_pager<8>
        BlkSize_ external block size in bytes, default is 2 MiB
        AllocStr_ one of allocation strategies: striping , RC , SR , or FR default is RC 
        Memory consumption: BlkSize_*x*PgSz_ bytes
    */
    stxxl::vector< Edge, 4, stxxl::lru_pager<8> > adjList;

    if( argc>1 )
        Populate(adjList,atol(argv[1]),atol(argv[2]));
    else
        Input(adjList);

    // Edge list
    std::cout << "\n\nEdge List:\n" << adjList;

    stxxl::vector< Vertex, 4, stxxl::lru_pager<8> > indSet;
    FindMIS(adjList, indSet);

    // Maximal independent set
    std::cout << "\nMIS:\n" << indSet << "\n\n";

    stxxl::stats_data stats_end(*stxxl::stats::get_instance());
    std::cout << stats_end - stats_begin;

    return 0;
}
