#include "bits/stdc++.h"
#include "omp.h"
using namespace std;
void comp1()
{
	int count=100;
	#pragma omp parallel
  		#pragma omp single
  		{
  			while (count>0) 
  			{
  				#pragma omp task
  				{
  					int countcopy = count;
  					if (count==50) 
  					{
  						printf("%d ", count);
  					}
  				}
  				count--;
  			}
  			printf("%d\n",count );
  		}       

  	
}
void comp2()
{
		
	#pragma omp parallel
  		#pragma omp single
  		{
  			int count=100;
  			while (count>0) 
  			{
  				#pragma omp task
  				{
  					int countcopy = count;
  					if (count==50) 
  					{
  						printf("%d ", count);
  					}
  				}
  				// printf("%d ", count);
  				count--;
  			}

  		}       

  	// printf("%d\n",count );
}
int main()
{
	comp1();
	comp2();	
}
