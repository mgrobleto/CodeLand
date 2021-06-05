#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>

/*funcion*/
float Volumen (float a)
{
	float v;
	v=pow(a,3);
	return v;
}
float Area(float a)
{
	float area;
	area=6*pow(a,2);
	return area;
}
int main()
{
	int opc;
	char R;
	float a,v,area;
	a=0;
	do{
	printf("\n===================\n");
	printf("Qu%c desea calcular?\n===================\n\n1.%Crea de un cubo.\n\n2.Volumen de un cubo.\n",130,181);
	printf("\nOpcion:");scanf("\t\t\t%d",&opc);
	system("cls");
		if(opc==1)
		{
		printf("\n=============================\nDigite el valor del arista: ");scanf(" %f",&a);
		if(a>0)
		{
		printf("\n======================================\nSuperficie cubo: %.2f metros cuadrado\n======================================\n", Area(a));
		printf("\nDesea volver a calcular?\n (S o N?)"); //scanf("%c",&R);
		fflush(stdin);
		}else{
		printf("Ingrese datos validos!");
		}
		}else
		{
		if(opc==2)
		{
		printf("\n=============================\nDigite el valor del arista: ");scanf(" %f",&a);
		if(a>0)
		{
		printf("\n======================================\nVolumen cubo: %.2f metros cubicos \n======================================\n", Volumen(a));
		printf("\nDesea volver a calcular?\n (S o N?)"); 
		fflush(stdin);
		}else{
		printf("Ingrese datos validos!");
		}
		}else
		{
		printf("\nSolo existen dos opciones!\n");
		system("pause");
		}
		}
		scanf("%c",&R);
	}while(R!='N' && R!='n');
	printf("\nSaliendo...");
}
