/*
    Value of Pie (Monte Carlo Simulation) - Random generator

    References:
        http://pubs.opengroup.org/onlinepubs/009695399/functions/rand.html
	https://github.com/lat/esc
*/
#include "bits/stdc++.h"
#include "omp.h"

#define RNG_MOD 0x80000000
int state;

int rand_int(void);
double rand_double(double range);

double serial(int n)
{
    int i,count;
    double x,y,pi;
    for(i=0;i<n;i++)
    {
        x = (double)rand_double(1.0);
        y = (double)rand_double(1.0);
        if((x*x + y*y) <= 1)
        {
                count++;
        }
    }

    pi = ((double)4*count)/n;

    return pi;
}

double parallel(int n)
{
    int i, count;
    double x,y,pi;

    count = 0;

    // removes synchronization issue - hence reduction clause
    #pragma omp parallel for private(x, y, i) reduction(+:count) 
        for(i=0; i<n; i++) 
        {
            x = (double)rand_double(1.0);
            y = (double)rand_double(1.0);
            if((x*x + y*y) <= 1)
            {
                count++;
            }
        }
    
    pi = ((double)4*count)/n;
    
    return pi;
}

int main() 
{
    int i, count, n;
    double x, y, pi;
    n = 1<<30;

    double serial_start_time, serial_end_time;
    double parallel_start_time, parallel_end_time;
    
    // Serial
    serial_start_time = omp_get_wtime();
    double pi_serial = serial(n);
    serial_end_time = omp_get_wtime();

    // Parallel
    parallel_start_time = omp_get_wtime();
    double pi_parallel = parallel(n);
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

int rand_int(void) 
{
   // & 0x7fffffff is equivalent to modulo with RNG_MOD = 2^31
   return (state = (state * 1103515245 + 12345) & 0x7fffffff);
}

double rand_double(double range) 
{
    return ((double)rand_int()) / (((double)RNG_MOD)/range);
}
