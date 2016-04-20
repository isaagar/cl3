#include<iostream>
using namespace std;

class binarysearch {

private:

	int i,j,first,last,middle,temp,key,*array,size;

public:

	binarysearch()
	{
	cout<<"===============WELCOME TO BINARY SEARCH ========================="<<endl;
	int i=j=first=last=middle=key=temp=size=0;
	array = new int[size];
	}

void input()
{
	cout<<"Enter the size of the array:"<<endl;
	cin>>size;
	array = new int[size];
	cout<<"Enter the numbers for the array:"<<endl;
	for(i=0;i<size;i++)
	{
	cin>>array[i];
	}
	cout<<endl<<"The numbers you have entered are:"<<endl;
	display();
}
void display()
{

for(i=0;i<size;i++)
{
cout<<array[i]<<",";
}
cout<<endl;
}

void sorting()
{
cout<<"Now perform Sorting....."<<endl;
for(i=0;i<size-1;i++)
{
	for(j=0;j<size-1-i;j++)
	{
		if(array[j]>array[j+1])
		{
		temp= array[j];
		array[j]=array[j+1];
		array[j+1]=temp;
		}
	}
}
cout<<"Sorted numbers!!"<<endl;
display();

}

void searching()
{
cout<<"Enter the key you want to search:"<<endl;
cin>>key;
first=0;
last=size-1;
middle= (first+last)/2;
	while(first<=last)
	{
	if(array[middle]<key)
		first=middle+1;
	else if(array[middle]==key)
		{
		cout<<key<<" found at location"<<" "<<middle<<"\n";
		break;
		}
	else
		last=middle-1;
	middle=(first+last)/2;
	}
if(first>last)
	cout<<key<<"not present"<<"\n";

}


};

int main()
{
binarysearch obj;
obj.input();
obj.sorting();
obj.searching();
return 0;
}
