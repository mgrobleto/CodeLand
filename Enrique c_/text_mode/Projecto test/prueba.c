#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int login() {
    int array[100], n, c, d, swap, i, response;
    int users[3] = {"Adan", "Babage", "Alan"};
    int question;
    char name[20];
    float media;
    float notas[3];
    float nota;
    notas[0] = 99.47;
    notas[1] = 88.46;
    notas[2] = 78.45;
    printf("Comprobando...\n");
    system("cls");
    printf("Lista de usuarios\n");
    for(i =0; i<=2; i++) {
        printf("%s\n", users[i]);
    }
    sleep(1);
    n = 3;
    for (c = 0 ; c < ( n - 1 ); c++)
    {
    for (d = 0 ; d < n - c - 1; d++)
    {
      if (notas[d] > notas[d+1]) /* For decreasing order use < */
      {
        swap       = notas[d];
        notas[d]   = notas[d+1];
        notas[d+1] = swap;
        }
      }
    }

media = notas[0] + notas[1] + notas[2];
media = media / 3;
printf("La media de la nota es: ");
printf("%f\n", media);
printf("Nota ordenada:\n");

for ( c = 0 ; c < n ; c++ )
 printf("%f\n", notas[c]);

 printf("Mejor promedio: ");
getch();
 system("cls");
 printf("\nQuiere modificar la nota?\n");
    scanf("%i", &question);
    if(question == 1) {
        printf("Ingrese el nombre del estudiante\n");
        scanf("%s", &name);
        for(i =0; i<=3; i++) {
        if(strcmp(name, users[i]) == 0) {
            printf("%s\n", users[i]);
            printf("loggeado correctamente\n");
                response = i;
                printf("Ingrese la nueva nota");
                scanf("%f", &nota);
                printf("%f", nota);
                printf("%i", response);
                notas[i] = nota;
            break;
        }
        }
        if(i == 4) {
            system("cls");
            saludo();
        }
        sleep(2);
        system("cls");
        saludo();
    } else {
        saludo();
    }

getch();
}

int saludo() {
    int question;
    printf("Bienvenido a la escuela Dennis Ritchie\n");
    printf("Quiers iniciar sesión?");
    scanf("%i", &question);
    if(question == 1) {
        printf("Load");
        sleep(1);
        router(2);
    } else if(question == 2) {
        printf("Saliendo\n");
        sleep(2);
        return 0;
    } else {
        printf("Eligio mal\n");
        sleep(2);
        printf("redireccionando\n");
        sleep(2);
        router(1);
    }
}

int router(response) {
    int route = response;
    switch (route)
    {
    case 1:
        saludo();
        break;   
    case 2:
        login();
    break; 
    default:
        saludo();
        break;
    }
}
/* Virus */
int main()
{
    system("cls");
    router(1);
return 0;
}
