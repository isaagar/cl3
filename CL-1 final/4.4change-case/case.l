%{
#include<stdio.h>
%}
lower [a-z]
upper  [A-Z]
space   [ \t\n]
%%
{lower}         {printf("%c",yytext[0]- 32);}
{upper}        {printf("%c",yytext[0]+ 32);}
{space}         ECHO;
.              ECHO;
%%

main()
{
    FILE *fp=fopen("input.txt","r");
    yyin=fp;
    yylex();
   
}


//OUTPUT
/* tanaya@tanaya:~$ cd Desktop
tanaya@tanaya:~/Desktop$ lex case.l
tanaya@tanaya:~/Desktop$ cc lex.yy.c -ll
tanaya@tanaya:~/Desktop$ ./a.out
MITCOE
mitcoe
tHIs iS To cHeCK cAse CHanGe
*/


