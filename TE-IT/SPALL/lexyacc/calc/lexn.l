%{
	#include<stdlib.h>
	#include<stdio.h>
	#include"y.tab.h"
%}

%%
[0-9]+  { yylval=atoi(yytext);
	  return(num);
	}
"+" 	{ return(plus); }
"-" 	{ return(minus); }
"*"	{ return(mul); }
"/"	{ return(divi); }
";"	{ return 1; }
%%

int yywrap()
{
	return 1;
}
