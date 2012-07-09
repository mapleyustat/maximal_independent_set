#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc,char *argv[])
{
	int n;
	srand ( static_cast<unsigned>( time(0) ) );		

	if( argc>1 )
		{
			n=atoi(argv[1]);
			
		}
	else 
		cin>>n;



	for(int i=1;i<n;i++)
		cout<< i <<' '<< i+1 <<'\n';
	
	cout<< n <<' '<< 1 <<'\n';		

	return 0;
}
