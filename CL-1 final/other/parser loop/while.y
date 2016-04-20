%{
#include<stdio.h>
#include<stdlib.h>

%}

%token ID WHILE GE LE LR GR INC DEC DIGIT
%right '='
%left GR LR GE LE 
%left '+' '-'
%left '*' '/'

%%

S : ST {printf("INPUT ACCEPTED  \n");};

ST : WHILE '(' COND ')' DEF
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
     
COND : ID  RELOP ID
     | DIGIT
     | DIGIT RELOP DIGIT
     | ID RELOP DIGIT
     ;
     
RELOP : GE 
      | LE
      | GR
      | LR
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
yyin=fopen("while.txt","r");
yyparse();

return 0;
}


