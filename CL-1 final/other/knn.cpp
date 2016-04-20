#include<iostream>
#include<fstream>
#include<string.h>
#include<math.h>
using namespace std;
struct element{
float a,b,c,d ;
char label[100];
float euc;
};
float euclid(element x,element y)
{
return(sqrt(pow((x.a-y.a),2)+pow((x.b-y.b),2)+pow((x.c-y.c),2)+pow((x.d-y.d),2)));
}
int main()
{
ifstream file;
int i=0,j=0,k,setosa=0,versi=0,vergi=0;
float a,b,c,d;
element ele[150],dude,temp;
char e;
char f[100];
cout<<"Enter 4 coordinate values";
cin>>dude.a>>dude.b>>dude.c>>dude.d;
file.open("iris_data.txt");
while((file >> a >> e >> b >> e >> c >> e >> d >> e >> f) && (e ==','))
{
ele[i].a=a;
ele[i].b=b;
ele[i].c=c;
ele[i].d=d;
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
if(ele[j].euc>ele[j+1].euc)
{
temp=ele[j];
ele[j]=ele[j+1];
ele[j+1]=temp;
}
}
}
cout<<"Enter K";
cin>>k;
for(i=0;i<k;i++)
{
if(strcmp(ele[i].label,"Iris-setosa")==0)
setosa++;
else if(strcmp(ele[i].label,"Iris-versicolor")==0)
versi++;
else if(strcmp(ele[i].label,"Iris-virginica")==0)
vergi++;
}
cout<<setosa<<"\t"<<versi<<"\t"<<vergi<<endl;
if(setosa>versi && setosa>vergi)
cout<<"Iris-setosa"<<endl;
else if(versi>setosa && versi>vergi)
cout<<"Iris-versicolor"<<endl;
else
cout<<"Iris-verginica"<<endl;
}

