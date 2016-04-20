%{
#include<stdio.h>
#include<stdlib.h>
int addition=0,count=0,temp=0;
%}

%%

[0-9]+ { 
	temp = atoi(yytext);
	addition = addition + temp;
	count++;
      }
     
 
%%

int main()
{
	FILE *fp=fopen("num.txt","r");
	yyin = fp;
	yylex();
	addition=addition/count;
	printf("Average is %d \n",addition);

}
yywrap()
{
}
