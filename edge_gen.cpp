#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc,char *argv[])
{
	int n,p;
	srand ( static_cast<unsigned>( time(0) ) );		

	if( argc>2 )
		{
			n=atoi(argv[1]);
			p=atoi(argv[2]);
		}
	else 
		cin>>n>>p;



	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
			{
			 if( rand() %p == 0 )
				{ cout<<i<<' '<<j<<'\n'; }
			}

	return 0;
}
