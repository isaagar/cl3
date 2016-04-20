%{
#include<stdio.h>
%}
digit [0-9]+
header [t]*"#include<"[a-z]+".h>"
keyword "if".*|"else".*|"do".*|"while".*|"for".*|"return".*
inbuilt [t]*"printf(".*");"|[t]*"scanf(".*");"
user [a-z]+"("[a-z].*")"
datatype "void"|"int"|"float"|"char"|"double"
comment [t]*"//".*
operator "+"|"*"|"/"|"-"|"="
openbracket "{"|"("|"["
closebracket "}"|")"|"]"
variable [a-zA-Z]*[_]*[a-zA-Z0-9]*
seprator ","
terminator ";"
%%
{digit} {printf("\n Digit --> %s",yytext);}
{header} {printf("\n Header file --> %s",yytext);}
{inbuilt} {printf("\n Inbuilt Function --> %s",yytext);}
{user} {printf("\n User Function --> %s",yytext);}
{datatype} {printf("\n Datatype --> %s",yytext);}
{comment} {printf("\n Comment --> %s",yytext);}
{operator} {printf("\n Oprator --> %s",yytext);}
{openbracket} {printf("\n Opening bracket --> %s",yytext);}
{closebracket} {printf("\n Closing bracket --> %s",yytext);}
{variable} {printf("\n Variable --> %s",yytext);}
{seprator} {printf("\n Separator --> %s",yytext);}
{terminator} {printf("\n Terminator --> %s",yytext);}
{keyword} {printf("\n Keyword --> %s ",yytext);}
%%
int main()
{
yyin=fopen("input.c","r");
yylex();
return(0);
}

