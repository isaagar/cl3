#include <stdio.h>
#include <stdlib.h>
#define max 25
int x[max];
int flag=0;
void Nextvalue(int G[max][max],int n,int k)
{
	int j;
	while (1)
	{
		x[k]=(x[k]+1)%(n+1);		//Next value
		if(x[k]==0)
			return;
		if(G[x[k-1]][x[k]]!=0)		//Is there any edge between vertices
		{
			for(j=1;j<=k-1;j++)
			{
				if(x[j]==x[k])
					break;
			}
			if(j==k) //if true then vertex is distinct
			{
				if((k<n) || ((k==n) && (G[x[n]][x[1]]!=0)))
					return;
			}
		}
	}
}

void hc(int G[][max],int n,int k)
{
	int i;
	while(k<=n && k!=1)
	{
		Nextvalue(G,n,k);//Assign legal next value for x[k]

		if(x[k]==0)
			k--;
		else if(k==n)
		{
		flag=1;			
		printf("\n\nHamiltonian Cycle present in the graph ::");			
			printf("\n");
			for(i=1;i<=n;i++)
				printf("%d",x[i]);
			printf("%d",x[1]);
			k--;
			
		}
		else
			
			k++;
	}
}
void main()
{
	int i,j,v1,v2,edges,n,G[max][max];
	printf("\nEnter number of vertices ::");
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			G[i][j]=0;
			x[i]=0;
		}
	}
	printf("\nEnter total number of edges::");
	scanf("%d",&edges);

	for(i=1;i<=edges;i++)
	{
		printf("\nEnter edge %d::",i);
		scanf("%d%d",&v1,&v2);
		G[v1][v2]=1;
		G[v2][v1]=1;
	}
	x[1]=1;
	
	hc(G,n,2);
	if (flag==0)
		printf ("\n\nHamiltonian Cycle is not present in the graph ::");
}

