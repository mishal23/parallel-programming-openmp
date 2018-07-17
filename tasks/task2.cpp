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
#pragma omp task firstprivate(x)
    {
        x++;
        printf("from task 1: x = %d\n", x);
    }
#pragma omp taskwait

#pragma omp task firstprivate(x)
    {
        x++;
        printf("from task 2: x = %d\n", x);
    }
}
}
}