#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	char array[100];
	char seguir;
	int i=0,longitud=0;
	do{
		system("cls");
		printf("En este programa se le pedira digitar una palabra, el programa no esta validado para una frase :)\n\n");
		printf("===================\n");
		printf("Digite una cadena:\n");scanf("%s",&array);
		printf("=================================\n");
		printf("La cadena ingresada es: %s\n",array);
		printf("=================================\n");
	
		longitud = strlen(array);
		printf("\nLa cadena invertida: ");
		for(i=longitud;i>=0;i--){
		printf("%c",array[i]);
		}
		fflush(stdin);
		printf("\nDesea volver a probar el programa?\n (S\\N ?)");scanf("%c",&seguir);
	}while(seguir!='N' && seguir!='n');
	printf("Saliendo.");
	sleep(1);
	printf(".");
	sleep(1);
	printf(".");
	sleep(1);
}
