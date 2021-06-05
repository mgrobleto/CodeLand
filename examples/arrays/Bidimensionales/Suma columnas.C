#include<stdio.h>
#include<conio.h>

 /*muestre los primeros 100 números de izquierda a derecha usando un array de dos dimensiones, 
 la última fila a mostrará la suma de sus respectivas columnas.*/

void main(){
     int i,j,sum=0,suma[10],cont,numeros[10][10];

    clrscr();
    for (i=0;i<10;i++)
    {
	    for (j=0;j<10;j++)
	    {
	        sum++;
		    numeros[i][j]=sum;
	    }
    }

    for (i=0;i<10;i++)
    {
        cont=0;/*El contador se ira limpiando cada vez que salte de columna*/
	    for (j=0;j<10;j++)
	    {
	        cont+=numeros[j][i];/*Leemos la columna*/
	    }
	suma[i]=cont;
    }

    for (i=0;i<10;i++)
    {
	for (j=0;j<10;j++)
	{
	    printf(" %03d ",numeros[i][j]);
	}
	printf("\n");
    }

    for(i=0;i<10;i++){
	printf(" %d ",suma[i]);
    }
    getch();
}