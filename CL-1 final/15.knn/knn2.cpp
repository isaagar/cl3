#include<iostream>
#include<fstream>
#include<math.h>
#include<string.h>
using namespace std;

struct element
{
float a,b;
float euc;
char label[150];
};

float euclid(element x,element y)
{
	return (sqrt(pow((x.a-y.a),2)+pow((x.b-y.b),2)));
}

int main()
{
	ifstream in;
	int i=0,j=0,k=0,good=0,bad=0;
	element ele[150],dude,temp;
	float a,b;
	char f[100];
	char e;
	cout<<"Enter the four co-ordinates:";
	cin>>dude.a>>dude.b;
	
	in.open("data.txt");
	
	while(in>>a>>e>>b>>e>>f &&(e==','))
	{
		ele[i].a=a;
		ele[i].b=b;
		strcpy(ele[i].label,f);
		i++;
	}
	
	for(i=0;i<150;i++)
	{
		ele[i].euc=euclid(dude,ele[i]);
	}
	for(i=0;i<150;i++)
	{
		for(j=0;j<150;j++)
		{
 			if(ele[j].euc > ele[j+1].euc)
			{
			temp =ele[j];
			ele[j]= ele[j+1];
			ele[j+1]= temp;
			}
		}
	}
	
	cout<<"Enter k:";
	cin>>k;
	
	for(i=0;i<k;i++)
	{
	if(strcmp(ele[i].label,"bad")==0)
		bad++;
	if(strcmp(ele[i].label,"good")==0)
		good++;
	}
	cout<<good<<"\t"<<bad<<"\t";
	if(good>bad)
	cout<<"Good\n";
	if(bad>good)
	cout<<"Bad\n";
	else if(good==bad)
	cout<<"Its different";
	

}
