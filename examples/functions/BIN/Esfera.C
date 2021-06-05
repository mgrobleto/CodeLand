#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#define PI 3.1415

/*Funcion para calcular el area*/
float Volumen(float r)
{
float v, p;
p=pow(r,3);
v=(4*PI*p)/3;
return v;
}

int main()
{
	float r,v;
	r=0;
	printf("\t\t\t****Este programa calcula el volumen de una esfera****\t\t\t\n");
	printf("\t\t=======================================================================\t\t\t\n");
	printf("\t\t\t\tIngrese el valor del radio\t\t\t\t\n");
	printf("\t\t\t\tRadio:");scanf("%f",&r);
	system("cls");
	if(r>0)
	{
	printf("\t\t\t\t============================================\t\t\t\n");
	printf("\t\t\t\tEl volumen de la esfera es igual a:%.2f\n",Volumen(r));
	printf("\t\t\t\t============================================\t\t\t\n");
	}else
	{
		printf("Ingrese datos validos!");
	}
	return 0;
}

