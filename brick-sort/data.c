#include "stdio.h"
#include "stdlib.h"
int main()
{
	int test=10,i;
	printf("%d\n",test);
	while(test--)
	{
		int n=rand()%1000000;
		printf("%d %d\n", n, (rand()%6) +1);
		for(i=0;i<n;i++)
		{
			printf("%d ",rand()%100);
		}
		printf("\n");
	}
}