%{
#include<stdio.h>
%}

%%

go |
runs   {printf("%s is a verb",yytext);}

dog | 
cats | 
fish | 
glove | 
foxglove | 
mouse  {printf("%s is a noun",yytext);}
quick | 
slow | 
lazy | 
clever | 
smart | 
stupid | 
blue | 
white  {printf("%s is an adjective",yytext);}
quickly | 
easily | 
openly | 
slowly  {printf("%s is an adverb",yytext);}
"." |
, | 
"?" | 
; | 
: | 
! | 
@ | 
#  {printf("%s is puncutation",yytext);}
over | 
under |
around |
through | 
between  {printf("%s is a preposition",yytext);} 
 
  

%%


int main()
{
 FILE *fd; 
 
 fd=fopen("ab.txt","r");
 yyin=fd;
 yylex();
 }
 
 yywrap()
 {
 }


