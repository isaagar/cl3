#include<stdio.h>
#include<string.h>
#include<stdlib.h>
 
#define MAX 20
#define M_MAX 11
#define AD_MAX 5
#define R_MAX 4
#define C_MAX 6
 
struct LITTAB
{
    char Lit[5];
    int Addr;
}   L[MAX];
 
struct POOLTAB
{
    int Addr;
};
 
 
int  POOLTAB[MAX],LitCnt,PoolCnt ,TokCnt,LC,i,j,k;
 
char Tok1[MAX],Tok2[MAX],Tok3[MAX],Tok4[MAX],Tok5[MAX],Buffer[80],temp[MAX];
FILE *fp1,*fp2,*fp3;
 
char MOTAB[][10]=
{
    "STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"
};
 
char REGTAB[][10]=    {"AREG","BREG","CREG","DREG"};
char CONDTAB[][10]=    {"LE","LT","EQ","GT","GE","ANY"};
char ADTAB[][10]=    {"START","END","ORIGIN","EQU","LTORG"};
 
 
 
int  SearchLit(char *s)
{
        int i;
        for( i=POOLTAB[PoolCnt]; i< LitCnt; i++)
        {
            if(strcmp(L[i].Lit,s)==0)
            return (i);
        }
            return -1;
}
 
 
int SearchReg(char *s)
{
    int i;
    for(i=0;i<R_MAX;i++)
    {
        if(strcmp(REGTAB[i],s)==0)
            return i;
    }
    return -1;
}
 
 
int SearchDirective(char *s)
{
    int i;
    for(i=0;i<AD_MAX;i++)
    {
        if(strcmp(ADTAB[i],s)==0)
            return i;
    }
    return -1;
}
 
 
int SearchOp(char *s)
{
    int i;
    for(i=0;i<M_MAX;i++)
    {
        if(strcmp(MOTAB[i],s)==0)
            return i;
    }
    return -1;
}
 
int SearchCond(char *s)
{
    int i;
    for(i=0;i<C_MAX;i++)
    {
        if(strcmp(CONDTAB[i],s)==0)
            return i;
    }
    return -1;
}
 
void PassOne()
{
    fp1=fopen("vim.asm","r");
    if(fp1==NULL)
    {
        printf("\nCannot Open Input File\n");
        exit(0);
    }
    fp2=fopen("vim.txt","w");
    if(fp2==NULL)
    {
        printf("\nCannot Create File\n");
        exit(0);
    }
    while(fgets(Buffer,50,fp1))
    {
        strcpy(Tok1,"");
        strcpy(Tok2,"");
        strcpy(Tok3,"");
        strcpy(Tok4,"");
        TokCnt=sscanf(Buffer,"%s%s%s%s",Tok1,Tok2,Tok3,Tok4);
        switch(TokCnt)
        {
            case 1:
                i=SearchOp(Tok1);
                if(i==0)
            {
                fprintf(fp2,"(IS, %02d)\n",i);
                break;
            }
                i=SearchDirective(Tok1);
                if(i==0)
            {
                fprintf(fp2,"(AD, %02d)\n",i);
                LC=-1;
            }
            else if(i==1 || i==4)
            {
                fprintf(fp2,"(AD, %02d)\n",i);
                 
            for(k=POOLTAB[PoolCnt];k<LitCnt;k++)
                 
                L[k].Addr=LC++;
                     
                POOLTAB[++PoolCnt]=LitCnt;
                LC--;
                 
            }
            break;
         
         
         
         
         
        case 2:
         
        i=SearchOp(Tok1);
        i=SearchDirective(Tok1);
        if(i==0 ||i==2)
        {
            LC=atoi(Tok2)-1;
            fprintf(fp2,"(AD, %02d) (C, %03d)\n",i,LC+1);
            break;
        }
               break;
             
        case 3:
         
        i=SearchOp(Tok1);
        if(i>=1 && i <=8)
        {
        if (Tok3[0]=='=')
        {
                j=SearchLit(Tok3);
                 
                 
        if(j==-1)
        {
            sprintf(temp,"(L, %02d)",LitCnt);
            strcpy(L[LitCnt++].Lit,Tok3);
        }
                 
        else
        {
            sprintf(temp,"(L, %02d)",j);
        }
        }
        }
         
         
        Tok2[strlen(Tok2)-1]='\0';
        if(i==7)
            j=SearchCond(Tok2);
        else
            j=SearchReg(Tok2);
         
            fprintf(fp2,"(IS, %02d) (%d) %s\n",i,j,temp);
        break;
        }
        LC++; 
    }
    fcloseall();
}
 
void PassTwo()
{
int i,j,k;
LC=0;
 
if((fp2=fopen("vim.txt","r"))==NULL)
{
    printf("\n Cannot Open Intermediate code File");
exit(0);
}
if((fp3=fopen("vim_target.txt","w"))==NULL)
{
    printf("\n Cannot create Target File");
    exit(0);
}
while(fgets(Buffer,80,fp2))
{
    TokCnt=sscanf(Buffer,"%s %s %s %s %s",Tok1,Tok2,Tok3,Tok4,Tok5);
    Tok1[strlen(Tok1)-1]='\0';
    Tok2[strlen(Tok2)-1]='\0';
    Tok3[strlen(Tok3)-1]='\0';
    Tok4[strlen(Tok4)-1]='\0';
    Tok5[strlen(Tok5)-1]='\0';
     switch(TokCnt)
     {
 
 case 2:
     if(strcmp(Tok1+1,"AD")==0) //START
      
     {
     for(j=0;j<PoolCnt;j++)
     if(L[POOLTAB[j]].Addr==LC)
     break;
     for(i=POOLTAB[j];i<POOLTAB[j+1];i++)
     {
         strcpy(temp,L[i].Lit);
         temp[strlen(temp)-1]='\0';
         fprintf(fp3,"%d) + 00 0 %03d\n",LC++,atoi(strstr(temp,"'")+1));
     }
         LC--;
     }
      
         else if(strcmp(Tok1+1,"IS")==0) //STOP
     {
         fprintf(fp3,"%d) + 00 0 000\n",LC);
     }
     break;
      
      
 
 case 4: //START/ORIGI
     if(strcmp(Tok1+1,"AD")==0)  //START,ORIGIN
     {
         LC=atoi(Tok4)-1;
     }
     else if(atoi(Tok2)==0)
     {
         fprintf(fp3,"%d) + 00 0  %03d\n",LC,atoi(Tok4));
     }
     break;
      
      
case 5:
 
     fprintf(fp3,"%d) + %02d %d %03d\n",LC,atoi(Tok2),atoi(Tok3+1),L[atoi(Tok5)].Addr);
     break;
 }//switch
 LC++;
}//while
         
}
 
 
 
     
void display_Lit()
{
    int i;
    printf("*****Literal Table*****");
    printf("\n Literal Address\n\t");
    for(i=0;i<LitCnt; i++)
    {
        printf("\n %s\t  %03d\t \n", L[i].Lit, L[i].Addr);
    }
}
 
 
void display_Pool()
{
    int i;
    printf("****Pool Table****");
    printf("\nAddress\t");
    for(i=0;i<PoolCnt; i++)
    {
        printf("\n  %d\t \n", POOLTAB[i]);
    }
}
 
void main()
{
    PassOne();
    PassTwo();
    display_Lit();
    display_Pool();
}     
 
 
 
/* OUTPUT:
    ASM File:
     
    START  200
    ADD  AREG,  ='1'
    MULT  BREG,  ='2'
        LTORG
    MOVER  CREG,  ='7'
    SUB  CREG,  ='8'
    STOP
    END
 
kumud@ kumud -HP:~/Desktop/vim$ gcc -o v lit.c
kumud@ kumud -HP:~/Desktop/vim$ ./v
 
*****Literal Table*****
 Literal Address
     
 ='1'      202     
 
 ='2'      203     
 
 ='7'      207     
 
 ='8'      208     
****Pool Table****
Address     
  0     
 
  2     
kumud@kumud -HP:~/Desktop/vim$ cat vim.txt
 
(AD, 00) (C, 200)
(IS, 01) (0) (L, 00)
(IS, 03) (1) (L, 01)
(AD, 04)
(IS, 04) (2) (L, 02)
(IS, 02) (2) (L, 03)
(IS, 00)
(AD, 01)
 
kumud@ kumud -HP:~/Desktop/vim$ cat vim_target.txt
200) + 01 0 202
201) + 03 1 203
202) + 00 0 001
203) + 00 0 002
204) + 04 2 207
205) + 02 2 208
206) + 00 0 000
207) + 00 0 007
208) + 00 0 008 
