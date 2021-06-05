
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>


void main()
{
	char encriptado[200];
	char cadena[200];
	int i=0,longitud=0;
	system("cls");
	gotoxy(15,12);
	printf("Digite el texto a encriptar: ");gets(cadena);
	longitud=strlen(cadena);
	for(i=0;i<strlen(cadena);i++)
	{
		if(i % 2 == 0)
		{
			encriptado[i]=cadena[i]+2;
		}else
		{
			if(i % 2 != 0)
			{
				encriptado[i]=cadena[i]+3;
			}
		}
	}
	system("cls");
	gotoxy(33,12);
	printf("Cargando");
	printf(".");
	sleep(1);
	printf(".");
	sleep(1);
	printf(".");
	sleep(1);
	system("cls");
	textbackground(RED);
	gotoxy(15,12);
	printf("Mensaje encriptado: ");
	for(i=0;i<strlen(cadena);i++){
		printf("%c",encriptado[i]);
	}
	getch();
}
