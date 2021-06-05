#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int main()
{
	int x[5],copy[5],i=0,suma=0,num;
	printf("Digite un numero entero: ");scanf("%d",&num);
	for(i=0;i<5;i++)
	{
		x[i]=num;
		num++;
	}
	fflush(stdin);
	printf("Los numeros dentros del arreglo 1: ");
	for(i=0;i<5;i++)
	{
		printf("%d.",x[i]);
	}
	fflush(stdin);
	for(i=0;i<5;i++)
	{
		copy[i]=x[i];
	}
	printf("\nEn el arreglo 2 guardamos los valores dentro del arreglo 1: ");
	for(i=0;i<5;i++)
	{
		printf("%d.",copy[i]);
	}
}
