#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
#define MAX 20            //Maximum entries for symbol table
#define M_MAX 11        //Maximum number of mnemonics
#define AD_MAX 5         //Maximum number of assembler directives
#define R_MAX 4            //Maximum number of registers
#define C_MAX 6		//Maximum number of conditional codes

//Variables		
int SymbCnt, LitCnt, PoolCnt, TokCnt, LC, i,j,k;
char Tok1[MAX], Tok2[MAX], Tok3[MAX], Tok4[MAX], Tok5[MAX], Buffer[80], temp[MAX];
FILE *fp1, *fp2, *fp, *fpErr;     
static int errFlag;         

//Data Structures
int POOLTAB[MAX];
char MOTAB[][10]    =  {"STOP", "ADD", "SUB", "MULT", "MOVER", "MOVEM", "COMP", "BC", "DIV", "READ", "PRINT"};
char REGTAB[][10]   =  {"AREG", "BREG", "CREG","DREG"};
char CONDTAB[][10]  =  {"LT", "LE", "EQ", "GT", "GE", "ANY"};
char ADTAB[][10]    =  {"START", "END", "ORIGIN", "EQU", "LTORG"};
 
struct SYMTAB
{
    char Symb[10];
    int Addr;
    int Used, Defined;
}S[MAX];
  
struct LITTAB
{
    char Lit[5];
    int Addr;
}L[MAX];
 
 
//Functions  
int SearchSymb(char *s)
{
    int i;
    for(i = 0; i < SymbCnt; i++)
    {
        if(strcmp(S[i].Symb,s) == 0)
            return(i);
    }
    return(-1);
}
 
int SearchLit(char *s)
{
    int i;
    for(i = POOLTAB[PoolCnt]; i < LitCnt; i++)
    {
        if(strcmp(L[i].Lit,s) == 0)
            return(i);
    }
    return(-1);
}
 
int SearchOp(char *s)
{
    int i;
    for(i = 0; i < M_MAX; i++)
    {
        if(strcmp(MOTAB[i],s) == 0)
            return(i);
    }
    return (-1);
}
 
int SearchDirective(char *s)
{
    int i;
    for(i = 0; i < AD_MAX; i++)
    {
        if(strcmp(ADTAB[i],s) == 0)
            return(i);
    }
    return (-1);
}
 
int SearchReg(char *s)
{
    int i;
    for(i = 0; i < R_MAX; i++)
    {
        if(strcmp(REGTAB[i],s) == 0)
            return(i);
    }
    return(-1);
}
 
int SearchCON(char *s)
{
        int i;
        for(i=0;i< C_MAX;i++) 
        {
                if(strcmp(CONDTAB[i],s)==0)
                      return i; 
        }
      return -1;
} 
 
void PassOne()
{
    //fp1 - ptr of source file
    //fp2 - ptr of Intermediate code file
    int k;
    fp1 = fopen("input.asm", "r");
    if(fp1 == NULL)
    {
        printf("\nCannot open the file");
        exit(0);
    }
     
    fp2 = fopen("input.txt", "w");
    if(fp2 == NULL)
    {
        printf("\nCannot create the file");
        exit(0);
    }
     
    while(fgets(Buffer,50,fp1))
    {
        //Initialise tokens to null
        strcpy(Tok1,"");
        strcpy(Tok2,"");
        strcpy(Tok3,"");
        strcpy(Tok4,"");
         
        TokCnt = sscanf(Buffer, "%s %s %s %s",Tok1, Tok2, Tok3, Tok4);   
         
        switch(TokCnt)
        {
            case 1 :  //STOP,START,LTORG,END
                 
                 i = SearchOp(Tok1);
                 if(i == 0)            //STOP
                 {
                     fprintf(fp2,"(IS,   %02d)\n",i);
                     break;
                 }
                 
                 i = SearchDirective(Tok1);
                 
                 if(i == 0)
                 { 
                    fprintf(fp2,"(AD,%02d)\n",i);
                    LC = -1;
                 }
                 
                 else if(i == 1 || i == 4)    //END or LTORG
                 {
                     fprintf(fp2,"(AD.%02d)\n",i);
                      
                     for(k = POOLTAB[PoolCnt]; k < LitCnt; k++)
                         L[k].Addr = LC++;
                          
                     POOLTAB[++PoolCnt] = LitCnt;
                     LC--;
                 }
                 
                 break;        //end of case 1
             
            case 2 : //READ, PRINT, START, ORIGIN         
                 i = SearchOp(Tok1);        // i for search in opcodes
                 k = SearchDirective(Tok1);    //Search in ADTAB
                 
                 if(i == 9 || i == 10)
                 {
                     j = SearchSymb(Tok2);
                      
                     if(j == -1)
                     {
                         fprintf(fp2, "(IS, %02d) (S, %02d)\n",i,SymbCnt);
                         strcpy(S[SymbCnt].Symb, Tok2);
                         S[SymbCnt++].Used = 1;
                     }                      
                     else
                     {
                         fprintf(fp2, "(IS,    %02d) (S, %02d)\n",i,j);
                     }
                     break;
                 }
                 
                          
                 if(k == 0 || k == 2)           //START or ORIGIN
                 {
                     LC = atoi(Tok2) - 1;
                      
                     fprintf(fp2, "(AD, %02d) (C, %03d)\n",k,LC+1);
                     break;
                 }                 
                 
                 if( i == -1 || k == -1 )
                 {
                     fprintf(fp2, "%s --- Invalid Instruction\n", Tok1);
                     errFlag = 1;
                     break;
                 }
                 break;         //end of case 2
                 
                 
            case 3 : //ADD to DIV and DS/DC
                                 
                                 i = SearchOp(Tok1);
                                
                                 if(i >= 1 && i <= 8)           //if Assembler directive
                                 {
                                        if(Tok3[0] == '=')      //Literal
                                        {
                                                j = SearchLit(Tok3);
                                                
                                                if(j == -1)     //Literal not present
                                                {
                                                        sprintf(temp,"(L, %02d)",LitCnt);
                                                        strcpy(L[LitCnt++].Lit,Tok3);
                                                }
                                                
                                                else
                                                        sprintf(temp,"(L,%02d)",j);
                                         }     //end of literal case
                                          
                                          
                                          
                                          else          //operand is symbol
                                          {
                                                j = SearchSymb(Tok3);
                                                
                                                if(j == -1)     //Symbol not present
                                                {
                                                        sprintf(temp,"(S,%02d)",SymbCnt);
                                                        strcpy(S[SymbCnt].Symb,Tok3);
                                                        S[SymbCnt++].Used = 1;
                                                }
                                                
                                                else
                                                        sprintf(temp,"(S,%02d)",j);
                                          }             //end of symbol case
                                                                                                                           
                                          Tok2[strlen(Tok2) - 1] = '\0';
                                          
                                          if(i == 7)    //first token is BC
                                                j = SearchCON(Tok2);
                                                
                                          else
                                                j = SearchReg(Tok2);
                                                
                                          fprintf(fp2,"(IS,   %02d) (%d) %s\n",i,j,temp);
                                          break;
                                  } // end of i 1 to 8                                  
                                                                   
                                  if(strcmp(Tok2,"DC") == 0)            //dc
                                  {
                                        j = SearchSymb(Tok1);
                                        
                                        if(j == -1)             //symbol not present
                                        {
                                                strcpy(S[SymbCnt].Symb,Tok1);
                                                S[SymbCnt++].Addr = LC;
                                        }
                                        
                                        else    //Symbol present
                                                S[j].Addr = LC;
                                         S[j].Defined = 1;
                                        fprintf(fp2,"(DL, 00) (C, %02d)\n",atoi(Tok3));
                                        break;
                                  }     //end of dc
                                                                                                              
                                  if(strcmp(Tok2,"DS") == 0)    //ds
                                  {
                                        j = SearchSymb(Tok1);
                                        
                                        if(j == -1)     //symbol not present
                                        {
                                                strcpy(S[SymbCnt].Symb,Tok1);
                                                
                                                S[SymbCnt++].Addr = LC;
                                        }
                                        
                                        else
                                      
                                                S[j].Addr = LC;
                                         S[j].Defined = 1;
                                       
                                        LC += atoi(Tok3) - 1;
                                        fprintf(fp2,"(DL, 01) (C, %02d)\n",atoi(Tok3));
                                        break;
                                  }     //end of Ds                                                                   
 
                                  i = SearchDirective(Tok2);        //EQU
                                  if(i == 3)
                                  {
                                      k = SearchSymb(Tok3);
                                      j = SearchSymb(Tok1);
                                       
                                      if(j == -1)    //not present
                                      {
                                          strcpy(S[SymbCnt].Symb,Tok1);
                                          S[SymbCnt++].Addr = S[k].Addr;
                                      }
                                       
                                      else
                                          S[j].Addr = S[k].Addr;
                                       
                                      fprintf(fp2, "(AD,%02d)\n",i);
                                      LC--;
                                       
                                     break;               //end of EQU
                                 }
                            
                                        break;                //end of case 3                      
 
                      case 4 :     //instructions with labels
                              j = SearchSymb(Tok1);    //label
                               
                              if(j == -1)
                              {
                                  strcpy(S[SymbCnt].Symb,Tok1);
                                  S[SymbCnt++].Addr = LC;
                              }
                               
                              else        //present, update address
                                  S[j].Addr = LC;
                                   
                              //end of symbol present
                                   
                             
                            i = SearchOp(Tok2);
                             
                            if(i >= 1  &&  i <= 8)            //add-div
                                if(Tok4[0] == '=')        //operand is literal
                                {
                                    j = SearchLit(Tok4);
                                    if(j == -1)
                                    {
                                        sprintf(temp, "(L, %02d)",LitCnt);
                                        strcpy(L[LitCnt++].Lit,Tok4);
                                    }
                                     
                                    else
                                        sprintf(temp,"(L, %02d)",j);
                                }
                             
                            else                    //operand is symbol
                            {
                                j = SearchSymb(Tok4);
                                if(j == -1)
                                {
                                    sprintf(temp,"(S,%02d)",SymbCnt);
                                    strcpy(S[SymbCnt++].Symb,Tok4);
                                }
                                 
                                else
                                    sprintf(temp,"(S,%02d)",j);
                                     
                            }        //end of operand is symbol
                             
                            Tok3[strlen(Tok3) - 1] = '\0';        //remove
                             
                            if(i == 7)                 //first oerand is reg or cond
                                j = SearchCON(Tok3);
                            else
                                j = SearchReg(Tok3);
                                fprintf(fp2,"(IS,   %02d) (%d) %s\n",i,j,temp);
                                 
                            break;                //end case 4
                  } //end of switch
        LC++;
    }// end of while
    fcloseall();
}//End of PassOne
void PassTwo()
{
    int i,j,k;
    LC = 0;
     
    if((fp1 = fopen("input.txt","r")) == NULL)
    {
        printf("\nCannot open Intermediate Code file");
        exit(0);
    }
     
    if((fp2 = fopen("target.txt","w")) == NULL)
    {
        printf("\nCannot open Target Code file");
        exit(0);
    }
     
    while(fgets(Buffer,80,fp1))
    {
        TokCnt = sscanf(Buffer,"%s %s %s %s %s",Tok1,Tok2,Tok3,Tok4,Tok5);
        Tok1[strlen(Tok1) - 1] = '\0';
        Tok2[strlen(Tok2) - 1] = '\0';
        Tok3[strlen(Tok3) - 1] = '\0';
        Tok4[strlen(Tok4) - 1] = '\0';
        Tok5[strlen(Tok5) - 1] = '\0';
     
        switch(TokCnt)
        {
            case 2 : if(strcmp(Tok1 + 1,"AD") ==0)    //START
                    LC--;
                 else if(strcmp(Tok1 + 1,"IS") == 0)    //Stop
                     fprintf(fp2,"%d) + 00 0 000\n",LC);
                 break;
                 
            case 4 : if(strcmp(Tok1 + 1,"AD") == 0)    //START,ORIGIN
                     LC = atoi(Tok4) - 1;
                 
                 else if(strcmp(Tok1 + 1,"IS") == 0)    //READ,PRINT
                     fprintf(fp2,"%d) + %02d 0 %03d\n",LC,atoi(Tok2),S[atoi(Tok4)].Addr);
                 
                 else if(strcmp(Tok1 + 1,"DL") == 0)
                 {
                     if(atoi(Tok2) == 1)    //Ds
                     {
                         for(i = 0; i < atoi(Tok4); i++)
                             fprintf(fp2,"%d)\n",LC++);
                         LC--;
                     }
                      
                     else if(atoi(Tok2) == 0)    //DC
                         fprintf(fp2,"%d) + 00 0 %03d\n",LC,atoi(Tok4));
                 }
                 break;
                 
            case 5 : fprintf(fp2,"%d) + %02d %d %03d\n",LC,atoi(Tok2),atoi(Tok3+1),S[atoi(Tok5)].Addr);
                 break;
        }//end of switch
        LC++;
    }//end of while
    fcloseall();
}//end of PassTwo
                                  
void display_Symbtab()
{
        int i;
         printf("\nSymbName\tAddress\t\tUsed\tDefined\n");         
        for(i = 0; i < SymbCnt; i++)
        {
                printf("%s\t\t%d\t\t%d\t%d\n",S[i].Symb,S[i].Addr,S[i].Used,S[i].Defined);
                fpErr = fopen("Error.txt", "w");
                if ( S[i].Used == 1 && S[i].Defined == 0 )
                {
                    fprintf(fpErr, "\nError : Symbol %s is Used but not Defined", S[i].Symb);
                }
                if ( S[i].Defined == 1 && S[i].Used == 0 )
                {
                    fprintf(fpErr, "\nWarning : Symbol %s is Defined but not Used", S[i].Symb);
                }
        }                
}

void display_Err()
{
    fpErr = fopen("Error.txt", "r");
    if( fpErr == NULL)
    {
        printf("\nCannot Open File");
        exit(0);
    }
    while(fgets(Buffer,80,fpErr))
        printf("%s",Buffer);
    fclose(fpErr);
}

int main()
{
    PassOne();
    display_Symbtab();
    if (errFlag == 0)
        PassTwo();
    else
    {
        display_Err();
        printf("\n Cannot create target code!!\n");
    }
    return 0;
}
 
/*
Input asm file
START 200
READ A
ORIGIN 300
ADD AREG, B
MULT BREG, D
SUB CREG, Z
BC ANY, B
MOVER CREG, C
PRNT A
A DS 5
B DC 10
C DS 15
D DS 4
  
OUTPUT:
 
(AD, 00) (C, 200)
(IS, 09) (S, 00)
(AD, 02) (C, 300)
(IS,   01) (0) (S,01)
(IS,   03) (1) (S,02)
(IS,   02) (2) (S,03)
(IS,   07) (5) (S,01)
(IS,   04) (2) (S,04)
PRNT --- Invalid Instruction
(DL, 01) (C, 05)
(DL, 00) (C, 10)
(DL, 01) (C, 15)
(DL, 01) (C, 04)

200) + 09 0 306
300) + 01 0 306
301) + 03 0 306
302) + 02 2 306
303) + 07 0 306
304) + 04 0 306
305) + 10 0 306
306)
307)
308)
309)
310)
311) + 00 0 010
*/
