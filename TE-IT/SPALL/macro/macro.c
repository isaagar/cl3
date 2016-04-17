					ASSIGNMENT NO. 03

#include<stdio.h>
#include<string.h>

int arg1,arg2;

typedef struct MNT
{
	char mname[20];
	int sindex;
	int eindex;
	int no_of_arguments;

}MNT;

typedef struct MDT
{
	char label[20];
	char instruct[20];
	int arguments[5];
	int no;

}MDT;

typedef struct FPPL
{
	char name[20];
	int pos;

}FPPL;

typedef struct Pass1table
{
	char label[20];
	char instruct[20];
	char arguments[5][20];
	int no;

}Pass1table;

typedef struct Pass2table
{
	char label[20];
	char instruct[20];
	char arguments[5][20];
	int no;
	
}Pass2table;

typedef struct APPL
{
	char name[20];
	int pos;

}APPL;
	
void display_Pass2(Pass2table table2[50], int tp2);
void display_APPL(APPL appl[10], int aptr);		

int main()
{

	int Pass1(MNT mnt[50], MDT mdt[50], int mntc, int mdtc, Pass1table table1[50]);
	int Pass2(MNT mnt[50], MDT mdt[50], int mntc, Pass1table table1[50], int tp, Pass2table table2[50]);
	int putinbuffer(FILE *fin, char buffer[20]);
	int displayPass1tables(MNT mnt[50], int mntc, MDT mdt[50], int mdtc, FPPL fppl[5], int fptr);
	int print_IC(Pass1table table1[50], int tp);
	
	int o=0;

	MNT mnt[50];
	MDT mdt[50];
	Pass1table table1[50];
	
	int mdtc=0, tp=0, tp2=0, mntc=0;

	printf("\nPrinting the IC File");
	tp=Pass1(mnt,mdt,mntc,mdtc,table1);
	

	return 0;
}

int Pass1(MNT mnt[50], MDT mdt[50], int mntc, int mdtc, Pass1table table1[50])
{
	int tp=0,i=0, succ=0, fptr=0, temp=0, j=0, flagl=0;
	FPPL fppl[10];
	
	Pass2table table2[50];
	
	FILE *fin=NULL;
	char ch='\0', buffer[20]={"\0"};

	fin=fopen("input1.c","r");
	mntc=0;
	mdtc=0;
	tp=0;
	fptr=0;
	succ=1;
	do
	{
		ch='\0';
		i=0;
		while(ch!=' ' && ch!='\n' && ch!=',' && ch!=':' && succ==1)
		{
			succ=fscanf(fin,"%c",&ch);
			buffer[i]=ch;
			i++;
		
		}
		buffer[i-1]='\0';

		if(strcmp(buffer,"MACRO")==0)	//handling of macro definition
		{
			succ=putinbuffer(fin,buffer);

			strcpy(mnt[mntc].mname,buffer);		//macro name

			mnt[mntc].sindex=mdtc;
			mnt[mntc].no_of_arguments=0;

			ch='\0';
			while(ch!='\n')			// macro parameters into fppl
			{
				ch='\0';
				i=0;
				while(ch!='\n' && ch!=',' && succ==1)
				{
					succ=fscanf(fin,"%c",&ch);
					buffer[i]=ch;
					i++;
		
				}
				buffer[i-1]='\0';
				printf("\nBuffer:%s",buffer);
				mnt[mntc].no_of_arguments++;
	
				strcpy(fppl[fptr].name,buffer);
				fppl[fptr].pos=mnt[mntc].no_of_arguments;
				fptr++;
			}
			
			j=0;
			flagl=0;
			while(strcmp(buffer,"MEND")!=0)		//putting macro def into mdt
			{
				ch='\0';
				i=0;
				while(ch!=' ' && ch!=',' && ch!=':' && ch!='\n')
				{
					fscanf(fin,"%c",&ch);
					buffer[i]=ch;
					i++;
				}
				buffer[i-1]='\0';
		
				if(ch==':')
				{
					strcpy(mdt[mdtc].label,buffer);
					flagl=1;			//label encountered flag
				}
				
				else if(ch==' ')
				{
					strcpy(mdt[mdtc].instruct,buffer);
					mdt[mdtc].no=0;
					if(flagl==0)		//label was not encountered
					{						
						strcpy(mdt[mdtc].label,"\0");
					}
				}
				else if(ch==','||ch=='\n')	//arguments to be checked for position in fppl
				{
					i=0;
					for(i=0;i<fptr;i++)
					{
						if(strcmp(buffer,fppl[i].name)==0)
						{
							break;
						}
					}
					mdt[mdtc].arguments[j]=fppl[i].pos;
					j++;
				}

				if(ch=='\n')
				{
					mdt[mdtc].no=j;
					j=0;
					flagl=0;
					mdtc++;
				}
					
			}
			
			mnt[mntc].eindex=mdtc-1;
			strcpy(mdt[mdtc].instruct,buffer);
			mdt[mdtc].arguments[0]=mntc;
			succ=putinbuffer(fin,buffer);
			
			mntc++;
			mdtc++;			
			
		}
		else	//for the rest of the program
		{

			if(ch==':')
			{
				strcpy(table1[tp].label,buffer);
				flagl=1;
			}
			else if(ch==' ')
			{
				strcpy(table1[tp].instruct,buffer);
				j=0;
				table1[tp].no=0;
				if(flagl==0)
				{
					strcpy(table1[tp].label,"\0");
				}

			}
			else if(ch==',' || ch=='\n')
			{
				strcpy(table1[tp].arguments[j],buffer);
				j++;
				if(ch=='\n')
				{
					table1[tp].no=j;
					j=0;
					flagl=0;
					tp++;
				}
			}
		}

	}while(succ==1);

	displayPass1tables(mnt,mntc,mdt, mdtc,fppl,fptr);
	print_IC(table1,tp);

	fclose(fin);
	fin=NULL;
	
	Pass2(mnt,mdt,mntc,table1,tp,table2);
	
	return tp;
}

int putinbuffer(FILE *fin, char buffer[20])
{
	int i=0, succ=0;
	FILE *j=NULL;
	char ch='\0';

	j=fin;
	succ=1;
	while(ch!=' ' && ch!='\n' && ch!=',' && succ==1)
	{
		succ=fscanf(j,"%c",&ch);
		buffer[i]=ch;
		i++;
		
	}
	buffer[i-1]='\0';
	
	return succ;
}


int displayPass1tables(MNT mnt[50], int mntc, MDT mdt[50], int mdtc, FPPL fppl[10], int fptr)
{
	int i=0,j=0;

	printf("\n\nMNT");
	printf("\nmname\tsindex\teindex\tno_of_arg");
	for(i=0;i<mntc;i++)
	{
		printf("\n%s\t%d\t%d\t%d",mnt[i].mname,mnt[i].sindex,mnt[i].eindex,mnt[i].no_of_arguments);

	}
/*Check*/
	for(i=0;i<mntc;i++)
	{	
		arg1=mnt[i].no_of_arguments;
	}
	//printf("\narg1:%d",arg1);	
/**/
	printf("\n\nMDT");
	printf("\nindex  label\tinstruction\tno_of_arg");
	for(i=0;i<mdtc;i++)
	{
		printf("\n%d\t %s\t%s\t\t",i,mdt[i].label,mdt[i].instruct);
		for(j=0;j<mdt[i].no;j++)
		{
			printf(" %d",mdt[i].arguments[j]);
		}
	}
	
	printf("\n\nFPPL");
	printf("\nname\tpos");
	for(i=0;i<fptr;i++)
	{
		printf("\n%s\t%d",fppl[i].name,fppl[i].pos);

	}
	printf("\n");

	return 0;
}

int print_IC(Pass1table table1[50], int tp)
{
	int i=0,j=0;
	printf("\nIC File");
	printf("\nlabel\tinstr\tno_of_arg");
	for(i=0;i<tp;i++)
	{
		printf("\n%s\t%s\t",table1[i].label,table1[i].instruct);
		
		for(j=0;j<table1[i].no;j++)
		{
			printf(" %s",table1[i].arguments[j]);
		}

	}

	printf("\n");

	return 0;

}
		
int Pass2(MNT mnt[50], MDT mdt[50], int mntc, Pass1table table1[50], int tp, Pass2table table2[50])
{
	
	int i=0, j=0,l=0, tp2=0, aptr=0, flag=0;
	int temp=0, k=0;
	
	APPL appl[10];
	aptr=0;
	tp2=0;
	for(i=0;i<tp;i++)
	{
		flag=0;
		for(j=0;j<mntc;j++)
		{
			
			if(strcmp(table1[i].instruct,mnt[j].mname)==0)
			{
				flag=1;
				printf("\nMultiple declaration");break;
			}
		}
		

		if(flag==1)	//Macro Call is encountered
		{
		
			temp=j;
			aptr=0;
			
			for(j=0;j<table1[i].no;j++)	//Populating APPL
			{
			
				strcpy(appl[aptr].name,table1[i].arguments[j]);
				appl[aptr].pos=aptr+1;
				
				aptr++;
			}
			
			for(j=mnt[temp].sindex;j<=mnt[temp].eindex;j++)
			{
			
				strcpy(table2[tp2].label,mdt[j].label);
				strcpy(table2[tp2].instruct,mdt[j].instruct);
				table2[tp2].no=mdt[j].no;
				
				for(l=0;l<mdt[j].no;l++)
				{
					
					for(k=0;k<aptr;k++)
					{
						if(mdt[j].arguments[l]==appl[k].pos)
						{
							break;
						}
						
					}
					
					strcpy(table2[tp2].arguments[l], appl[k].name);
					
				}
				
				tp2++;
			}
		
		}
		else		//Regular Instruction
		{
		
			strcpy(table2[tp2].label,table1[i].label);
			strcpy(table2[tp2].instruct,table1[i].instruct);
			table2[tp2].no=table1[i].no;
			
			for(j=0;j<table2[tp2].no;j++)
			{
				strcpy(table2[tp2].arguments[j],table1[i].arguments[j]);
				
			}
			
			tp2++;
		
		}
		
	}
	
	display_APPL(appl,aptr);
	display_Pass2(table2,tp2);
	return tp2;
	
}

void display_Pass2(Pass2table table2[50], int tp2)
{

	int i=0, j=0;

	if(arg1!=arg2)
	{	
		printf("\nParameter mismatch..");
	}
	else	
	{
	printf("\n\nTarget File");
	printf("\nlabel\tinstr\tno_of_arg");
	for(i=0;i<tp2;i++)
	{
		printf("\n%s\t%s\t",table2[i].label,table2[i].instruct);
		
		for(j=0;j<table2[i].no;j++)
		{
			printf(" %s",table2[i].arguments[j]);
			
		}
	}
	}
	printf("\n");
	
}

void display_APPL(APPL appl[10], int aptr)
{

	int i=0;
	printf("\n\nAPPL");
	printf("\nname\tpos");
	for(i=0;i<aptr;i++)
	{
		printf("\n%s\t%d",appl[i].name,appl[i].pos);
	}
	printf("\n");
/*Check*/
	for(i=0;i<aptr;i++)	
	{	
 		arg2=appl[i].pos;
	}
	//printf("\narg2:%d",arg2);	
/**/
}	
