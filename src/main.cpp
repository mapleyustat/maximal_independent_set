#include "Edge.h"
#include "PQElem.h"
#include "stxxl_params.h"
#include <stxxl.h>
#include <iostream>
#include <cstdlib>
#include <ctime>


typedef stxxl::PRIORITY_QUEUE_GENERATOR< PQElem, MorePrio,
    PQ_M, 256 >::result PriorityQueue;

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
    os << "[" << e.priority << "]("
        << (e.inIndependentSet ? "true" : "false") << ")";
    return os;
};

void Populate(stxxl::vector< Edge >& adjList, VertexId maxV)
{
    srand ( static_cast<unsigned>( time(0) ) );

    for(int i=1;i<maxV;i++)
        for(int j=i+1;j<=maxV;j++)
        {
            //if( rand() & 0x1 )
            if( rand() %10 == 0 )
                adjList.push_back( Edge(i,j) );
        }
}

void Input(stxxl::vector< Edge >& adjList)
{
    VertexId a,b;

    while( std::cin>>a>>b )
        adjList.push_back( Edge(a,b) );
}


bool pop_PQ( PriorityQueue& pq )
{
    VertexId u;
    bool is_independent=false;

    if( !pq.empty() )
        u = pq.top().priority;


    while( !pq.empty() && pq.top().priority == u )
    {
        is_independent = is_independent || pq.top().inIndependentSet;

        // std::cout << "pop "<<pq.top().priority<<' '<<pq.top().inIndependentSet<<'\n';
        pq.pop();
    }

    return ( ! is_independent );
}

void push_PQ(   PriorityQueue& pq,
                stxxl::vector< Edge >::iterator &i,
                stxxl::vector< Edge >::iterator end,
                bool is_independent )
{
    VertexId u;

    if( i!=end )
        u=i->u.vid;

    while( i!=end && i->u.vid == u )
    {
        pq.push( PQElem( i->v.vid, is_independent ) );
        // std::cout<<"push "<< i->v.vid <<' '<< is_independent<<'\n';
        ++i;
    }
}

void FindMIS(stxxl::vector< Edge >& adjList,
    stxxl::vector< Vertex >& indSet)
{
    PriorityQueue pq(PREFETCH_M, WRITE_M);

    // Sort list by edge source
    if ( !stxxl::is_sorted(adjList.begin(), adjList.end(), LessEdgeSrc()) )
        stxxl::sort(adjList.begin(), adjList.end(), LessEdgeSrc(), SORT_M);

    for (auto it = adjList.begin(); it != adjList.end();)
    {
        VertexId u = it->u.vid;

        if( pq.empty() || pq.top().priority > u )
        {
            indSet.push_back(u);

            //std::cout<<'\n'<<u<<"\n\n";

            push_PQ( pq,it, adjList.end(),true );
        }

        else if ( pq.top().priority <= u )
        {
            VertexId v = pq.top().priority;

            bool is_independent = pop_PQ( pq );

            if( is_independent )
            {
                indSet.push_back(v);
                //std::cout << '\n' << v << "\n\n";
            }

            if( v == u )
                push_PQ( pq, it, adjList.end(), is_independent );
        }
    }

    while( !pq.empty() )
    {
        VertexId v = pq.top().priority;

        bool is_independent = pop_PQ( pq );

        if( is_independent )
        {
            indSet.push_back(v);
            //std::cout << '\n' << v << "\n\n";
        }
    }
}

int main(int argc, char const *argv[])
{
    stxxl::stats_data stats_begin(*stxxl::stats::get_instance());

    stxxl::vector< Edge > adjList;

    if( argc>1 )
        Populate(adjList,atol(argv[1]));
    else
        Input(adjList);

    // Edge list
    // std::cout << adjList;

    stxxl::vector< Vertex > indSet;
    FindMIS(adjList, indSet);

    // Maximal independent set
    std::cout << "\n\n" << indSet << "\n\n";

    stxxl::stats_data stats_end(*stxxl::stats::get_instance());
    std::cout << stats_end - stats_begin;

    return 0;
}