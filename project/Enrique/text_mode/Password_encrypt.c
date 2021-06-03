#include<stdio.h>
#define ENTER 13
#define TAB 9
#define BKSP 8

char pwd[100];
int main(){
	int i=0;
	char ch;
	char password1[5]={"1234"};
	printf("Introducir contrase%ca\n",164);
	printf("Contrase%ca: ",164);
	
	while(1)
	{
		ch=getch();
		
		if(ch==ENTER||ch==TAB){
			pwd[i]= '\0';
			break;
		}else if(ch==BKSP){
			if(i>0){
				i--;
				printf("\b \b");
				
			}
		}else{
			pwd[i++]=ch;
			printf("* \b");
		}
	}
	if(strcmp(pwd,password1)==0){
		printf("\nHola");}
		else{printf("\nContrase%ca incorrecta, no te conozco bai",164);
		}
	return 0;
}
