//-------------------------Program-------------------------------
//AIM: Write a C program to tokenize given input C program and identify category of token.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void header(char tok[30]); // for header detection
void function(char tok[30]); //for function call
int keyword(char tok[30]); //reserved keywords
int variable(char tok[30]); //variable declared

struct keyword{
char name[15];
}kw[32];

int max_key;

void main()
{
	char fname[10],buff[100],tok1[30],tok2[30],tok3[30],tok4[30];
	int n,x,l=0,i=0;
	int ch=0;
  	FILE *fp,*fk;
	fk = fopen("keyword.txt","r");
	while(fgets(buff,80,fk))
	{
		strcpy(kw[i].name,buff);
		i++;
	}
	max_key = i;
	printf("\nEnter The file name : ");
	scanf("%s",fname);
	fp = fopen("input.c","r");
	if(fp==NULL)
		printf("\nUnable to open file");
	else
	{
		while(fgets(buff,80,fp))
		{
			n=sscanf(buff,"%s %s %s %s",tok1,tok2,tok3,tok4);
			l++;
			printf("\nline:%d :\t",l);
			switch(n)
			{
				case -1 : printf("Blank line");break;
				case 1 :if(tok1[0]=='#')
					{
						header(tok1);
					}
					else if(tok1[0]=='{')
					     {
						printf("%s : Opening Brace",tok1);
					     }
					     else if(tok1[0]=='}')
						  {
							printf("%s : Closing Brace",tok1);
						  }
						  else if((x = keyword(tok1))!=-1)
						       {
								;
						       }
						       else if(strstr(tok1,"=")!=NULL||strstr(tok1,"+")!=NULL||strstr(tok1,"-")!=NULL||strstr(tok1,"*")!=NULL||strstr(tok1,"/")!=NULL)
						       {
								printf("%s : Arithmatic Calculation/Assignment Operation",tok1);
						       }
						       else function(tok1);
								break;
				case 2 :x=keyword(tok1);
					if(x>=2&&x<9)
					{
						if(strstr(tok2,"(")!=NULL && strstr(tok2,")")!=NULL)
						printf(" %s : %s's statement",tok2,tok1);
						else
						printf(" Error in %s's statement",tok1);
					}
					else if((x=variable(tok2))==1)
					{
						;}
					else
					function(tok2);
					break;
			}//switch ends
	}//while ends
}//else ends
	printf("\n\n\n");
		}
void header(char tok[30])
{
	int i=0,j;
	char buff[20];
	for(i=0;tok[i]!='<';i++)
		buff[i] = tok[i];
		buff[i++] = '\0';
	printf("%s : Preprocessor Directive",buff);
	for(j=0;tok[i]!='>';j++)
	{
	buff[j] = tok[i];
	i++;
	}
	buff[j++] = '\0';
	printf(" %s : Header File",buff);
}
void function(char tok[30])
{
	int i=0,j;
	char buff[20];
	for(i=0;tok[i]!='(';i++)
	buff[i] = tok[i];
	if(i>0)
	{
	buff[i++] = '\0';
	printf("%s(); : Function name",buff);
	for(j=0;tok[i]!=')';j++)
	{
	buff[j] = tok[i];
	i++;
	}
	buff[j++] = '\0';
	if(j>1)
	printf(" %s : parameter list",buff);
	}
}
int keyword(char tok[30])
{
	int i=0,y;
	for(i=0;i<max_key;i++)
	{
	if(strstr(kw[i].name,tok)!=NULL)
	{
	if(strstr(tok,";")!=NULL||strstr(tok,";")!=NULL)
	printf("Error in keyword structure");
	else
	{
	printf("%s : Keyword ",tok);
	return i;
	}
	}
	}
	return -1;
}
int variable(char tok[30])
{
	char temp[10];
	int i=0,flag=0;
	if(strstr(tok,"()")==NULL)
	{
	while(tok[i]!=';')
	{
	temp[i]=tok[i];
	i++;
	}
	temp[i]='\0';
	if(tok[i]==';')
	{
	flag=1;
		printf(" %s : variable ",temp);
	}
	}
	if(flag==1)
	return 1;
	else
	return 0;
}

