#include<iostream>
#include<ctime>
#include<time.h>
#include<omp.h>
#define SIZE 10
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int cities[SIZE][SIZE],reduction[SIZE],visited[SIZE]={0},copy_matrix[SIZE][SIZE],sum_temp[SIZE]={0},path_min[SIZE]={0},cost_path[SIZE][SIZE],reference[SIZE][SIZE],reference_1[SIZE][SIZE]; 

void display(int size);
void row_reduction_copy( int size ,int ); 	//  ROW REDUCTION OF MATRIX 
void col_reduction_copy( int size ,int );	//  COLUMN REDUCTION OF MATRIX
int  sum(int size);				//  COST CALCULATION OF NODE 
int  minimum(int size);				//  SELECTING MINIMUM COST NODE 
///////////////////////////////////////////////////////////////

int main()
{
	int size,r_bound,c_bound,lower_bound,path_cost=0 ,tid ;
	clock_t begin = clock();	//  MEASURING THE TIME 
	time_t start,end;
	time (&start);
	cout<<"ENTER NUMBER OF CITIES ..."<<endl;  // TAKING INPUT 
	cin>>size;
	for(int i=1;i<=size;i++)
	{
		for(int j=1;j<=size;j++)
		{
			cout<<"ENTER THE DISTANCE   "<<i<<"----->  "<<j<<"  :  ";
			cin>>cities[i][j];
			if(cities[i][j]<0)
			{
				cout<<"ENTER ONLY POSITIVE EDGES "<<endl;	// CHECKING POSITIVE EDGES 
				j--;
			}
	
		}
	}
	
	for(int i = 1;i<=size;i++)		// COPYING ORIGINAL MATRIX FOR COST CALCULATION LATER 
	{
		for(int j=1;j<=size;j++)
		{
			cost_path[i][j] = cities[i][j]; 
		}
	}
	row_reduction_copy(size,0);
	r_bound = sum(size);
	col_reduction_copy(size,0);
	c_bound = sum(size);
	lower_bound = r_bound + c_bound;
	sum_temp[1] = lower_bound;
	visited[1]=1;
	int selected_vertex,count = 0,prev_vertex = 1,counter = 2;

	for(int i = 1;i<=size;i++)		// COPYING ORIGINAL MATRIX FOR REFERENCE  LATER 
	{
		for(int j=1;j<=size;j++)
		{
			reference_1[i][j] = cities[i][j]; 
			reference[i][j]   = cities[i][j];
		}
	}
	for(int i = 1;i<=size;i++)		
	{
		reference[1][i] = 99999;
	}

	while(counter <= size)			// LOOP FOR VISITING ALL VERTICES 
	{		
		for(int i = 1;i<=size;i++)
		{
			for(int j=1;j<=size;j++)
			{
			copy_matrix[i][j] = reference[i][j]; 	// MAKING  A COPY OF ORIGINAL MATRIX TO PERFORM OPERATION
			}
		} 
		for(int i = 1;i<=size;i++)		// RESETTING THE SUM MATRIX 
		{
			if(visited[i]==1)
			continue;
			sum_temp[i]=0;		
		}

		#pragma omp parallel for  
		for(int k = 1;k<=size;k++)	// PARALLEL SECTION 
		{
			if (visited[k] == 0)
			{			
				selected_vertex = k;	// SELECTING THE UNVISITED NODE
				
			} 
			#pragma omp critical
			{
			for(int i = 1;i<=size;i++)
			{
				copy_matrix[prev_vertex][i] = 99999;
				copy_matrix[i][selected_vertex]	= 99999;	
			}	 
				copy_matrix[selected_vertex][1] = 99999;
				
				row_reduction_copy(size,1);
				//display(size);
				sum_temp[selected_vertex] = sum(size);
				col_reduction_copy(size,1);
				//display(size);
				sum_temp[selected_vertex]+=sum(size);
				sum_temp[selected_vertex]+=sum_temp[prev_vertex];
				sum_temp[selected_vertex]+=reference_1[prev_vertex][selected_vertex];
				
				
			for(int i = 1;i<=size;i++)
			{
				for(int j=1;j<=size;j++)
				{
					copy_matrix[i][j] = reference[i][j]; 
				}
			}
			}
		}
		for(int a = 1;a<=size;a++)
		cout<<sum_temp[a]<<"\t";
		cout<<endl;
		int index = minimum(size);
		cout<<"SELECTED IS  :"<<index<<endl;
	
		for(int i = 1;i<=size;i++)		// SELECTING MATRIX FOR NEXT ITERATION 
		{
			reference[1][i] = 99999;
			reference[index][i]= 99999;	
		}	
		visited[index]=1;	
		prev_vertex = index;
		
		path_min[1] = 1;
		path_min[counter] = index;

	counter++;	
	}

	path_min[size+1]=1;
	for(int i =1 ;i<=size+1;i++)
	cout<<path_min[i]<<"\t";
	cout<<endl;
	for(int i =1 ;i<=size;i++)
	{
		int row , col;
		row = path_min[i];
		col = path_min[i+1];
		path_cost+=cost_path[row][col];

	}
	cout<<"THE PATH COST IS :  "<<path_cost<<endl;
	time (&end);
	double dif = difftime (end,start);
	cout<<"Time taken (seconds)  : "<<dif/1000<<endl;
return 0;
}

//////////////////////////////////////////////////////////////
void display(int size)
{
	cout<<"THE MATRIX  IS : "<<endl;
	for(int i=1;i<=size;i++)
	{
		for(int j=1;j<=size;j++)
		{
			cout<<copy_matrix[i][j]<<"\t";
		}
			cout<<endl;
	}
cout<<endl;
} 

////////////////////////////////////////////////////////////////////

int sum(int size)
{
	int total = 0;
	for(int i = 0;i <= size;i++)
	{
		total+=reduction[i];
	}
return total;
}

/////////////////////////////////////////////////////////////////////

void row_reduction_copy(int size,int flag)
{
	if(flag==0)
	{
	int min ;
	for(int i=1;i<=size;i++)
	{
		min = 999;
		for(int j=1;j<=size;j++)
		{
			if (cities[i][j] == 99999)
				continue;
			else
			{
				if (cities[i][j] < min)
				{
					min = cities[i][j];
				}

			}
		}
		if (min == 999)
		reduction[i]=0;
		else
		reduction[i] = min;
		for(int j=1;j<=size;j++)
		{
			if (cities[i][j] == 99999)
				continue;
			else
			cities[i][j] = cities[i][j] - min; 
		}
	}
	}
	else
	{
		int min ;
	for(int i=1;i<=size;i++)
	{
		min = 999;
		for(int j=1;j<=size;j++)
		{
			if (copy_matrix[i][j] == 99999)
				continue;
			else
			{
				if (copy_matrix[i][j] < min)
				{
					min = copy_matrix[i][j];
				}

			}
		}
		if (min == 999)
		reduction[i]=0;
		else
		reduction[i] = min;
		for(int j=1;j<=size;j++)
		{
			if (copy_matrix[i][j] == 99999)
				continue;
			else
			copy_matrix[i][j] = copy_matrix[i][j] - min; 
		}
	}



	}		
}
///////////////////////////////////////////////////////////////////////////

void col_reduction_copy(int size,int flag)
{
	if(flag==0)
	{	
	int min;
	for(int i=1;i<=size;i++)
	{
		min = 999;
		for(int j=1;j<=size;j++)
		{
			if (cities[j][i] == 99999)
				continue;
			else
			{
				if (cities[j][i] < min)
				{
					min = cities[j][i];
				}

			}
		}
		if (min == 999)
		reduction[i]=0;
		else
		reduction[i] = min;
		for(int j=1;j<=size;j++)
		{
			if (cities[j][i] == 99999)
				continue;
			else
			cities[j][i] = cities[j][i] - min; 
		}
	}
	}
	else
	{
		int min;
	for(int i=1;i<=size;i++)
	{
		min = 999;
		for(int j=1;j<=size;j++)
		{
			if (copy_matrix[j][i] == 99999)
				continue;
			else
			{
				if (copy_matrix[j][i] < min)
				{
					min = copy_matrix[j][i];
				}

			}
		}
		if (min == 999)
		reduction[i]=0;
		else
		reduction[i] = min;
		for(int j=1;j<=size;j++)
		{
			if (copy_matrix[j][i] == 99999)
				continue;
			else
			copy_matrix[j][i] = copy_matrix[j][i] - min; 
		}
	}	
	}
}

//////////////////////////////////////////////////////////////////////////
int minimum(int size)
{
	int min = 999,in;
	for(int i=1;i<=size;i++)
	{
		if (visited[i] ==1)
		continue;
		else
		{
			if (sum_temp[i] < min)
				min = sum_temp[i];
		}	
	}
	for(int i=1;i<=size;i++)
	{
		if(visited[i]== 1)
		continue;		
		else if(sum_temp[i] == min)
		{
		in = i;
		break;
		}

	}
return in;	
}
/////////////////////////////////////////////////////////////////////////////

/******************** 		OUTPUT 

rohan@rohan-HP-ProBook-4410s:~/Dropbox/7_SEMESTER$ 
rohan@rohan-HP-ProBook-4410s:~/Dropbox/7_SEMESTER$ g++ -fopenmp tsp_parallel.cpp
rohan@rohan-HP-ProBook-4410s:~/Dropbox/7_SEMESTER$ ./a.out
ENTER NUMBER OF CITIES ...
5
ENTER THE DISTANCE   1----->  1  :  -1
ENTER ONLY POSITIVE EDGES 
ENTER THE DISTANCE   1----->  1  :  99999
ENTER THE DISTANCE   1----->  2  :  11
ENTER THE DISTANCE   1----->  3  :  10
ENTER THE DISTANCE   1----->  4  :  9
ENTER THE DISTANCE   1----->  5  :  6
ENTER THE DISTANCE   2----->  1  :  8
ENTER THE DISTANCE   2----->  2  :  -1
ENTER ONLY POSITIVE EDGES 
ENTER THE DISTANCE   2----->  2  :  99999
ENTER THE DISTANCE   2----->  3  :  7
ENTER THE DISTANCE   2----->  4  :  3
ENTER THE DISTANCE   2----->  5  :  4
ENTER THE DISTANCE   3----->  1  :  8
ENTER THE DISTANCE   3----->  2  :  4
ENTER THE DISTANCE   3----->  3  :  99999
ENTER THE DISTANCE   3----->  4  :  4
ENTER THE DISTANCE   3----->  5  :  8
ENTER THE DISTANCE   4----->  1  :  11
ENTER THE DISTANCE   4----->  2  :  10
ENTER THE DISTANCE   4----->  3  :  5
ENTER THE DISTANCE   4----->  4  :  99999
ENTER THE DISTANCE   4----->  5  :  5
ENTER THE DISTANCE   5----->  1  :  6
ENTER THE DISTANCE   5----->  2  :  9
ENTER THE DISTANCE   5----->  3  :  5
ENTER THE DISTANCE   5----->  4  :  5
ENTER THE DISTANCE   5----->  5  :  99999
24	29	28	28	27	
SELECTED IS  :5
24	34	31	31	27	
SELECTED IS  :3
24	36	31	40	27	
SELECTED IS  :2
24	36	31	41	27	
SELECTED IS  :4
1	5	3	2	4	1	
THE PATH COST IS :  29
Time taken (seconds)  : 0.035
rohan@rohan-HP-ProBook-4410s:~/Dropbox/7_SEMESTER$


**********************/

