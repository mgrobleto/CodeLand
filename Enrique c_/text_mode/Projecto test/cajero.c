#include <stdio.h>
#include <string.h> /* gets, strcmp */
#include <stdlib.h> /* system */

#define USUARIO "c"
#define CLAVE "java"

#define LONGITUD 80

int main() {
	char usuario[LONGITUD + 1];
	char clave[LONGITUD + 1];
	int intento = 0;
	int ingresa = 0;
	char caracter;
	int i = 0;
	
	do {
		i = 0;
		system("cls");
		printf("\n\t\t\tINICIO DE SESION\n");
		printf("\t\t\t---------------\n");
		printf("\n\tUSUARIO: ");
		gets(usuario);
		printf("\tCLAVE: ");
		while (caracter = getch()) {
			if (caracter == 13) {
				clave[i] = '\0';
				break;
				
			} else if (caracter == 8) {
				if (i > 0) {
					i--;
					printf("\b \b");
				}
				
			} else {
				if (i < LONGITUD) {
					printf("*");
					clave[i] = caracter;
					i++;
				}
			}
		}
		
		if (strcmp(usuario, USUARIO) == 0 && strcmp(clave, CLAVE) == 0) {
			ingresa = 1;
			
		} else {
			printf("\n\tUsuario y/o clave son incorrectos\n");
			intento++;
			getchar();
		}
		
	} while (intento < 3 && ingresa == 0);
	
	if (ingresa == 1) {
		printf("\n\tBienvenido al Sistema\n");
        getch();
		
	} else {
		printf("\n\tHa sobrepasado el numero maximo de intentos permitidos\n");
	}

	return 0;
}