#include<stdio.h>
#include<malloc.h>
typedef struct node{
	char character;
	int frequency;
	struct node *left;
	struct node *right;
}node;
void downadjust(node *heap[],int i,int size){
	int j,flag=1;
	node *temp;
	while(i*2<size && flag){
		j=2*i;
		flag=1;
		if(j+1<size && heap[j]->frequency>heap[j+1]->frequency)
			j++;
		if(heap[i]->frequency>heap[j]->frequency){
			temp=heap[i];
			heap[i]=heap[j];
			heap[j]=temp;
			i=j;
		}	
		else
			flag=0;
	}
}
node* remove_t(node *heap[],int size){
	node *n;
	int i;
	n=heap[0];
	heap[0]=heap[size];
	for(i=size/2;i>=0;i--)
		downadjust(heap,i,size);
	return n;
}
node * huffman(node *heap[],int size){
	node *n1,*n2,*n;
	int i;
	while(size>1){
		size--;
		n1=remove_t(heap,size);	
		size--;
		n2=remove_t(heap,size);
		n=(node*)malloc(sizeof(node));
		n->character='-';
		n->frequency=n1->frequency+n2->frequency;
		n->left=n1;
		n->right=n2;
		size++;
		heap[size-1]=n;
		for(i=size/2;i>=0;i--)
			downadjust(heap,i,size);
	}
	return heap[0];
}
void traverse(node *n,int arr[],int k){
	int i;
	if(n->left!=NULL){
		arr[k]=0;
		traverse(n->left,arr,k+1);	
	}	
	if(n->right!=NULL){
		arr[k]=1;
		traverse(n->right,arr,k+1);
	}	
	if((n->left==NULL)&&(n->right==NULL)){
		printf("\n%c:",n->character);
		for(i=0;i<k;i++)
			printf("%d",arr[i]);
	}		
}
void t(node *n){
	if(n!=NULL){
		t(n->left);
		printf(" %d",n->frequency);
		t(n->right);
	}
}
int main(){
	node *heap[20],*n;
	int size,i,arr[5];
	printf("\n Enter the number of characters to be encoded:");
	scanf("%d",&size);
	for(i=0;i<size;i++){
		n=(node*)malloc(sizeof(node));
		printf("\n Enter the character:");
		scanf(" %c",&n->character);
		printf("\n Enter the frequency:");
		scanf("%d",&n->frequency);
		n->left=NULL;
		n->right=NULL;
		heap[i]=n;
	}
	for(i=size/2;i>=0;i--)
		downadjust(heap,i,size);
	n=huffman(heap,size);
	//t(n);
	traverse(n,arr,0);
	return 0;
}
