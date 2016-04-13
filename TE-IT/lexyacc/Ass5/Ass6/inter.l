%{
	#include<stdio.h>
	#include<stdlib.h>
	#include "calc.tab.h" //	Gives Tokens Letters & Digit to YACC
	 
%}
ALPHA [A-Za-z]

DIGIT [0-9]

%%

{ALPHA}({ALPHA}|{DIGIT})* return ID;

{DIGIT}+ {yylval=atoi(yytext); return NUM;}

[\n\t] yyterminate();

. return yytext[0];

%%
