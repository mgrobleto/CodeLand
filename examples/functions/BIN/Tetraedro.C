#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
/*funcion*/
float Area(float ar)
{
	float A;
	A=sqrt(3)*pow(ar,2);
	return A;
}
float Volumen(float ar)
{
	float V;
	V=(sqrt(2)/12)*pow(ar,3);
	return V;
}
int main()
{
	int opc;
	char R;
	float ar;
	ar=0;
	do{
	printf("\n===================\n");
	printf("Qu%c desea calcular?\n===================\n\n1.%Crea de un tetraedro.\n\n2.Volumen de un tetraedro.\n",130,181);
	printf("\nOpcion:");scanf("\t\t\t%d",&opc);
	system("cls");
	if(opc==1)
	{
		printf("\n=============================\nDigite el valor del arista: ");scanf(" %f",&ar);
		if(ar>0)
		{
		printf("\n======================================\nSuperficie tetraedro: %.2f metros cuadrado\n======================================\n", Area(ar));
		printf("\nDesea volver a calcular?\n(S o N?)");
		fflush(stdin);
		}else{
			printf("Ingrese datos validos!");
		}
	}else
	{
		if(opc==2){
		printf("\n=============================\nDigite el valor del arista: ");scanf(" %f",&ar);
		if(ar>0)
		{
		printf("\n=========================================\nVolumen tetraedro: %.2f metros cubicos \n=========================================\n", Volumen(ar));
		printf("\nDesea volver a calcular?\n(S o N?)");
		fflush(stdin);
		}else{
			printf("Ingrese datos validos");
		}
	}else{
		printf("\nSolo existen dos opciones!\n");
		system("pause");
	}
	}
	scanf("%c",&R);
}while(R!='N' && R!='n');
printf("\nSaliendo...");
}
