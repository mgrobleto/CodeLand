#include<stdio.h>
#include<conio.h>
#include<string.h>

int main()
{
	char texto[100];
	bool palindromo=true;
	int i=0;
	int longitud;
	printf("********************************************************************************\n");
	printf("\tEn este programa te diremos si una PALABRA es o no palindroma\n");
	printf("********************************************************************************\n");
	printf("Cargando.");
	//sleep(1);
	printf(".");
	//sleep(1);
	printf(".");
	printf("\t========================================\n");
	printf("\t\tDigite una cadena: ");
	printf("\t========================================\n");
	gets(texto);

	longitud=strlen(texto);
	for(i=0;i<longitud/2;i++)
	{
		if(texto[i]!=texto[longitud-i-1])
		{
			palindromo=false;
		}
		/*printf("%c",texto[i]);*/
	}
	if(palindromo==true)
	{
		printf("\nLa cadena ingresada es palindroma");
	}else
	{
		printf("\nLa cadena ingresada no es palindroma");
	}
}
