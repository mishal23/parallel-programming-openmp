#include "bits/stdc++.h"
#include "omp.h"
using namespace std;
int main()
{
	#pragma omp parallel
	{
		#pragma omp single
		{
			#pragma omp task
			{
				cout<<"hi "<<endl;
			}
			#pragma omp task
			{
				cout<<"bye "<<endl;
			}
		}
	}
}