/*
	Work Sharing Construct - Sections
*/
#include "stdio.h"
#include "omp.h"
void functionA()
{
	printf("FunctionA: Executed by thread %d\n", omp_get_thread_num());
}
void functionB()
{
	printf("FunctionB: Executed by thread %d\n", omp_get_thread_num());
}

int main()
{
	#pragma omp parallel 
	{
		#pragma omp sections
		{
			#pragma omp section
				functionA();
		        #pragma omp section
				functionB();
		}
	}
}
