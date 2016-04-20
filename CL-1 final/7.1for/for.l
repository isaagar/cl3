%{
#include"y.tab.h"
%}
alpha [A-Za-z]
digit [0-9]

%%
for                           return FOR;
[0-9]+                        return DIGIT ;
{alpha}({alpha}|{digit})*     return ID;
">="                          return GE;
"<="                          return LE;
"<"                           return LR;
">"                           return GR;
"++"                          return INC;
"--"                          return DEC;
.                             return yytext[0];

%%
int yywrap()
{ 
return 0; 
}
