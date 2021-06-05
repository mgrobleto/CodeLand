#include<stdio.h>
#include<conio.h>

int main (){
    int i,j,n;
    char nombre[20];
    float sueldo[2];

    printf("Ingrese el numero de empleados a leer: ");
    scanf("%d",&n);
   

    for ( i = 0; i < n; i++)
    {
        printf("\nIngrese el nombre del empleado y salario base: ");
        for (j = 0; j <2; i++)
        {
            scanf("%s",&nombre[i]);
            scanf("%f",&sueldo[i]);
        }
        
    }

    for ( i = 0; i < n; i++)
    {
        for (j = 0; j <2; i++)
        {
            printf("%s",&nombre[i]);
            printf("%f",&sueldo[i]);
        }
        printf("\n");
    }
    
    

    getch();
    return 0;
}