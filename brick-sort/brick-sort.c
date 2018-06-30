/*

*/
#include "stdio.h"
#include "omp.h"
long long int a[10000001],n;
void brick_sort_serial()
{
	long long int i,j,temp;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(a[j]>a[j+1])
			{
				temp = a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
}

void brick_sort_static(int chunk_size)
{
	long long int i, phase, temp;
	#pragma omp parallel shared(a,n, chunk_size) private(i,temp,phase)
	 for(phase=0;phase<n;phase++)
	 {
	 	if(phase%2 == 0)
	 	{
	 		#pragma omp for schedule(static,chunk_size)
	 			for(i=1;i<n;i+=2)
	 			{
	 				if(a[i-1]>a[i])
	 				{
	 					temp=a[i-1];
	 					a[i-1]=a[i];
	 					a[i]=temp;
	 				}
	 			}
	 	}
	 	else
	 	{
	 		#pragma omp for schedule(static,chunk_size)
	 			for(i=1;i<n-1;i+=2)
	 			{
	 				if(a[i]>a[i+1])
	 				{
	 					temp=a[i];
	 					a[i]=a[i+1];
	 					a[i+1]=temp;
	 				}
	 			}
	 	}
	 }
}

void brick_sort_dynamic(int chunk_size)
{
	long long int i, phase, temp;
	#pragma omp parallel shared(a,n, chunk_size) private(i,temp,phase)
	 for(phase=0;phase<n;phase++)
	 {
	 	if(phase%2 == 0)
	 	{
	 		#pragma omp for schedule(dynamic,chunk_size)
	 			for(i=1;i<n;i+=2)
	 			{
	 				if(a[i-1]>a[i])
	 				{
	 					temp=a[i-1];
	 					a[i-1]=a[i];
	 					a[i]=temp;
	 				}
	 			}
	 	}
	 	else
	 	{
	 		#pragma omp for schedule(dynamic,chunk_size)
	 			for(i=1;i<n-1;i+=2)
	 			{
	 				if(a[i]>a[i+1])
	 				{
	 					temp=a[i];
	 					a[i]=a[i+1];
	 					a[i+1]=temp;
	 				}
	 			}
	 	}
	 }
}

void brick_sort_guided(int chunk_size)
{
	long long int i, phase, temp;
	#pragma omp parallel shared(a,n) private(i,temp,phase)
	 for(phase=0;phase<n;phase++)
	 {
	 	if(phase%2 == 0)
	 	{
	 		#pragma omp for schedule(guided,chunk_size)
	 			for(i=1;i<n;i+=2)
	 			{
	 				if(a[i-1]>a[i])
	 				{
	 					temp=a[i-1];
	 					a[i-1]=a[i];
	 					a[i]=temp;
	 				}
	 			}
	 	}
	 	else
	 	{
	 		#pragma omp for schedule(guided,chunk_size)
	 			for(i=1;i<n-1;i+=2)
	 			{
	 				if(a[i]>a[i+1])
	 				{
	 					temp=a[i];
	 					a[i]=a[i+1];
	 					a[i+1]=temp;
	 				}
	 			}
	 	}
	 }
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		long long int i;
		int chunk_size;
		scanf("%lld %d",&n, &chunk_size);
		// int a[n];
		for(i=0;i<n;i++)
		{
			scanf("%lld",&a[i]);
		}

		double serial_start_time, serial_end_time;
		serial_start_time = omp_get_wtime();
		brick_sort_serial();
		serial_end_time = omp_get_wtime();

		double parallel_start_time_static, parallel_end_time_static;
		parallel_start_time_static = omp_get_wtime();
		brick_sort_static(chunk_size);
		parallel_end_time_static = omp_get_wtime();

		double parallel_start_time_dynamic, parallel_end_time_dynamic;
		parallel_start_time_dynamic = omp_get_wtime();
		brick_sort_dynamic(chunk_size);
		parallel_end_time_dynamic = omp_get_wtime();

		double parallel_start_time_guided, parallel_end_time_guided;
		parallel_start_time_guided = omp_get_wtime();
		brick_sort_guided(chunk_size);
		parallel_end_time_guided = omp_get_wtime();

		printf("%lld %d ",n, chunk_size);
		printf("%lf %lf %lf %lf\n", (serial_end_time - serial_start_time), (parallel_end_time_static- parallel_start_time_static), (parallel_end_time_dynamic - parallel_start_time_dynamic), (parallel_end_time_guided - parallel_start_time_guided));
	}
}