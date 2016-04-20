%{
#include<stdio.h>
#include<stdlib.h>

%}

%token ID FOR GE LE LR GR INC DEC DIGIT
%right '='
%left GR LR GE LE 
%left '+' '-'
%left '*' '/'

%%

S : ST {printf("INPUT ACCEPTED  \n");};

ST : FOR '(' ASSG ';' TEST ';' ID U  ';' ')' DEF
   ;

ASSG : ID '=' DIGIT 
     | ID '=' ID
     ;

TEST : ID GR DIGIT 
      |ID LR DIGIT
      |ID GE DIGIT
      |ID LE DIGIT
     ;

U :  INC 
    |DEC
    ;
 
DEF : '{' BODY '}'
    |  E';'
    |  ST 
    |  
    ;
    
BODY : BODY BODY 
     | E';'
     | ST
     |
     ;
 
E : ID '=' E 
  | E '+' E 
  | E '-' E
  | E '*' E  
  | E '/' E
  | ID 
  | DIGIT 
  ;  

%%
#include "lex.yy.c"

int main ()
{
yyin=fopen("for.txt","r");
yyparse();

return 0;
}


