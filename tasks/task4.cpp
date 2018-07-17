#include<bits/stdc++.h>
#include<omp.h>
using namespace std;
int main()
{
    omp_set_num_threads(6);
    
    #pragma omp parallel
    {
        int x=omp_get_num_threads();
    
        #pragma omp single
            {
                
                #pragma omp task
                {
                    cout<<"Hi ";
                }
                #pragma omp taskwait
                #pragma omp task
                {
                    cout<<"bye ";
                }
                // cout<<"nice";
            }

           
    }
}