%{
#include<stdio.h>
%}

%%
printf |
scanf |
strcmp |
strcpy |
getc {printf("%s() is a built in funtion",yytext);}
[0-9]+ {printf("%s is digit",yytext);} 
[a-z]+ {printf("%s is an identifier",yytext);}

%%


int main()
{
 FILE *fd; 
 
 fd=fopen("b.c","r");
 yyin=fd;
 yylex();
 }
 
 yywrap()
 {
}


