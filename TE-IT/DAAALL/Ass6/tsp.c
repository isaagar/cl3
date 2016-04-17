#include<stdio.h>
#define INFINITY 999
int rowReduce(int cost[][10],int nodes){
	int i,j,flag=0,min,rmin=0;
	for(i=0;i<nodes;i++){
		flag=0;
		min=cost[i][0];
		for(j=0;j<nodes;j++){
			if(cost[i][j]==0){
				flag=1;
				break;
			}	
			else	
				if(min>cost[i][j])
					min=cost[i][j];	
		}
		if(!flag){
			for(j=0;j<nodes;j++){
				if(cost[i][j]!=INFINITY && min!=INFINITY)
					cost[i][j]=cost[i][j]-min;
			}
			if(min!=INFINITY)
				rmin+=min;
		}
	}
	return rmin;
}
int columnReduce(int cost[][10],int nodes){
	int i,j,flag=0,min,cmin=0;
	for(i=0;i<nodes;i++){
		flag=0;
		min=cost[0][i];
		for(j=0;j<nodes;j++){
			if(cost[j][i]==0){
				flag=1;
				break;
			}
			else
				if(min>cost[j][i])
					min=cost[j][i];
		}
		if(!flag){
			for(j=0;j<nodes;j++){
				if(cost[j][i]!=INFINITY && min!=INFINITY)
					cost[j][i]=cost[j][i]-min;
					
			}
			if(min!=INFINITY)
				cmin+=min;
		}
	}
	return cmin;
}
void copy(int cost[][10],int auxCost[][10],int nodes){
	int i,j;
	for(i=0;i<nodes;i++){
		for(j=0;j<nodes;j++)
			auxCost[i][j]=cost[i][j];
	}
	
}
void makeInfinity(int auxCost[][10],int row,int col,int nodes){
	int i;
	for(i=0;i<nodes;i++){
		auxCost[i][col]=INFINITY;
		auxCost[row][i]=INFINITY;
	}
}
void tsp(int cost[][10],int nodes){
	int path[10],p=1,i,j,rmin,cmin,redCost,prevCost,flag=0,auxCost[10][10],minCost[5][2],k=0,min,pos,z;
	path[0]=0;
	rmin=rowReduce(cost,nodes);
	cmin=columnReduce(cost,nodes);
	redCost=rmin+cmin;
	prevCost=redCost;
	while(p<nodes){
		k=0;
		for(i=1;i<nodes;i++){
			flag=0;
			for(j=0;j<p;j++){
				if(path[j]==i)
					flag=1;
			}
			if(!flag){
				copy(cost,auxCost,nodes);
				makeInfinity(auxCost,path[p-1],i,nodes);
				auxCost[i][0]=INFINITY;
				rmin=rowReduce(auxCost,nodes);
				cmin=columnReduce(auxCost,nodes);
				z=path[p-1];
				if(cost[z][i]!=INFINITY)
					redCost=prevCost+rmin+cmin+cost[z][i];
				else	
					redCost=prevCost+rmin+cmin;
				minCost[k][0]=redCost;
				minCost[k][1]=i;
				k++;
			}
		}
		min=minCost[0][0];
		pos=0;
		for(i=1;i<k;i++){
			if(minCost[i][0]<min){
				min=minCost[i][0];
				pos=i;	
			}	
		}
		makeInfinity(cost,path[p-1],minCost[pos][1],nodes);
		j=minCost[pos][1];
		cost[j][0]=INFINITY;
		rowReduce(cost,nodes);
		columnReduce(cost,nodes);
		path[p++]=minCost[pos][1];
		prevCost=minCost[pos][0];
	}
	printf("\nPath:1");
	for(i=1;i<p;i++)
		printf("--->%d",path[i]+1);
		printf("\nCost:%d\n",minCost[pos][0]);
		
}
	


int main(){
	int nodes,cost[10][10],i,j;
	printf("\n\t*****Travelling Salesman Problem******");
	printf("\n Enter the number of nodes:");
	scanf("%d",&nodes);
	printf("\n Enter the cost matrix");
	for(i=0;i<nodes;i++){
		for(j=0;j<nodes;j++){
			if(i==j)
				cost[i][j]=INFINITY;
			else{
				printf("\n Enter cost of edge[%d][%d]:",i,j);
				scanf("%d",&cost[i][j]);
				
			}	
		}
	}
	tsp(cost,nodes);
	return 0;
}
