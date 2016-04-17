
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct op_table
{
	char mnemonic[7];
	char class[3];
	char opcode[3];
	int chain;
	char length;
};

struct register_table
{
	char reg[5];
	int opcode;
};

struct operator_table
{
	char operator[4];
	int opcode;
};

struct symbol_table
{
	char index[3];
	char symbol[20];
	int addr;
	int len;
};

struct ic
{
	int addr;
	char opcode[8];
	int opreg;
	char operandcode[10];
};

struct undefinedsymbol
{
	char index[3];
	char symbol[20];
};

struct target_file
{
	char opcode[3];
	int mem_operand;
	int operator;
	int address;
	char sign;
};

struct wrongmnemonic
{
	char mnemonic[7];
}wm[20];

struct literal_table
{
	char literal[6];
	int addr;
	int index;

}lt[20];

struct pool_table
{
	int index;
}pt[20];

int main(void)
{
	int i,pool_i=0;

	struct op_table ob[18]=
	{	
		{"DS","DL","02",1,'-'},
		{"START","AD","01",2,'-'},
		{"END","AD","02",3,'-'},
		{"EQU","AD","04",-1,'-'},
		{"LTORG","AD","05",-1,'-'},
		{"MUL","IS","03",6,'1'},
		{"MOVER","IS","04",7,'1'},
		{"MOVEM","IS","05",9,'1'},
		{"PRINT","IS","10",-1,'1'},
		{"ORIGIN","AD","03",-1,'-'},
		{"READ","IS","09",-1,'1'},
		{"STOP","IS","00",12,'1'},
		{"ADD","IS","01",13,'1'},
		{"SUB","IS","02",14,'1'},
		{"COMP","IS","06",15,'1'},
		{"BC","IS","07",16,'1'},
		{"DIV","IS","08",17,'1'},
		{"DC","DL","01",0,'-'}
	};

	struct register_table ob1[4]=
	{
		{"AREG",1},
		{"BREG",2},
		{"CREG",3},
		{"DREG",4}
	};

	struct operator_table ob2[6]=
	{
		{"LT",1},
		{"LE",2},
		{"GT",3},
		{"GE",4},
		{"EE",5},
		{"ANY",6}
	};

	struct symbol_table ob3[20];
	struct ic ob4[20];
	struct undefinedsymbol us[20];
	struct target_file tf[20];

	printf("\n\n----- MOT / OPTAB ----- \n\n");
	printf("Index\tMnemonic\tClass\tOpcode\tChain\tLength\n");

	for(i=0;i<18;i++)
	{
		printf("%d\t%s\t\t%s\t%s\t%d\t%c\n",i,ob[i].mnemonic,ob[i].class,ob[i].opcode,ob[i].chain,ob[i].length);
	}

	printf("\n\n--- REGISTER TABLE --- \n\n");
	printf("Opcode\tRegister\n");
	for(i=0;i<4;i++)
	{
		printf("%d\t%s\n",ob1[i].opcode,ob1[i].reg);
	}

	printf("\n\n--- OPERATOR TABLE --- \n\n");
	printf("Opcode\tOperators\n");
	for(i=0;i<6;i++)
	{
		printf("%d\t%s\n",ob2[i].opcode,ob2[i].operator);
	}

	char ch, f1[25],word[20],buf[20],var[10],prevbuf[20],class1[3],lit[2];
	char ad[10], ad1[2];
	int wm_i=0,lt_i=0,l;
	int hash;
	int c;
	int j=0;
	int error_i=0;
	int target_i=0;
	int g,equ,cmp,h;
	int flag=0;
	int s=0;
	int d;
	int f=0;
	int f2=0;
	int cm=0,cm1=0,cm2=0,cm3=0,cm4=0,cm5=0,cm6=0;
	int cmpds,cmpdc,cmpequ,equaddr;
	int m=0;
	int flag1=0;
	int n=0;
	int addr=0;
	int num=0;
	
	FILE *fp1 = fopen("file.txt","r");

	if (fp1==NULL)
	{
		printf("Error in opening file %s", f1);
		exit(0);
	}


	for(i=0;i<20;i++)
		lt[i].addr=0;

	c=fscanf(fp1,"%c",&ch);

	while(c!=-1)
	{
		flag=0;
		f=0;
		f2=0;
		flag1=0;



		if(ch==' '||ch=='\n'||ch==','||ch==':')
		{
			word[j]='\0';
			cm=strcmp(word,"START");
			if(cm==0)
			{
				c=fscanf(fp1,"%c",&ch);
				while(ch!='\n')
				{

				buf[m++]=ch;
				c=fscanf(fp1,"%c",&ch);

				}
				buf[m]='\0';
				for(d=0;d<m;d++)
				{
					if(isdigit(buf[d]))
						flag1=1;
					else
					{
						flag1=0;
						break;
					}
				}
				if(flag1==1)
				{
					addr=atoi(buf);
					//printf("Address is %d",addr);

				}
				else
				{
					strcpy(ob3[s++].symbol,buf);
				}

				buf[0] = '\0' ;
				m = 0 ;

			}
			hash=word[0]%18;
			//printf("\nString is %s",word);

			while(hash!=-1)
			{

				cmp=strcmp(ob[hash].mnemonic,word);
				if(cmp==0)
				{
					cm1=strcmp(word,"START");
					cm2=strcmp(word,"END");
					cm3=strcmp(word,"DS");
					cm4=strcmp(word,"DC");
					cm5=strcmp(word,"EQU");
					cm6=strcmp(word,"LTORG");
					if(cm1==0)
					{
						strcpy(ob4[n].opcode,ob[hash].class);
						strcat(ob4[n].opcode,",");
						strcat(ob4[n].opcode,ob[hash].opcode);

						ob4[n].opreg=0;
						strcpy(ob4[n].operandcode,"C");
						strcat(ob4[n].operandcode,",");
						sprintf(ad,"%d",addr);
						strcat(ob4[n].operandcode,ad);
						ob4[n].addr=0;

					}
					else if(cm2==0)
					{
						strcpy(ob4[n].opcode,ob[hash].class);
						strcat(ob4[n].opcode,",");
						strcat(ob4[n].opcode,ob[hash].opcode);
						ob4[n].addr=0;

					}
					else if(cm3==0)
					{
						c=fscanf(fp1,"%c",&ch);
						while(ch!='\n')
						{

							buf[m++]=ch;
							c=fscanf(fp1,"%c",&ch);

						}
						buf[m]='\0';

						num=atoi(buf);
						for(i=0;i<s;i++)
						{
							cmpds=strcmp(prevbuf,ob3[i].symbol);
							if(cmpds==0)
							{
								ob3[i].addr=addr;
								ob3[i].len=num;
								break;
							}
						}


						ob4[n].addr=addr;

						addr=addr+num-1;

						strcpy(ob4[n].opcode,ob[hash].class);
						strcat(ob4[n].opcode,",");
						strcat(ob4[n].opcode,ob[hash].opcode);
						strcpy(ob4[n].operandcode,"-");


						buf[0] = '\0' ;
						m = 0 ;
					}
					else if(cm4==0)
					{
						c=fscanf(fp1,"%c",&ch);
						while(ch!='\n')
						{

							buf[m]=ch;
							buf[m+1] = '\0' ;
							m++ ;
							c=fscanf(fp1,"%c",&ch);

						}
						buf[m]='\0';
						for(i=0;i<s;i++)
						{
							cmpdc=strcmp(prevbuf,ob3[i].symbol);
							if(cmpdc==0)
							{
								ob3[i].addr=addr;
								ob3[i].len=1;
								break;
							}
						}
						ob4[n].addr=addr;

						//addr++;
						strcpy(ob4[n].opcode,ob[hash].class);
						strcat(ob4[n].opcode,",");
						strcat(ob4[n].opcode,ob[hash].opcode);
						strcpy(ob4[n].operandcode,"C");
						strcat(ob4[n].operandcode,",");
						strcat(ob4[n].operandcode,buf);


						buf[0] = '\0' ;
						m = 0 ;
					}
					else if(cm5==0)
					{
						strcpy(ob4[n].opcode,ob[hash].class);
						strcat(ob4[n].opcode,",");
						strcat(ob4[n].opcode,ob[hash].opcode);

						ob4[n].opreg=0;

						c=fscanf(fp1,"%c",&ch);
						while(ch!='\n')
						{

							buf[m++]=ch;
							c=fscanf(fp1,"%c",&ch);

						}
						buf[m]='\0';

						for(d=0;d<m;d++)
						{
							if(isdigit(buf[d]))
							flag1=1;
							else
							{
								flag1=0;
								break;
							}
						}
						ob4[n].addr=0;
						if(flag1==1)
						{

							equ=atoi(buf);
							strcpy(ob4[n].operandcode,"C");
							strcat(ob4[n].operandcode,",");
							sprintf(ad,"%d",equ);
							strcat(ob4[n].operandcode,ad);
							equaddr=equ;

						}
						else
						{
							for(i=0;i<s;i++)
							{
								cmpequ=strcmp(buf,ob3[i].symbol);
								if(cmpequ==0)
								{
									strcpy(ob4[n].operandcode,"S");
									strcat(ob4[n].operandcode,",");
									strcat(ob4[n].operandcode,ob3[i].index);
									equaddr=ob3[i].addr;
									break;
								}
							}
						}
						for(i=0;i<s;i++)
						{
							cmpequ=strcmp(prevbuf,ob3[i].symbol);
							if(cmpequ==0)
							{
								ob3[i].addr=equaddr;
								break;
							}
						}


						buf[0] = '\0' ;
						m = 0 ;
					}

					else if(cm6==0)
					{
						strcpy(ob4[n].opcode,ob[hash].class);
						strcat(ob4[n].opcode,",");
						strcat(ob4[n].opcode,ob[hash].opcode);

						ob4[n].opreg=0;
						strcpy(ob4[n].operandcode,"-");
						ob4[n].addr=0;

					}
					else
					{
						//ob4[n].addr=addr;
						//addr++;
						strcpy(ob4[n].opcode,ob[hash].class);
						strcat(ob4[n].opcode,",");
						strcat(ob4[n].opcode,ob[hash].opcode);

					}
					flag=1;
					j=0;
					strcpy(prevbuf,word);

					word[0] = '\0' ;
					j = 0 ;
					break;
				}
				else
				{
					h=hash;
					hash=ob[h].chain;
				}
			}


			if(flag==0)
			{

				if(word[0]=='=')
				{

					if(strcmp(prevbuf,"LTORG")==0||strcmp(prevbuf,"END")==0||prevbuf[0]=='=')
					{

						for(i=0;i<lt_i;i++)
						{

							if(strcmp(lt[i].literal,word)==0)
							{

								if(lt[i].addr==0)
									lt[i].addr=addr;
								sprintf(ad1,"%d",i+1);
								strcpy(ob4[n].operandcode,"L");
								strcat(ob4[n].operandcode,",0");
								strcat(ob4[n].operandcode,ad1);

							}

						}
					}

					else
					{
						strcpy(lt[lt_i].literal,word);
						lt[lt_i].index=lt_i+1;
						lt_i++;
						sprintf(ad1,"%d",lt_i);
						strcpy(ob4[n].operandcode,"L");
						strcat(ob4[n].operandcode,",0");
						strcat(ob4[n].operandcode,ad1);


					}
					strcpy(prevbuf,word);
					word[0] = '\0' ;
					j = 0 ;
					flag=1;

				}
			}
			if(flag==0)
			{
				for(i=0;i<4;i++)
				{
					cmp=strcmp(ob1[i].reg,word);
					if(cmp==0)
					{
						//printf("\nOpcode is %d\n",ob1[i].opcode);

						ob4[n].opreg=ob1[i].opcode;
						flag=1;

						strcpy(prevbuf,word);
						word[0] = '\0' ;
						j = 0 ;
						break;
					}
				}
			}
			if(flag==0)
						{
							for(i=0;i<6;i++)
							{
								cmp=strcmp(ob2[i].operator,word);
								if(cmp==0)
								{
									//printf("\nOpcode is %d\n",ob2[i].opcode);
									ob4[n].opreg=ob2[i].opcode;
									flag=1;

									strcpy(prevbuf,word);
									word[0] = '\0' ;
									j = 0 ;
									break;
								}
							}
						}



			if(flag==0)
			{

				int x=0;

				if(strcmp(prevbuf,"XYZ")==0 && ch!=':')
				{
					x=0;
					for(i=0;i<s;i++)
					{
						cmp=strcmp(word,ob3[i].symbol);
						if(cmp==0)
						{
							x=1;
							break;
						}
					}
					if(x==0)
					{
							printf("\n%s is a Wrong mnemonic", word);
							strcpy(wm[wm_i].mnemonic,word);
							wm_i++;
					}

				}
				else
				{

				for(d=0;d<j;d++)
				{
					if(isdigit(word[d]))
						f=1;
					else
					{
						f=0;
						break;
					}
				}

				if(f==0)
				{


					ob3[s].len=0;

					for(i=0;i<s;i++)
					{
						cmp=strcmp(ob3[i].symbol,word);
						if(cmp==0)
						{
							f2=1;

							strcpy(ob4[n].operandcode,"S");
							strcat(ob4[n].operandcode,",");
							strcat(ob4[n].operandcode,ob3[i].index);


							break;
						}


					}
					if(f2==0)
					{
						if(s>9)
						{
							sprintf(var,"%d",s);

							strcpy(ob3[s].index,var);

						}
						else
						{

							sprintf(var,"%d",s+1);
							strcpy(ob3[s].index,"0");
							strcat(ob3[s].index,var);

						}

						strcpy(ob3[s].symbol,word);
						strcpy(ob4[n].operandcode,"S");
						strcat(ob4[n].operandcode,",");
						strcat(ob4[n].operandcode,ob3[s].index);

						if(ch==':')
						{
							ob3[s].addr=addr;
						}


						s++;
					}



				}
				}





				strcpy(prevbuf,word);
				word[0] = '\0' ;
				j = 0 ;

			}
			if(ch=='\n')
			{

				n++;
				ob4[n].opreg=0;
				strcpy(ob4[n].operandcode,"-");
				strcpy(ob4[n].opcode,"-");
				//strcpy(prevbuf,"XYZ");
				if(ob4[n-1].opcode[0]!='A' && ob4[n-1].opcode[1]!='D')
					addr++;
				ob4[n].addr=addr;
			}
		}
		else
		{
			word[j++]=ch;
		}
		c=fscanf(fp1,"%c",&ch);

	}

	//ERROR HANDLING
		for(g=0;g<s;g++)
		{
			if(ob3[g].addr==0)
			{
				strcpy(us[error_i].index,ob3[g].index);
				strcpy(us[error_i].symbol,ob3[g].symbol);
				error_i++;
			}
		}

		//TARGET CODE
			for(g=0;g<n;g++)
			{
				class1[0]=ob4[g].opcode[0];
				class1[1]=ob4[g].opcode[1];
				class1[2]='\0';
				if(!(strcmp(class1,"AD")==0))
				{
					class1[0]=ob4[g].opcode[3];
					class1[1]=ob4[g].opcode[4];
					class1[2]='\0';
					strcpy(tf[target_i].opcode,class1);
					tf[target_i].operator=ob4[g].opreg;
					tf[target_i].address=ob4[g].addr;
					tf[target_i].sign='+';
					class1[0]=ob4[g].opcode[0];
					class1[1]=ob4[g].opcode[1];
					class1[2]='\0';
					if(!(strcmp(class1,"DL")==0))
					{
						if(ob4[g].operandcode[0]=='-')
						{
							tf[target_i].mem_operand=0;

						}
						else
						{
						class1[0]=ob4[g].operandcode[3];
						class1[1]='\0';
						j=atoi(class1);
						j--;
						if(ob4[g].operandcode[0]!='L')
							tf[target_i].mem_operand=ob3[j].addr;
						else
							tf[target_i].mem_operand=lt[j].addr;
					}
				}
					else
						tf[target_i].mem_operand=0;
						target_i++;
				}
			}

	printf("\n\n----Symbol Table----\n\n");
	printf("INDEX\tSYMBOL\tADDRESS\tLENGTH\tRELOCATION STATUS\n");
	for(i=0;i<s;i++)
	{
		printf("\n %s\t%s\t%d\t%d\tR",ob3[i].index,ob3[i].symbol,ob3[i].addr,ob3[i].len );
	}
	printf("\n\n-----IC File-----\n\n");
	printf("ADDRESS\tMNEUMONIC_op\tOPERATOR/REGISTER\tOPERAND CODE\n");
	for(i=0;i<n;i++)
		{
			printf("\n%d\t%s\t\t\t%d\t\t%s\t",ob4[i].addr,ob4[i].opcode,ob4[i].opreg,ob4[i].operandcode );
		}
	printf("\n\n-----TARGET FILE-----\n\n");
		printf("ADDRESS\tSIGN\tOPCODE\tOPERATOR\tMEM_OP\n");

			for(i=0;i<target_i;i++)
			{
				if(tf[i].address!=0)
				printf("%d\t%c\t%s\t%d\t\t%d\n",tf[i].address,tf[i].sign,tf[i].opcode,tf[i].operator,tf[i].mem_operand);
			}
	if(error_i>0)
	{
	printf("\n\nError:Undefined Symbol\n");
	for(i=0;i<error_i;i++)
		{
			printf("%s\t%s",us[i].index,us[i].symbol);
		}
	}
	if(wm_i>0)
		{
		printf("\n\nError:Wrong Mnemonic\n");
		for(i=0;i<wm_i;i++)
			{
				printf("%s\t",wm[i].mnemonic);
			}
		}



	return 0;
}
