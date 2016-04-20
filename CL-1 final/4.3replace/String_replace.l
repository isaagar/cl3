%{
#include<stdio.h>
#include<string.h>

FILE *ff,*fr;
char p[20],q[20],r[20],fname[20];
%}

word [a-zA-Z]+
eol n
%%
{word} {
                if(strcmp(p,yytext)==0)
                        fprintf(fr,"%s",q);
                else
                        fprintf(fr,"%s",yytext);

        }

{
{eol} {fprintf(fr,"%s",yytext);}
. {fprintf(fr,"%s",yytext);}
%%

int main(int argc,char *argv[])
{
        strcpy(fname,argv[1]);
        strcpy(p,argv[2]);
        strcpy(q,argv[3]);
        ff=fopen(fname,"r+");
        fr=fopen("out.txt","w");   
        yyin=ff;
        yylex();
        return(0);
}

yywrap()
{
}


