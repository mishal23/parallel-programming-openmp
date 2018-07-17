#include "bits/stdc++.h"
#include "omp.h"
using namespace std;
int main()
{
	
	#pragma omp parallel
	{
		int x = 0;  
		#pragma omp single
		{
			printf("%d\n", omp_get_thread_num());
			#pragma omp task 
	    	{
	        	x++;
	        	printf("from task 1: x = %d %d\n", x, omp_get_thread_num());
	    	}
			#pragma omp taskwait
	    	{
				#pragma omp task 
		    	{
		        	x++;
		        	printf("from task 2: x = %d %d\n", x, omp_get_thread_num());
		    	}
		    }
		}
	}
}