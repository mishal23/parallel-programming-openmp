/*
    Value of Pie (Monte Carlo Simulation) - Thread Safe random generator

    References:
        https://github.com/Team-initrd/lfprng
	https://github.com/lat/esc
*/
#include "bits/stdc++.h"
#include "omp.h"

#define RNG_MOD 0x80000000

static unsigned long long MULTIPLIER  = 764261123;
static unsigned long long PMOD        = 2147483647;
static unsigned long long mult_n;
double random_low, random_hi;

#define MAX_THREADS 128
static unsigned long long pseed[MAX_THREADS][4]; //[4] to padd to cache line
                                                 //size to avoid false sharing

void seed(double, double);
double drandom();
unsigned long long random_last = 0;
#pragma omp threadprivate(random_last)

double serial(int n)
{
    int i, count;
    double x,y,pi;

    count = 0;
    for(i=0; i<n; i++) 
    {
        x = drandom();
        y = drandom();
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
    int i, count=0;
    double x,y,pi;

    count = 0;
    #pragma omp parallel for private(x, y, i) reduction(+:count) 
        for(i=0; i<n; i++) 
        {
            x = drandom();
            y = drandom();
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
    int n;
    seed(0.0, 1.0);
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

double drandom()
{
        unsigned long long random_next;
        double ret_val;

/* 
 * compute an integer random number from zero to mod
 */
        random_next = (unsigned long long)((mult_n  * random_last)% PMOD);
        random_last = random_next;

/*
 * shift into preset range
 */
        ret_val = ((double)random_next/(double)PMOD)*(random_hi-random_low)+random_low;
        return ret_val;
}

/*
 * set the seed, the multiplier and the range
 */
void seed(double low_in, double hi_in)
{
     int i, id, nthreads;
     unsigned long long iseed;
     id = omp_get_thread_num();

     #pragma omp single
     {
            if(low_in < hi_in)
            { 
                 random_low = low_in;
                 random_hi  = hi_in;
            }
            else
            {
                 random_low = hi_in;
                 random_hi  = low_in;
            }
    
/*
 * The Leapfrog method ... adjust the multiplier so you stride through
 * the sequence by increments of "nthreads" and adjust seeds so each 
 * thread starts with the right offset
 */

            nthreads = omp_get_num_threads();
            iseed = PMOD/MULTIPLIER;     // just pick a reasonable seed
            pseed[0][0] = iseed;
            mult_n = MULTIPLIER;
            for (i = 1; i < nthreads; ++i)
            {
                iseed = (unsigned long long)((MULTIPLIER * iseed) % PMOD);
                pseed[i][0] = iseed;
                mult_n = (mult_n * MULTIPLIER) % PMOD;
            }
     }
     random_last = (unsigned long long) pseed[id][0];
}
