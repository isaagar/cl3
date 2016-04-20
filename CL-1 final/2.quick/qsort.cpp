#include<iostream>
#include<omp.h>
#include<stdlib.h>
#include<string.h>

using namespace std ;

class Quicksort
{
public :
	int i,i1;
	int a[100];
	void take_input(int n)
	{
	 	
		cout<<"Enter the Elements: ";
    		for(i=0; i<n; i++)
    		{
    			cin>>a[i];
    		}    
	}
	
	void display(int n)
	{
		for(int i1=0;i1<n;i1++)
		{
			cout<<"\t"<<a[i1];
		}
	}

	
	void quicksort(int left,int right)
	{
		int index;
		if(left<right)
		{
			index = partition(left,right);
			#pragma omp parallel sections 
			{
			#pragma omp section
				quicksort(left,index-1);
			#pragma omp section 
				quicksort(index+1,right);
			}	
		}
	}

	int partition(int low,int high)
	{
		int pivot ,temp,i,j;
		pivot = a[low];
		i=low;
		j=high+1;
		while(1)
		{
			do ++i;
			while(pivot>=a[i] && i<=high);
		
			do --j;
			while(pivot<a[j]);

			if(i>=j)
			break;
		
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
		temp = a[low];
		a[low] = a[j];
		a[j] = temp;
		return j;
	}
};

int main()
{
	int n,a[100];
	cout<<"Enter the number of elements:";
	cin>>n;
	Quicksort q;
	q.take_input(n);
	cout<<"Input Array:\n";
	q.display(n);
	q.quicksort(0,n-1);
	cout<<endl<<endl;
	cout<<"Sorted array :\n";
	q.display(n);
	cout<<endl;
	return 0;
}

