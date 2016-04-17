#include <stdio.h>
#include <stdlib.h>
#define true 1;
#define false 0;
void NQueens(int k,int n);
int Place(int k,int i);
//int x[8]={0,0,0,0,0,0,0,0,0};
int* x=0;
int main(void) 
{
	int n=0,k=1;
	int i=0;

	printf("\nEnter the number of queens\n");
	scanf("%d",&n);
	x= malloc(sizeof(int)*n);

	NQueens(k,n);
	return EXIT_SUCCESS;
}

void NQueens(int k,int n)
{
	int i=1;
	int j;

for(i=1;i<=n;i++)
	{
		if(Place(k,i))
			{
				x[k]=i;
				if(k==n)

				{
					printf("\n\nROW\tQUEEN NO\tCOLUMN\n\n");
					
						for(j=1;j<=n;j++)
						{
						printf("%d\t",j);
						printf("%d\t",j);
						printf("%d\n",x[j]);
						}
					printf("\n");
				}
				else
					NQueens(k+1,n);
			}
	}
}

int Place(int k,int i)
{
	int j;
	for(j=1;j<=k-1;j++)
	{
		if((x[j]==i)|| (abs(x[j]-i) == abs(j-k)))
			return 0;

	}
	return 1;
}
