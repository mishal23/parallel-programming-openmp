/*
	Work Sharing Construct - Parallel Loop
*/
#include "stdio.h"
#include "omp.h"
int main()
{
	int i, n =10;
	#pragma omp parallel shared(n) private(i)
	{
		#pragma omp for
			for (i=0; i<n; i++)
				printf("Thread %d executes loop iteration %d\n", omp_get_thread_num(),i);
	}
}

