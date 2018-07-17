#include "stdio.h"
#include "omp.h"
int fib_serial(int n)
{
	if(n==0 || n==1)
	{
		return n;
	}
	int result, f1,f2;
	f1=fib_serial(n-1);
	f2=fib_serial(n-2);
	result=f1+f2;
	return result;
}

int fib_parallel(int n)
{
	if(n==0 || n==1)
	{
		return n;
	}
	int result, f1,f2;
	#pragma omp parallel
	{
		#pragma omp single
		{
			#pragma omp task shared(f1)
				f1=fib_parallel(n-1);
			#pragma omp task shared(f2)
				f2=fib_parallel(n-2);
			#pragma omp taskwait
				result=f1+f2;
		}		
	}
	return result;
}
int main()
{
	int n;
	scanf("%d",&n);
	double serial_start_time, serial_end_time;
	double parallel_start_time, parallel_end_time;

	parallel_start_time = omp_get_wtime();
	int fibval_parallel = fib_parallel(n);
	parallel_end_time = omp_get_wtime();

	serial_start_time = omp_get_wtime();
	int fibval_serial = fib_serial(n);
	serial_end_time = omp_get_wtime();

	printf("Serial   (Value and Time): %d %lf\n", fibval_serial, serial_end_time - serial_start_time);
	printf("Parallel (Value and Time): %d %lf\n", fibval_parallel, parallel_end_time - parallel_start_time);
}