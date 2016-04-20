%{
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include "lex.yy.c"
struct icode
{
  char op1[20],op2[20],opr[20],result[20];
  //int indx;
};
int icnt=1;
struct icode ic[10];
int var;
char tmp[20];
void add_into_table(char op1[20],char op2[20],char opr[20],char result[20]); 
void disp();
void yyerror(char *s);
int yywrap();
%}
%union { char cval[10];
	  int dval;	
	}
%token<cval> ID IF STCB ENCB RELOP SEMI EQUAL PLUS
%token<dval> DIGIT
%type<cval> S D E B A S1 
%left PLUS
%%

S:EXP	{disp();}
    ;
EXP:D'('E')'B
   ;
D:IF	
 ; 
E:ID RELOP ID	{
	          add_into_table($1,$3,$2,"t");
                  var=icnt+2;   //icnt=2
		  sprintf(tmp,"%d",var);
		  add_into_table("t","--","IF",tmp);
		}
  ;
B:STCB S1 ENCB		{
				  sprintf(tmp,"%d",icnt);		
				  strcpy(ic[3].result,tmp);
				}
  ;         
S1:ID EQUAL A SEMI		{add_into_table("--","--","goto",tmp);
				 add_into_table(tmp,"--","=",$1);}//icnt=5
  ;
A:ID	{sprintf(tmp,"%s",$1);}
 |DIGIT	{sprintf(tmp,"%d",$1);}
 |A PLUS A	{var=icnt+3;
		 sprintf(tmp,"%d",var);
		  //icnt=4
		 add_into_table($1,$3,$2,"tx");		
		} 
 ;
%%

void add_into_table(char op1[20],char op2[20],char opr[20],char result[20])
 { 
   strcpy(ic[icnt].op2,op2);
   strcpy(ic[icnt].op1,op1);	
   strcpy(ic[icnt].opr,opr);
    strcpy(ic[icnt].result,result);
      icnt++; 
   printf("Entry Added");
 }

void disp()
 {
    int i,temp1,temp_indx;
  printf("\nQUADRUPLE  FORM");
  printf("\n---------------");
  printf("\nS.NO\tOperator\tOperand1\tOperand2\tResult\n\n");
   for(i=1;i<=icnt;i++)
    {
      printf("%d\t",i);	
      printf("%s\t\t",ic[i].opr);
      printf("%s\t\t",ic[i].op1);
      printf("%s\t\t",ic[i].op2);
      printf("%s\t\t",ic[i].result);
      printf("\n"); 
    }	 
 }
int main()
{
yyparse();
return 0;
}

void yyerror(char *s)
{
printf("\n%s",s);
}

int yywrap()
{
 return 1;
}

