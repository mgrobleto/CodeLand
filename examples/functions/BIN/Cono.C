#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#define PI 3.1415
/*funcion*/
float Area(float g, float r)
{
	float A;
	A=(PI*r*(g+r));
	return A;
}
float Volumen(float r, float h)
{
	float V;
	V=(PI*pow(r,2)*h)/3;
	return V;
}
int main()
{
	float g,r,h;
	int opc;
	char R;
	g=0,r=0,h=0;
	do{
	printf("\n===================\n");
	printf("Qu%c desea calcular?\n===================\n\n1.%Crea de un cono.\n\n2.Volumen de un cono.\n",130,181);
	printf("\nOpcion: ");scanf("\t\t\t%d",&opc);
	system("cls");
	if(opc==1)
	{
		printf("\n======================================\nDigite el valor de la generatriz: ");scanf(" %f",&g);
		if(g>0)
		{
		printf("\n=================================\nDigite el valor del radio: ");scanf(" %f",&r);
		}
			if(r>0)
			{
			printf("\n======================================\nSuperficie del cono: %.2f metros cuadrado\n======================================\n", Area(g,r));
			printf("\nDesea volver a calcular?\n(S o N?)");
			fflush(stdin);
			}else{
				printf("Ingrese datos validos!");
			}
	}else
	{
		if(opc==2){
		printf("\n=============================\nDigite el valor del radio: ");scanf(" %f",&r);
		if(r>0)
		{
		printf("\n=============================\nDigite el valor de la altura: ");scanf(" %f",&h);
		}
		
		if(h>0)
		{
		printf("\n=========================================\nVolumen del cono: %.2f metros cubicos\n=========================================\n", Volumen(r,h));
		printf("\nDesea volver a calcular?\n(S o N?)");
		fflush(stdin);
		}else{
			printf("Ingrese datos validos");
		}
		}
		else{
		printf("Solo existen dos opciones!\n");
		system("pause");
		}
	}
	scanf("%c",&R);
}while(R!='N' && R!='n');
printf("\nSaliendo...");
}
	
