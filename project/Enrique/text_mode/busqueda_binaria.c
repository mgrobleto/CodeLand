#include<stdio.h>

/*Busqueda binaria*/

int func(int array[],int left, int right, int objetivo){
if(right>=left){
	int mid = left+(right-left)/2;
	if(array[mid]==objetivo){
		return mid;
	}
	if(array[mid]>objetivo){
		return func(array,left,mid-1,objetivo);
	}
	return func(array,mid+1,right,objetivo);
}
return -1;
}
void main(void){
int array[]={1,7,2,5,3,8,2};/*Numeros dados*/
int objetivo;

printf("Ingrese el numero a buscar:");
scanf("%d",&objetivo);

int arraysize=7;
int resultado=func(array,0,arraysize-1,objetivo);
if(resultado==-1){
printf("not found");

}else{printf("found!");}
getch();
}
