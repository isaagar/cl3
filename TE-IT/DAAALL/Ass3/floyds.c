#include<stdio.h>
#include<math.h>
#define MAX 9999
#define NIL -1
/*Function to get the shortest path*/
void print_shortest(int path[10][10],int i,int j);
void print_shortest(int path[10][10],int i,int j)
{
if(i==j)
{
return;
}
else if(path[i][j]==-1)
{
printf("path not exists");
return;
}
else
{
print_shortest(path,i,path[i][j]);
printf(" %d->",j);
}
}
/*Main function*/
void main()
{
int p[10][10],m[10][10],n,x,y,e,u,v,i,j,w,k;
int path[10][10];
printf("\n Enter the number of vertices:");
//Accept the number of edges and vertices of input graph
scanf("%d",&n);
printf("\n Enter the number of edges:");
scanf("%d",&e);
for(i=1;i<=n;i++) //Initialization of matrix representation of input graph
{
for(j=1;j<=n;j++)
{
m[i][j]=MAX;
path[i][j]=MAX;
if(i==j)
{
path[i][j]=-1;
//For diagonal elements
m[i][j]=0;
}
else{
path[i][j]=i;
}
}
}
for(i=1;i<=e;i++) //Accept the weights of the input weighted graph
{
printf("\n Enter the end vertices of edge %d:",i);
scanf("%d%d",&u,&v);
printf("\nEnter the weight :");
scanf("%d",&w);
m[u][v]=w;
}
printf("\n Matrix of input data: \n");
//Print the matrix representation of
the input graph
for(i=1;i<=n;i++)
{
for(j=1;j<=n;j++)
{
printf("%d\t",m[i][j]);
}
printf("\n");
}
for(i=1;i<=n;i++)
//Initialization of distance matrix
{
for(j=1;j<=n;j++)
{
p[i][j]=m[i][j];
}
}
for(k=1;k<=n;k++)
//Initialization of predecessor matrix
{
for(i=1;i<=n;i++)
{
for(j=1;j<=n;j++)
{
if(p[i][j]>p[i][k]+p[k][j])
{
p[i][j]=p[i][k]+p[k][j];
path[i][j]=path[k][j];
}
}
}
printf("\nIntermediate matrix--\n");
for(x=1;x<=n;x++)
{
for(y=1;y<=n;y++)
{
printf("%d\t",p[x][y]);
}
printf("\n");
}
}
printf("\n Transitive Closure: \n");
for(i=1;i<=n;i++)
//Print the transitive closure{
int q[20][20];
for(j=1;j<=n;j++)
{
if(p[i][j] > 0)
{
q[i][j]=1;
}
else
q[i][j]=0;
printf("%d\t",q[i][j]);
}
printf("\n");
}
printf("\n Print Path: \n"); //Print the path for each pair of vertices
for(i=1;i<=n;i++)
{
for(j=1;j<=n;j++)
{
printf("Shortest Path from %d,%d : \t",i,j);
if(i!=j)
{
printf("%d->",i);
print_shortest(path,i,j);
}
else
{
printf("Path not found ( No Self loop)");
}
printf("\n");
}
}
}
