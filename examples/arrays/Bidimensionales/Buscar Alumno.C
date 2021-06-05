#include <stdio.h>
#include <conio.h>
#include<string.h>

int main ()
{
	char nombres[6][7]= {"Norwing","Ernesto","Luis","Pedro","Maria","Juan"};
	char alumno[7];

	int cont, i;


	printf("\n Ingrese el nombre del alumno a buscar: ");
	scanf("%s",alumno);

	for (i=0; i<5; i++)
	{
		if(strcmp(nombres[i],alumno)==0)
		{
			printf("\n El alumno %s esta en Registrado",nombres[i]);
		}
		else
		{
			cont++;
		}
	}
	if (cont==5)
	{
		printf("\n El Alumno no esta registrado");
	}
	getch();
	return 0;

}