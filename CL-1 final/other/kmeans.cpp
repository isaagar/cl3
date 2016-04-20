#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;
int main()
{
	int i1=0,i2,i3,t1,t2;
	float k0[150];
	float k1[150];
	float k2[150];
	ifstream infile;
	double array[150];
	char cNum[150] ;
	infile.open ("iris_data.txt", ifstream::in);
	// cout<<"\nEnter 10 numbers:\n";
	if (infile.is_open())
	{
	while (infile.good())
	{
	infile.getline(cNum, 256, ',');
	k0[i1]= atof(cNum) ;
	i1++ ;
	}
	infile.close();
	}
	else
	{
	cout << "Error opening file";
	}
	//cin>>k0[i1];
	cout<<"dataset::\n";
	for(int i=0;i<150;i++)
	cout<<k0[i]<<"\t";
	cout<<"\n\n";
	//initial means
	float m1=3.2;
	float m2=5.1;
	float om1,om2;
	//old means
	do
	{
	//saving old means
	om1=m1;
	om2=m2;
	//creating clusters
	i1=i2=i3=0;
	for(i1=0;i1<150;i1++)
	{
		//calculating distance to means
		t1=k0[i1]-m1;
		if(t1<0){t1=-t1;}
		t2=k0[i1]-m2;
		if(t2<0){t2=-t2;}
		if(t1<t2)
		{
		//near to first mean
		k1[i2]=k0[i1];
		i2++;
		}
		else
		{
		//near to second mean
		k2[i3]=k0[i1];
		i3++;
		}
	}
	t2=0;
	//calculating new mean
	for(t1=0;t1<i2;t1++)
	{
		t2=t2+k1[t1];
	}
	m1=t2/i2;
	t2=0;
	for(t1=0;t1<i3;t1++)
	{
		t2=t2+k2[t1];
	}
	m2=t2/i3;
	//printing clusters
	cout<<"\nCluster 1:";
	for(t1=0;t1<i2;t1++)
	{
		cout<<k1[t1]<<" ";
	}
	cout<<"\nm1="<<m1;
	cout<<"\nCluster 2:";
	for(t1=0;t1<i3;t1++)
	{
		cout<<k2[t1]<<" ";
	}
	cout<<"\nm2="<<m2;
	cout<<"\n ----";
	}while(m1!=om1&&m2!=om2);
	cout<<"\n Clusters created";
	//ending
	return 0;
}

