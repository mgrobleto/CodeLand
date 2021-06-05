#include <stdio.h>

struct corre {
    float core;
} corre[2];

int login() {
    char err[16];
    int holas;
    FILE * me;
    me = fopen("riales.txt", "r");
    for(holas = 1; holas <= 2; holas++) {
        fscanf(me, "%f", &corre[holas].core);
    }
    fclose(me);
	printf("%.2f\n" , corre[1].core);
    getch();
}

int main() {
    char hola[20];
	float i;
	FILE * new;
	system("cls");
	new = fopen("movistar.txt", "w");
    printf("Escribe Algo");
	scanf("%f", &i);
	printf("Ya, gracias muy amable xd\n");
	fprintf(new, "%f\n", i);


    fclose(new);
    getch();
    return 0;
}