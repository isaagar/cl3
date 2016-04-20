#include <stdio.h>
int i;
int error = 0;
char input[10];
void E();
void T();
void Eprime();
void Tprime();
void F();
int main(){
	printf("Enter the expression:");
	scanf("%s",input);
	printf("%s",input);
	int len;
	for(len = 0 ; len < 10 ; len ++){
		if (input[len] == '\0')
			break;
	}
	printf("\nE -> TE'\n");
	printf("E' -> +TE' | #\n");
	printf("T -> FT'\n");
	printf("T' -> *FT' | #\n");
	printf("F -> (E) | id\n\n\n");
	i = 0;
	E();
	printf("%d\n",len);
	if (error == 1 )
		printf("Error\n");
	else
		printf("Accepted\n");
	return 0;
}
void E(){
	printf("E -> TE'\n");
	T();
	Eprime();
};
void T(){
	printf("T -> FT'\n");
	F();
	Tprime();
};
void F(){
	if (input[i] == 'a'){
		printf("F -> a\n");
		i++;
	}
	else if(input[i] == '('){
		printf("F -> (E)\n");
		i++;
		E();
		if (input[i] !=')')
			error = 1;
	}
	else
		error = 1;
};
void Tprime(){
	if (input[i] == '*'){
		printf("T' -> *FT'\n");
		i++;
		F();
		Tprime();
	}
	else
		printf("T' -> #\n");
};
void Eprime(){
	if (input[i] == '+'){
		printf("E' -> +TE'\n");
		i++;
		T();
		Eprime();
	}
	else
	printf("E' -> #\n");
};
