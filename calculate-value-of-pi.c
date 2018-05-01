/*
	Calculating the value of integral 0 to 1, 4/(1+x^2)

	Cyclic distribution of loop iterations
*/
#include "stdio.h"
#include "omp.h"
static long number_of_steps = 100000;
#define NUMBER_OF_THREADS 4
double step;
double serial()
{
	int i;
	double x,pi,sum=0.0;
	step = 1.0/(double)number_of_steps;
	for(i=0;i<number_of_steps;i++)
	{
		x = (i+0.5)*step;
		sum = sum + 4.0/(1.0 + x*x);
	}
	pi = step*sum;

	return pi;
}

double parallel()
{
	int i, nthreads;
	double  pi, sum[NUMBER_OF_THREADS];
	step = 1.0/(double)number_of_steps;

	omp_set_num_threads(NUMBER_OF_THREADS);

	#pragma omp parallel
	{
		int id,nthrds;
		double x;
		id = omp_get_thread_num();
		nthrds = omp_get_num_threads();
		//
		if(id == 0)
		{
			nthreads = nthrds;
		}
		sum[id] = 0.0;
		for(i=id; i<number_of_steps; i+=nthrds)
		{
			x = (i+0.5)*step;
			sum[id] = sum[id] + 4.0/(1.0 + x*x);
		}
	}

	pi=0.0;
	for(i=0;i<nthreads;i++)
	{
		pi += sum[i]*step;
	}
	return pi;
}

int main()
{
	// Serial Code
	double serial_start_time, serial_end_time;
	double parallel_start_time, parallel_end_time;
	serial_start_time = omp_get_wtime();
	double pi_serial = serial();
	serial_end_time = omp_get_wtime();

	// Parallel Code
	parallel_start_time = omp_get_wtime();
	double pi_parallel = parallel();
	parallel_end_time = omp_get_wtime();

	// Output
	printf("Type     | Value of pi  | Time\n");
	for(int i=0;i<35;i++)
	{
		printf("-");
	}
	printf("\n");
	printf("Serial   | %lf \t| %lf\n", pi_serial , (serial_end_time - serial_start_time)*1000);
	printf("Parallel | %lf \t| %lf\n", pi_parallel , (parallel_end_time - parallel_start_time)*1000);

}