using namespace std;
#include<iostream>
#include<ctime>
#include<time.h>
#include<omp.h>
int row_red(int,int [][] );
int col_red();
int min_r(int,int);
int min_c(int,int);
int size;
int cost[10][10],tmp[10][10];
int main()
{
  
  cout<<"\nEnter no of cities:";
  cin>>size;
  cout<<"\nEnter cost matrix:";
  
  for(int i=0;i<n;i++)
   for(int j=0;j<n;j++)
   {
      cin>>cost[i][j];      
      }
   row_red(n,cost);
}
int row_red(int n,int t[size][size])
{
int m[n];
for(int i=0;i<n;i++)
  m[i]=min(i,n);

}
int min_r(int v,int n)
{
int m=tmp[v][0];
for(int i=1;i<n;i++)
 {
   if(tmp[v][i]<m)
     m=tmp[v][i];
 }
}
int min_c(int v,int n)
{
int m=tmp[0][v];
for(int i=1;i<n;i++)
 {
   if(tmp[i][v]<m)
     m=tmp[i][v];
 }
}
