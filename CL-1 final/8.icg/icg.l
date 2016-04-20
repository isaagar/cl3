%{
 #include<stdio.h>
 #include<ctype.h>	
 #include<stdlib.h>
 #include<string.h>
 #include "y.tab.h" 
%}

%%
"if"		{strcpy(yylval.cval,yytext);return IF;}
[0-9]+		{yylval.dval=atoi(yytext);return DIGIT;}
[a-z]+		{strcpy(yylval.cval,yytext);return ID;}
"("|")"		{return *yytext;}
[{]		{strcpy(yylval.cval,yytext);return STCB;}
[}]		{strcpy(yylval.cval,yytext);return ENCB;}
"<"|">"		{strcpy(yylval.cval,yytext);return RELOP;}	
[=]		{strcpy(yylval.cval,yytext);return EQUAL;}
[+-]		{strcpy(yylval.cval,yytext);return PLUS;}
[;]		{strcpy(yylval.cval,yytext);return SEMI;}
%%

