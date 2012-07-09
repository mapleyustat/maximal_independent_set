#include <iostream>
#include <cstdint>
#include <functional>
#include <limits>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef uint32_t vertex_t ;


struct edge
{
 vertex_t v1;
 vertex_t v2;

 edge() {}

 edge(vertex_t u,vertex_t v)
 	{
 		if(u<v)
 			{
 				v1=u;v2=v;
 			}
 		else
 			{
 				v1=v;v2=u;
 			}

 	}
 bool operator< ( const edge &b ) const
 	{
 		return ( (v1 < b.v1) );  /*|| (v1==b.v1 && v2<b.v2) */
 	}
};


class lessEdgeSrc : public std::binary_function<edge, edge, bool>
{
public:
	bool operator () (const edge& left, const edge& right) const
	{
		return (left < right);
	}

	static edge min_value ()
	{
		return edge( std::numeric_limits< vertex_t >::min(),std::numeric_limits< vertex_t >::min() );
	}

	static edge max_value ()
	{
		return edge( std::numeric_limits< vertex_t >::max(),std::numeric_limits< vertex_t >::max() );
	}
};


 		
                struct priority_q_elem
                {
                        vertex_t priority; // out-neighbour
                        bool is_independant; // 1 if an in-neighbour is in MIS

                        priority_q_elem(vertex_t p, bool c) : priority(p), is_independant(c)
                        {

                        }

                     
                };

		
		struct pq_cmp
 		{
   			bool operator () (const priority_q_elem &a, const priority_q_elem &b) const 
			{ 
				return (a.priority > b.priority); // higher v has less priority
			}
   			
			priority_q_elem min_value() const  
			{ 
				return priority_q_elem( std::numeric_limits< vertex_t >::max(),true ); 
			}
 		};




struct Dgraph
{
 vector< edge > adj_list;


 Dgraph() {}

 Dgraph(vector< edge > edj_list)
 	{

 		sort( edj_list.begin(),edj_list.end(),lessEdgeSrc() );

 		copy( edj_list.begin(),edj_list.end(),back_inserter(adj_list) );

 	}
};






vector< vertex_t > max_independent_set( Dgraph &G);


void add_I_set( vector<vertex_t> &I, vertex_t v );


bool pop_PQ( priority_queue< priority_q_elem, vector< priority_q_elem >, pq_cmp > &Q );


void push_PQ( priority_queue< priority_q_elem, vector< priority_q_elem >, pq_cmp > &Q,
              vector< edge >::iterator &i,
              vector< edge >::iterator end,
              bool is_independent );




int main()
{
        vector< edge > edges;

        vertex_t a,b;


        while(cin>>a>>b)
                edges.push_back( edge(a,b) );


        Dgraph G(edges);

        vector< vertex_t > I = max_independent_set(G);

	cout<<"\n-----------\n";

        for(int i=0;i<I.size();++i)
                cout<<I[i]<<'\n';

	return 0;
}


vector<vertex_t> max_independent_set( Dgraph &G)
{
        vector< vertex_t > ind_set;
        priority_queue< priority_q_elem, vector< priority_q_elem >, pq_cmp > Q;


        vector< edge >::iterator i=G.adj_list.begin();

        while( i!=G.adj_list.end() )
                {
                       vertex_t u = i->v1;

                       if( Q.empty() || Q.top().priority > u )
                                {
                                 add_I_set( ind_set, u );
                                 push_PQ( Q,i, G.adj_list.end(),true );
                                }

                        else if ( Q.top().priority <= u )
                                {
                                 vertex_t v = Q.top().priority;

                                 bool is_independent = pop_PQ( Q );

                                 if( is_independent )
                                        add_I_set( ind_set, v );

                                if( v==u )
                                        push_PQ( Q,i, G.adj_list.end(),is_independent );
                                }
                }
        while( !Q.empty() )
                {
                 vertex_t v = Q.top().priority;

                 bool is_independent = pop_PQ( Q );

                 if( is_independent )
                        add_I_set( ind_set, v );
                }


        return ind_set;
}




void add_I_set( vector< vertex_t > &I, vertex_t v )
{
 I.push_back(v);
 cout<<'\n'<<v<<"\n\n";
}


bool pop_PQ( priority_queue< priority_q_elem, vector< priority_q_elem >, pq_cmp > &Q )
{
 vertex_t u;
 bool is_independent=false;

 if( !Q.empty() )
        u = Q.top().priority;


 while( !Q.empty() && Q.top().priority == u )
        {
        is_independent = is_independent || Q.top().is_independant;
        cout<<"pop "<<Q.top().priority<<' '<<Q.top().is_independant<<'\n';
        Q.pop();
        }

 return ( ! is_independent );
}


void push_PQ( priority_queue< priority_q_elem, vector< priority_q_elem >, pq_cmp > &Q,
              vector< edge >::iterator &i,
              vector< edge >::iterator end,
             bool is_independent )
{
 vertex_t u;

 if( i!=end )
        u=i->v1;

 while( i!=end && i->v1 == u )
        {
         Q.push( priority_q_elem( i->v2, is_independent ) );
         cout<<"push "<<i->v2<<' '<< is_independent<<'\n';
         ++i;
        }
}
