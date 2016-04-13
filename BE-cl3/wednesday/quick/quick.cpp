#include<iostream>
#include<omp.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include"rapidxml_utils.hpp"
#include <vector>

using namespace std ;
using namespace rapidxml ;

class Quicksort
{
public :
string input_xml;
string line;
char inputstring [50], outputstring[50];
int input[20],output[20],i1;

void display()
{
	for(int i1=0;i1<20;i1++)
	{
		cout<<"\n"<<input[i1];
	}
}

void take_input()
{ 	
    cout<<"Enter the input file pathname: ";
	cin>> inputstring;
	ifstream in(inputstring);    
    // read file into input_xml	
    while(getline(in,line))
        input_xml += line;
    int i=0;
// make a safe-to-modify copy of input_xml
    vector<char> xml_copy(input_xml.begin(), input_xml.end());
    xml_copy.push_back('\0'); // '\0' appened at the end of vector
// only use xml_copy from here on!
    xml_document<> doc;   // character type defaults to char
 /* we are choosing to parse the XML declaration
     parse_no_data_nodes prevents RapidXML from using the somewhat surprising
     behavior of having both values and data nodes, and having data nodes take
     precedence over values when printing*/
    doc.parse<parse_declaration_node | parse_no_data_nodes>(&xml_copy[0]); 
    xml_node<>* cur_node = doc.first_node("array"); // taking the first node as a root node (array).
    cur_node = cur_node->first_node("number"); //
    string content = "";
    
    for(i=0; i<20; i++)
    {
    content = cur_node->value(); // storing the number in content
    input[i]=atoi(content.c_str()); // converting char to int ; content to input[i]
    cur_node = cur_node->next_sibling("number"); // going to next node
    }    
}

void store()
{
	cout<<"\nEnter output file pathname: ";
	cin>>outputstring;
	ofstream ofs (outputstring , ofstream::out);		
	for (int i=0;i<20;i++)
	{
	ofs<<input[i]<<endl;
	}
	ofs.close();
	cout<<"\n Sortred array stored in: "<<outputstring<<endl;
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
	pivot = input[low];
	i=low;
	j=high+1;
	while(1)
	{
		do ++i;
		while(pivot>=input[i] && i<=high);
	
		do --j;
		while(pivot<input[j]);

		if(i>=j)
		break;
	
		temp = input[i];
		input[i] = input[j];
		input[j] = temp;
	}
	temp = input[low];
	input[low] = input[j];
	input[j] = temp;
return j;
}
};

int main()
{
	Quicksort q;
	q.take_input();
	cout<<"Input array from xml file :\n";
	q.display();
	cout<<endl<<endl;
	q.quicksort(0,20-1);
	cout<<endl<<endl;
	cout<<"Sorted array :\n";
	q.display();
	q.store();
	cout<<endl<<endl;
	return 0;
}
