#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
/*funcion*/
float Area(float b, float h)
{
	float A;
	A=(b*h)/2;
	return A;
}

int main ()
{
	float b,h,A;
	b=0,h=0;
	printf("\t\t==================================================\t\t\t\n");
	printf("\t\tEste programa calcula el %crea de un tri%cngulo\n",160,160);
	printf("\t\t==================================================\t\t\t\n");
	printf("\t\tDigite el valor de la base\n");printf("\t\tBase:");scanf("%f",&b);
	if(b>0)
	{
	printf("\t\tDigite el valor de la altura\n");printf("\t\tAltura:");scanf("%f",&h);
	if(h>0)
	{
	system("cls");
	printf("\t\t\t=============================================\t\t\t\n");
	printf("\t\t\tSuperficie del tri%cngulo:%.2f metros cuadrado\n",160, Area(b,h));
	printf("\t\t\t=============================================\t\t\t\n");
	return 0;
	}else
	{
		printf("\t\tPor favor, ingrese datos validos!");
	}
	}else
	{
		printf("\t\tPor favor, ingrese datos validos!");
	}
}

