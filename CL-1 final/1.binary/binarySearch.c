#include <stdio.h>
#define SIZE 10

/*
Program to implement:  Binary Search
*/

void scanArray(int a[], int s)//formal parameter a is a reference to actual parameter arr; formal parameter s is a copy of actual parameter 5
{
    int i;
    printf("\n Enter %d numbers ", s);
    for(i =0; i< s; i++)
    {
        scanf("%d", &a[i]);
    }
}

void displayArray(int a[], int s)
{
    int i;
    printf("\n");
    for(i =0 ; i< s; i++)
    {
        printf(" %d ", a[i]);
    }
}

//sort
void bubble(int a[], int s)
{
    int i, j;//indices and loop control
    int temp; //swap
    
    for(i=s-1; i>0; i--)
    {
        for(j=0; j<i; j++)
        {
            if(a[j] > a[j+1])
            {//swap
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }//if
        }//for(j ...    
    }//for(i ...
}

int binarySearch(int a[], int x, int y,  int val)
{
    if(x <= y)
    {
        int mid = (x+y)/2;
        
        //compare
        if(val == a[mid])
        {//match found
            return mid;//position (index)
        }
        else if(val < a[mid])
        {//look at LHS
            return binarySearch(a, x, mid-1, val);
        }
        else if(val > a[mid])
        {//look at RHS
            return binarySearch(a, mid+1, y, val);
        }
    }//if
    
    return -1; //not found
}//binarySearch

int main()
{
    int arr[SIZE];
    int val, pos;
    
    scanArray(arr,SIZE);
    displayArray(arr,SIZE);

    //sort the array for binary search
    bubble(arr, SIZE);
    displayArray(arr,SIZE);
    
    printf("\n Enter the value to search ");
    scanf("%d", &val);
    
    pos = binarySearch(arr, 0, SIZE -1, val);
    if(pos != -1)
        printf("\n %d found at index %d ", val , pos);
    else
        printf("\n %d not found ", val);
    return 0;
}

