#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
//Escribir un programa que llene un arreglo con los números pares comprendidos entre 1 y 100.

int main(){
	int array[100],i=0,suma=0,cont=0;
	
	printf("Los numeros pares comprendidos en un rango del 1 al 100:\n");
	for(i=1;i<101;i++){
		array[i]=i;
		if(i % 2 == 0){
			printf("%d.",array[i]);
		}
	}
	for(i=1;i<=100;i++){
		if(i % 2 == 0){
			suma+=i;
		}
	}
	printf("\nLa suma de los numeros pares: %d\n",suma);
	printf("\nPresione ENTER para volver al menu principal");
	getch();
}
