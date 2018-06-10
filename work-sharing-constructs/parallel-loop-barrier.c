/*
	Work Sharing Construct - Parallel Loops (Know about barrier)
*/
#include "stdio.h"
#include "omp.h"
int main()
{
	int i,a[10],b[10];
	int n=10;
	#pragma omp parallel shared(n,a,b) private(i)
	{
		#pragma omp for
			for (i=0; i<n; i++)
			{
				a[i] = i;
				printf("a[%d] = %d\n", i,a[i]);
			}
		
		#pragma omp for
			for (i=0; i<n; i++)
			{
				b[i] = 2 * a[i];
				printf("b[%d] = %d\n",i, b[i] );
			}
	}	
}

