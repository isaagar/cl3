#include<stdio.h>
#include<stdlib.h>
struct code
{
 char opr,op1,op2,res;
};
int n,i,ch=0;
struct code c[10];
void constant_expr_evaluation();
void common_subexpr_removal();
void display();
int main()
{
 printf("Enetr number of code:");
 scanf("%d",&n);
 printf("\nEnter 3 Address Code matrix\nopr  op1  op2  res\n");
 
 for (i=0;i<n;i++)
 {   
     scanf("%s",&c[i].opr);
scanf("%s",&c[i].op1);
scanf("%s",&c[i].op2);
scanf("%s",&c[i].res);
 }
display();

	printf("\n1. Constant expression evaluation\n2.Common subexpression removal\n3.Exit\nEnter your choice");
	fflush(stdin);
        scanf("%d",&ch);

     
         
   switch(ch)
	{
	   case 1:
				constant_expr_evaluation();
				display();
                break;
		case 2:
				common_subexpr_removal();
				display();				
				break;
		case 3:
				return 0;
		default:
				printf("\nWrong choice");
	}
 
}
void constant_expr_evaluation()
{
      int i,j=0;
      for(i=0;i<n;i++)
      {
		
        if(c[i].opr=='=')
          if(c[i].op2=='-')// null value chk
          {
		 for (j=i+1;j<n;j++)
	        {
			    if (c[j].op1==c[i].res)
                                   c[j].op1=c[i].op1;// replace constant val
			    else if (c[j].op2==c[i].res) 
                     		   c[j].op2=c[i].op1;
                 }
                for (j=i;j<n-1;j++)
	        {
                 c[j].opr=c[j+1].opr;
                 c[j].op1=c[j+1].op1; // to replc val remov entry of const exp
                 c[j].op2=c[j+1].op2;
                 c[j].res=c[j+1].res;
               }
          n--; // coz we rmv one entry
        } 
     }
}
void common_subexpr_removal()
{
  int i,j,k;
  char r;
  for(i=0;i<n;i++)
   for(j=i+1;j<n;j++)
   {
      if((c[i].op1==c[j].op1&&c[i].op2==c[j].op2)||c[i].op1==c[j].op2&&c[i].op2==c[j].op1)//a+b==b+a
       {r=c[j].res;				// rslt of duplict entry 
          for(k=j;k<n-1;k++)
         {					 // replce orignl entry rslt with duplicate entry rslt
		c[k].opr=c[k+1].opr;
             if(c[k+1].op1==r)
                  c[k].op1=c[i].res;
             else
                  c[k].op1=c[k+1].op1;
             if(c[k+1].op2==r)
                  c[k].op2=c[i].res;
             else
               c[k].op2=c[k+1].op2;
               c[k].res=c[k+1].res;	

         }
        n--;
       }

   } 
}


void display()
{
printf("\nS.NO\tOperator\tOperand1\tOperand2\tResult\n\n");
   for(i=0;i<n;i++)
    {
      printf("%d\t",i);	
      printf("\t%c\t",c[i].opr);
      printf("\t%c\t",c[i].op1);
      printf("\t%c\t",c[i].op2);
      printf("\t%c\t",c[i].res);
      printf("\n"); 
    }	 
}
