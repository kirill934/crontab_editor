#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort(int *a, unsigned int beg, unsigned int end);
void merge(int *a, unsigned int beg, unsigned int mid, unsigned int end);

int main(void)
{
	unsigned int N;
	clock_t t;
	FILE *file=fopen("sort_times","w");

	for(N=10000;N<1000000;N+=10000)
	{
		int arr[N];
		srand(time(NULL));
		for(unsigned int i=0;i<N;i++)
		{
			arr[i]=rand() % 100;
			//printf("%d	",arr[i]);
		}
		//printf("\n");
		t=clock();
		sort(arr,0,N-1);
		t=clock()-t;
		//for(int i=0;i<N;i++)
			//printf("%d	",arr[i]);
		//printf("\n");
		//printf("Time for sorting: %d(%f sec)\n",t,((float)t)/CLOCKS_PER_SEC);
		fprintf(file,"%f\n",((float)t)/CLOCKS_PER_SEC);
	}
}
void sort(int *a, unsigned int beg, unsigned int end)
{
	//printf("Now sorting [%d-%d]\n",beg,end);
	unsigned int i;
	if(end > beg+1)
	{
		i=(beg+end)/2;
		sort(a,beg,i);
		sort(a,i+1,end);
		merge(a,beg,i+1,end);
	}
	else
		merge(a,beg,beg+1,end);
}
//merge two arrays with sorting
void merge(int *a, unsigned int beg, unsigned int mid, unsigned int end)
{
	unsigned int N=mid-beg;
	unsigned int M=end-mid+1;
	unsigned int i,j,v;
	int b[N+1];
	int c[M+1];
	for(i=0;i<N;i++)
		b[i]=a[beg+i];
	for(i=0;i<M;i++)
		c[i]=a[mid+i];
	v= (b[N-1] > c[M-1]) ? b[N-1]+1 : c[M-1]+1;
	b[N]=v;
	c[M]=v;
	i=0;	//for b[]
	j=0;	//for c[]
	a+=beg;
	while(i<N || j<M)
	{
		if( b[i] < c[j] )
			*(a++)=b[i++];
		else
			*(a++)=c[j++];
	}
}
