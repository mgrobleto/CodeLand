#include <stdio.h>
#include <conio.h>
#include<stdlib.h>

int main ()
{
	int fila, columna, numero=0, Matriz[3][3];
	system("cls");
	
	for (fila=0;fila<3;fila++)
	{
		for (columna=0;columna<3;columna++)	
			{
				Matriz[fila][columna]=numero;
				numero++;
			}
	}
		
	printf("\n Matriz Original \n\n");
	
	for (fila=0;fila<3;fila++)
	{
		for (columna=0;columna<3;columna++)	
		{
			printf("  %d  ",Matriz[fila][columna]);
		}
			printf ("\n\n");
	}
	
	printf("\n Matriz Transpuesta \n\n");
	
	for (fila=0;fila<3;fila++)
	{
		for (columna=0;columna<3;columna++)	
		{
			printf("  %d  ",Matriz[columna][fila]);
		}
			printf ("\n\n");
	}
	
	getch();
	return 0;
		
	}