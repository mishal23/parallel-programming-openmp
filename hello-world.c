#include "omp.h"
#include "stdio.h"
int main()
{
	#pragma omp parallel
	{




	int thread_number = omp_get_thread_num();
		printf("hello %d\n", thread_number);
		printf("world %d\n", thread_number);
	}
}
