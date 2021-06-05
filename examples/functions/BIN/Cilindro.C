#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#define PI 3.1415

float Area(float r, float h)
{
	float A;
	A=(2*PI*r*(h+r));
	return A;
}
float Volumen(float r, float h)
{
	float V;
	V=PI*pow(r,2)*h;
	return V;
}
int main()
{
	int opc;
	float r,h;
	char R;
	r=0,h=0;
	printf("===================\n");
	printf("Qu%c desea calcular?\n===================\n\n1.%Crea de un Cilindro.\n\n2.Volumen de un Cilindro.\n",130,181);
	printf("\nOpcion:");scanf("\t\t\t%d",&opc);
	system("cls");
	if(opc==1)
	{
		printf("\n======================================\nDigite el valor del radio: ");scanf("%f",&r);
		if(r>0)
		{
			printf("\n======================================\nDigite el valor de la altura: ");scanf("%f",&h);
		}
			if(h>0)
			{
				printf("\n===============================================\nSuperficie del Cilindro: %.2f metros cuadrado\n===============================================\n", Area(r,h));
				system("pause");
			}else{
				printf("Ingrese datos validos!");
			}
	}else{
		if(opc==2)
		{
			printf("\n======================================\nDigite el valor del radio: ");scanf("%f",&r);
			if(r>0)
			{
			printf("\n======================================\nDigite el valor de la altura: ");scanf("%f",&h);
			}
			if(h>0)
			{
				printf("\n===============================================\nVolumen del Cilindro: %.2f metros cubicos \n===============================================\n", Volumen(r,h));
				system("pause");
			}else{
				printf("Ingrese datos validos!");
			}	
		}else{
			printf("Solo existen dos opciones!");
		}
	}
	getch();
}
