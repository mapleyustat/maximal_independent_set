#include "mis.h"
#include "PQElem.h"

void FindMIS(stxxl::vector< Edge >& adjList,
    stxxl::vector< Vertex >& indSet)
{
    bool CheckInNeighbours( PriorityQueue& );
    void FlagOutNeighbours(
        PriorityQueue&,
        stxxl::vector< Edge >::iterator&,
        stxxl::vector< Edge >::iterator,
        bool );

    PriorityQueue pq(PREFETCH_M, WRITE_M);

    // Sort list by edge source
    if ( !stxxl::is_sorted(adjList.begin(), adjList.end(), LessEdgeSrc()) )
            stxxl::sort(adjList.begin(), adjList.end(), LessEdgeSrc(), SORT_M);

    // Iterate over Adjacency list
    for (auto it = adjList.begin(); it != adjList.end();)
    {
        VertexId u = it->u.vid; // current source vertex

        if( pq.empty() || pq.top().priority > u ) 
        // u has no in neighbours
        {
            indSet.push_back(u);
            std::cout<<'\n'<<u<<" added to MIS\n\n";

            FlagOutNeighbours( pq,it, adjList.end(),true );
        }

        else if ( pq.top().priority <= u )
        // check top of priority queue
        {
            VertexId v = pq.top().priority;

            bool isIndependent = CheckInNeighbours( pq );

            if( isIndependent )
            {
                indSet.push_back(v);
                std::cout << '\n' << v << " added to MIS\n\n";
            }

            if( v == u )
                FlagOutNeighbours( pq, it, adjList.end(), isIndependent );
        }
    }

    while( !pq.empty() )
    // flush priority queue
    {
        VertexId v = pq.top().priority;

        bool isIndependent = CheckInNeighbours( pq );

        if( isIndependent )
        {
            indSet.push_back(v);
            std::cout << '\n' << v << " added to MIS\n\n";
        }
    }
}

/**
 * Keep popping the priority queue as long as pq.top() priority
 * remains same. Also check whether any of the in neighbours
 * are in the independent set.
 *
 * Return true if none of the in neighbours is in the independent
 * set.
 */
bool CheckInNeighbours( PriorityQueue& pq )
{
    VertexId u;
    bool isDependent = false;

    if( !pq.empty() )
        u = pq.top().priority;


    while( !pq.empty() && pq.top().priority == u )
    {
        isDependent = isDependent || pq.top().inIndependentSet;

        std::cout   << "Popped priority "<< pq.top().priority << " with "
                    << (pq.top().inIndependentSet ? "true" : "false") << '\n';
        pq.pop();
    }

    return ( ! isDependent );
}

void FlagOutNeighbours(   PriorityQueue& pq,
                stxxl::vector< Edge >::iterator &i,
                stxxl::vector< Edge >::iterator end,
                bool isIndependent )
{
    VertexId u;

    if( i!=end )
        u=i->u.vid;

    while( i!=end && i->u.vid == u )
    {
        pq.push( PQElem( i->v.vid, isIndependent ) );
        std::cout   << "Pushed priority "<< i->v.vid << " with "
                    << (isIndependent ? "true" : "false") << '\n';
        ++i;
    }
}
