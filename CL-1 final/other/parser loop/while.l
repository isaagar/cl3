alpha [A-za-z]
digit [0-9]

%%
while                         return WHILE;
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
return 1; 
}
