//Crea un programa en C que pida una cadena al usuario y muestre por pantalla la cadena invertida.

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	char array[100];
	int i=0,longitud;
	char seguir;
	system("cls");
	do{
	system("cls");
	printf("===================\n");	
	printf("Digite una cadena:\n");gets(array);
	printf("==========================\n");
	printf("La cadena ingresada es: %s\n",array);
	printf("==========================\n");
	
	longitud = strlen(array);
	printf("Longitud: %d\n",longitud);
	printf("================\n");
	printf("\nLa cadena invertida: ");
	for(i=longitud;i>=0;i--){
	printf("%c",array[i]);
	}
	printf("\n");
	printf("\nDesea volver a probar el programa? (S/N ?)\n");scanf("%c",&seguir);
	fflush(stdin);
	}while(seguir =='S' || seguir =='s');
	printf("Hasta luego!\n");
	system("pause");
}

