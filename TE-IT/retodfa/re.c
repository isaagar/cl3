	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>

	struct tree
	{
		struct tree *lnode;
		char element;
		struct tree *rnode;
		char firstpos[10];
		char lastpos[10];
	};

	struct stack
	{
		struct tree *node;
		struct stack *next;
	};

	struct fpt			//followpos table
	{
		char ip;
		char followpos[20];
	};

	struct state
	{
		char name;
		char states[10];
	};


	void buildtree(char ps[20], struct tree **root);
	void firstlastpos(struct tree **root);
	void followpos(struct tree **root, int n);
	void dfa(struct fpt f[10], int n);

	int main(void)
	{
		char ps[20]={'\0'};
		struct tree *root=NULL;
	
		printf("\n Enter Postfix String : ");
		fflush(stdin);
		scanf("%s",ps);
		printf("\n Press Any Key To Continue..... ");
	
		buildtree(ps,&root);
	
		return(0);
	}

	int push(struct stack **top, struct tree *enode)
	{
		int succ=0;
		struct stack *temp=NULL;
		temp=(struct stack *)calloc(1,sizeof(struct stack));
		if(temp!=NULL)
		{
			temp->node=enode;
			if((*top)==NULL)
			{
				*top=temp;
			}
			else
			{
				temp->next=(*top);
				*top=temp;
			}
			succ=1;
		}
		return(succ);
	}

	int pop(struct stack **top, struct tree **node)
	{
		int succ=0;
		struct stack *dnode=NULL;
		if(*top!=NULL)
		{
			dnode=*top;
			*top=dnode->next;
			dnode->next=NULL;
			*node=dnode->node;
			free(dnode);
			dnode=NULL;
			succ=1;
		}
		return(succ);
	}

	void buildtree(char ps[20], struct tree **root)
	{
		int i=0;
		int test=0;
		int succ=0;
		struct tree *newnode=NULL;
		struct tree *troot=NULL;
		struct tree *childnode=NULL;
		struct stack *top=NULL;
		while(ps[i]!='\0')
		{
			newnode=(struct tree *)calloc(1,sizeof(struct tree));
			if(newnode==NULL)
			{
				printf("\n MEMORY ALLOCATION FAILED!!! \n");
			}
			else
			{
				newnode->element=ps[i];
			}
			test=isalpha(ps[i]);
			if(test!=0||ps[i]=='#')
			{
				succ=push(&top,newnode);
				if(succ==0)
				{
					printf("\n MEMORY ALLOCATION ERROR \n");
				}
			}
			else
			{
				succ=pop(&top,&childnode);
				troot=newnode;
				if(succ!=0&&troot->element!='*')
				{
					troot->rnode=childnode;
				}
				if(troot->element=='*')
				{
					troot->lnode=childnode;
					troot->rnode=NULL;
				}
				succ=pop(&top,&childnode);
				if(succ!=0&&troot->element!='*')
				{
					troot->lnode=childnode;
				}
				push(&top,troot);
			}
			i++;
		}
		pop(&top,&troot);
		*root=troot;
		firstlastpos(&troot);
	}

	void copyset(struct tree **p, struct tree **q)
	{
		int i=0;
		while((*q)->firstpos[i]!=0)
		{
			(*p)->firstpos[i]=(*q)->firstpos[i];
			i++;
		}
	}

	void unionfirst(struct tree **p, struct tree *q, struct tree *r)
	{
		int i=0;
		int j=0;
		int k=0;
		int succ=0;
		while(q->firstpos[i]!='\0')
		{
			(*p)->firstpos[i]=q->firstpos[i];
			i++;
		}
		while(r->firstpos[j]!='\0')
		{
			succ=0;
			for(k=0;k<i;k++)
			{
				if((*p)->firstpos[k]==r->firstpos[j])
				{
					succ=1;
					k=i;
				}
				if(succ==0)
				{
					(*p)->firstpos[i]=r->firstpos[j];
					i++;
				}
				j++;
			}
		}
	}

	void unionlast(struct tree **p, struct tree *q, struct tree *r)
	{
		int i=0;
		int j=0;
		int k=0;
		int succ=0;
		while(q->lastpos[i]!='\0')
		{
			(*p)->lastpos[i]=q->lastpos[i];
			i++;
		}
		while(r->lastpos[j]!='\0')
		{
			succ=0;
			for(k=0;k<i;k++)
			{
				if((*p)->lastpos[k]==r->lastpos[j])
				{
					succ=1;
					k=i;
				}
				if(succ==0)
				{
					(*p)->lastpos[i]=r->lastpos[j];
					i++;
				}
				j++;
			}
		}
	}

	void postorder(struct tree *node)
	{
		if(node!=NULL)
		{
			postorder(node->lnode);
			postorder(node->rnode);
			printf("\n   %c\t    %s \t\t %s ",node->element,node->firstpos,node-	>lastpos);
		}
	}

	void firstlastpos(struct tree **root)
	{
		char nodenum[1]="1";
		int succ=0;
		int i=0;
		int n=0;
		struct tree *p=NULL;
		struct stack *top=NULL;
		p=*root;
		while(p!=NULL||top!=NULL)
		{
			if(p==NULL)
			{
				while(top!=NULL&&p==top->node->rnode)
				{
					succ=pop(&top,&p);
					if(succ==1)
					{
						if(p->lnode==NULL&&p->rnode==NULL)	// leaf node
						{
							p->firstpos[0]=nodenum[0];
							p->lastpos[0]=nodenum[0];
							n=atoi(nodenum);
							n++;
							sprintf(nodenum,"%d",n);
						}
						else if(p->element=='*'||p->element=='+')
						{
							i=0;
							while(p->lnode->firstpos[i]!=0)
							{
								p->firstpos[i]=p->lnode->firstpos[i];
								i++;
							}
							i=0;
							while(p->lnode->lastpos[i]!=0)
							{
								p->lastpos[i]=p->lnode->lastpos[i];
								i++;
							}
						}
						else if(p->element=='|')
						{
							unionfirst(&p,p->lnode,p->rnode);
							unionlast(&p,p->lnode,p->rnode);
						}
						else if(p->element=='.')
						{
							if(p->lnode->element=='*')		// c1 is nullable
							{
								unionfirst(&p,p->lnode,p->rnode);
							}
							else
							{
								i=0;
								while(p->lnode->firstpos[i]!='\0')
								{
									p->firstpos[i]=p->lnode->firstpos[i];
									i++;
								}
							}
							if(p->rnode->element=='*')		// c1 is nullable
							{
								unionlast(&p,p->lnode,p->rnode);
							}
							else
							{
								i=0;
								while(p->rnode->lastpos[i]!='\0')
								{
									p->lastpos[i]=p->rnode->lastpos[i];
									i++;
								}
							}
						}
					}
				}
				if(top==NULL)
				{
					p=NULL;
				}
				else
				{
					p=top->node->rnode;
				}
			}
			if(p!=NULL)
			{
				succ=push(&top,p);
				if(succ==0)
				{
					printf("\n MEMORY ALLOCATION FAILED \n");
				}
				else
				{
					p=p->lnode;
				}
			}
		}
		printf("\n STEP 1 : \n");
		printf("\n NODE \t FIRSTPOS     LASTPOS \n");
		postorder(*root);
		printf("\n Press Any Key To Continue..... ");
		p=*root;
		followpos(&p,n-1);
		*root=p;
	}


	void followpos(struct tree **root, int n)
	{
		int succ=0;
		int i=0;
		int j=0;
		int k=0;
		int s=0;
		int len=0;
		char str[20]={'\0'};
		char temp[2]={'\0'};
		struct tree *p=NULL;
		struct stack *top=NULL;
		struct fpt f[10]={0};
		p=*root;
		while(p!=NULL||top!=NULL)
		{
			if(p==NULL)
			{
				while(top!=NULL&&p==top->node->rnode)
				{
					succ=pop(&top,&p);
					if(succ==1)
					{
						if(p->lnode!=NULL||p->rnode!=NULL)
						{
							if(p->element=='*')
							{
								for(i=1;i<=n;i++)
								{
									j=0;
									sprintf(temp,"%d",i);
									while(p->lastpos[j]!='\0')
									{
										if(p->lastpos[j]==temp[0])
										{
											strcat(f[i].followpos,p->firstpos);
											j=9;
										}
										j++;
									}
								}
							}
							else if(p->element=='.'||p->element=='|')
							{
								for(i=1;i<=n;i++)
								{
									j=0;
									sprintf(temp,"%d",i);
									while(p->lnode->lastpos[j]!='\0')
									{
										if(p->lnode->lastpos[j]==temp[0])
										{
											strcat(f[i].followpos,p->rnode->firstpos);
											j=9;
										}
										j++;
									}
								}
							}
						}
						else
						{
							i=atoi(p->firstpos);
							f[i].ip=p->element;
						}
					}
				}
				if(top==NULL)
				{
					p=NULL;
				}
				else
				{
					p=top->node->rnode;
				}
			}
			if(p!=NULL)
			{
				succ=push(&top,p);
				if(succ==0)
				{
					printf("\n MEMORY ALLOCATION FAILED \n");
				}
				else
				{
					p=p->lnode;
				}
			}
		}
		for(i=1;i<=n;i++)
		{
			s=0;
			len=strlen(f[i].followpos);
			if(len>1)
			{
				for(j=1;j<=n;j++)
				{
					k=0;
					sprintf(temp,"%d",j);
					while(k<len)
					{
						if(temp[0]==f[i].followpos[k])
						{
							str[s]=temp[0];
							s++;
							k=len;
						}
						k++;
					}
				}
				str[k]='\0';
				strcpy(f[i].followpos,str);
				f[i].followpos[k]='\0';
			}
		}
		printf("\n STEP 2 : \n");
		printf("\n NODE NO:\tLEAF NODE \t FOLLOWPOS \n");
		for(i=1;i<=n;i++)
		{
			printf("\n    %d    \t%c \t\t %s\n",i,f[i].ip,f[i].followpos);
		}
		dfa(f,n);
	}

	void unionset(char nstate[10], struct fpt f1, struct fpt f2)
	{
		int i=0;
		int j=0;
		int k=0;
		int succ=0;
		while(f1.followpos[i]!='\0')
		{
			nstate[i]=f1.followpos[i];
			i++;
		}
		while(f2.followpos[j]!='\0')
		{
			succ=0;
			for(k=0;k<i;k++)
			{
				if(nstate[k]==f2.followpos[j])
				{
					succ=1;
					k=i;
				}
				if(succ==0)
				{
					nstate[i]=f2.followpos[j];
					i++;
				}
				j++;
			}
		}
	}

	void dfa(struct fpt f[10], int n)
	{
		char ip[5][5]={'\0'};
		int ipc[5]={0};
		char dfa[8][5]={'\0'};
		struct state s[8]={0};
		char nstate[10]={0};
		int i=0;
		int j=0;
		int k=0;
		int a=0;
		int b=0;
		int len=0;
		int point=0;
		int inputs=0;
		int succ=0;
		int flag=0;
		int loop=0;
		int loop1=0;
		for(i=1;i<=n;i++)
		{
			k=0;
			succ=0;
			if(f[i].ip!='#')
			{
				while(k<j)
				{
					if(ip[k][0]==f[i].ip)
					{
						ip[k][ipc[k]+1]=i;
						ipc[k]++;
						k=3;
						succ=1;
					}
					k++;
				}
				if(succ==0)
				{
					ip[j][0]=f[i].ip;
					ip[j][ipc[j]+1]=i;
					ipc[j]++;
					j++;
				}
			}
		}
		inputs=j;
		i=0;
		strcpy(s[i].states,f[i+1].followpos);
		s[i].name='P';
		dfa[loop1][0]=s[i].name;
		do
		{
			flag=0;
			len=strlen(s[i].states);
			for(j=0;j<inputs;j++)
			{
				k=0;
				loop=0;
				nstate[0]='\0';
				while(k<len)
				{
					point=s[i].states[k]-48;
					if(f[point].ip==ip[j][0])
					{
						a=0;
						while(f[point].followpos[a]!='\0')
						{
							succ=0;
							b=0;
							while(nstate[b]!='\0')
							{
								if(nstate[b]==f[point].followpos[a])
								{
									succ=1;
								}
								b++;
							}
							if(succ==0)
							{
								nstate[loop]=f[point].followpos[a];
								loop++;
							}
							a++;
						}
					}
					k++;
				}
				succ=0;
				k=0;
				while(k<=i&&succ!=1)
				{
					if(strcmp(nstate,s[k].states)==0)
					{
						succ=1;
						dfa[loop1][j+1]=s[k].name;
					}
					else
					{
						k++;
					}
				}
				if(succ!=1)
				{
					i++;
					strcpy(s[i].states,nstate);
					s[i].name=s[i-1].name+1;
					dfa[loop1][j+1]=s[i].name;
					flag=1;
				}
				while(loop>=0)
				{
					nstate[loop]='\0';
					loop--;
				}
			}
			loop1++;
			for(j=1;j<=i;j++)
			{
				succ=0;
				for(k=1;k<=loop1;k++)
				{
					if(s[j].name==dfa[k][0])
					{
						succ=1;
						k=loop1;
					}
				}
				if(succ==0)
				{
					i=j;
					dfa[loop1][0]=s[i].name;
					j=i+1;
				}
			}
		}while(flag!=0);
		printf("\n STEP 3 : \n\n RESULTING DFA \n\n");
		printf("\n\t");
		for(k=0;k<inputs;k++)
		{
			printf("%c\t",ip[k][0]);
		}
		printf("\n\n");
		for(j=0;j<=i;j++)
		{
			for(k=0;k<=inputs;k++)
			{
				printf("%c\t",dfa[j][k]);
			}
			printf("\n");
		}
	}
