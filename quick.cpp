#include<iostream>
#include<omp.h>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include "rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;

class Quicksort
{
public:
int input[10];
char inpu[50],outpu[50];
string inp;
int i;

void take_input()
{

string line,content="";
cout<<"Enter input file path: ";
cin>>inpu;
ifstream in(inpu);
while(getline(in,line))
inp+=line;
vector<char>xml_copy(inp.begin(),inp.end());
xml_copy.push_back('\0');
xml_document<>doc;
doc.parse<parse_declaration_node|parse_no_data_nodes>(&xml_copy[0]);
xml_node<>*cur_node = doc.first_node("array");
cur_node = cur_node->first_node("number");
for(i=0;i<10;i++)
{
content=cur_node->value();
input[i]=atoi(content.c_str());
cur_node=cur_node->next_sibling("number");
}
}

void display()
{
cout<<"Array is: ";
for(i=0;i<10;i++)
cout<<input[i]<<endl;
}

void store()
{
cout<<"output path: ";
cin>>outpu;
ofstream ofs(outpu, ofstream::out);
for(i=0;i<10;i++)
ofs<<input[i]<<endl;
ofs.close();
}

void quick(int left,int right)
{
int index;

if(left<right)
{
index = partition(left,right);
#pragma omp parallel sections
{
#pragma omp section
quick(left,index-1);
#pragma omp section
quick(index+1,right);

}
}
}

int partition(int low,int high)
{
int temp,pivot,i,j;
pivot=input[low];
i=low,j=high+1;

while(1)
{
do ++i;
while(pivot>=input[i] && i<=high);
do --j;
while(pivot<input[j]);

if(i>j)
break;
temp=input[i];
input[i]=input[j];
input[j]=temp;
}
temp=input[low];
input[low]=input[j];
input[j]=temp;
return j;
}
};

int main()
{
Quicksort q;
q.take_input();
q.display();
q.quick(0,9);
q.display();
q.store();
}
