#include<stdio.h>
#include<conio.h>

void main(void){
	char array[10];
	int i,j,aux;
		
		printf("Ingrese los 10 valores enteros del arreglo\n");
		
		for(i=0;i<sizeof(array);i++){
				printf("posicion: %d   >",i);
				scanf("%d",&array[i]);
				printf("%n");
		}
		
		for(i=0;i<sizeof(array);i++){
			
			for(j=0;j<sizeof(array);j++){
				if(array[j]>array[j+1]){					
					aux=array[j+1];
					array[j+1]=array[j];
					array[j]=aux;
				}				
			}
		}
		
		system("cls");
		printf("Ordenados\n");
		
		for(i=0;i<sizeof(array);i++){
			printf("%d - ",array[i]);
		}
}
