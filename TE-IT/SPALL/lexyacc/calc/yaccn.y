%{
	#include<stdio.h>
	#include<stdlib.h>
	
%}

%token num
%left plus minus
%left mul divi

%%
S: E{ printf("\n\n\t Result = %d\n\n",$1);}
E: E plus E { $$= $1+$3;}
E: E minus E { $$=$1-$3;}
E: E mul E { $$=$1*$3;}
E: E divi E 
	{	if($3==0)
	 	{
			printf("\n\n\t Error !! Division by zero !!\n");
			exit(0);
		}
		else
		{
			$$ = $1/$3;
		}
	}
E: num	{ $$=$1;}  


;
%%

int main(void)
{
	yyparse();
	return 0;
}

int yyerror()
{
	return;
}
