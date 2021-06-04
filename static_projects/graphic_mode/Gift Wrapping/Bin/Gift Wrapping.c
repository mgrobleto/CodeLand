/*Librerias a utilizar*/
#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define MAXPOINT 100 /*Numeros de puntos que se mostraran en pantalla*/
                     /*Se puede cambiar la cantidad y aun asi funcionaria el algoritmo*/
                     /*A excepcion que se dieran numeros menores de 3*/

typedef struct
{
    int x;
    int y;
} Point; /*Una estructura de tipo punto para un mayor entendimiento del codigo*/

void inicializar(void);              /*Funcion para inicializar el modo grafico*/
bool CCW(Point a, Point b, Point c); /*Funcion para saber si un punto va con las manesillas del reloj o encontra*/
                                     /*Tambien puede indicar si un punto esta a la derecha de una linea, colineal o la izquierda de esta*/

void main(void)
{
    Point Puntos[MAXPOINT], PuntoEnvol[MAXPOINT], Punto0, PuntoF; /*Declaracion de variables del tipo punto*/
    int i = 0, j = 0;                                             /*Variables de interaccion*/

    inicializar();

    srand((unsigned int)time(NULL)); /*Funcion para cambiar la funcion random en cada ejecucion de codigo*/

    for (i = 0; i < MAXPOINT; i++) /*Establecimiento de puntos*/
    {
        /*Se indica la posicion de los puntos a traves de la funcion random, estos puntos tendran cierto limites en pantalla*/

        Puntos[i].x = 100 + (rand() % 440);
        Puntos[i].y = 100 + (rand() % 280);
    }

    /*Bucle para mostrar los puntos en pantalla y obtener el punto que se encuentra mas a la izquierda*/

    for (i = 0; i < MAXPOINT; i++)
    {
        putpixel(Puntos[i].x, Puntos[i].y, WHITE);

        if (i == 0)
            Punto0 = Puntos[i];
        else if (Punto0.x > Puntos[i].x)
            Punto0 = Puntos[i];
    }

    i = 0;

    setcolor(WHITE);
    outtextxy(50, 20, "Pulse cualquier boton para continuar");
    getch();
    setcolor(BLACK);
    outtextxy(50, 20, "Pulse cualquier boton para continuar");

    /*Bucle para iniciar el cierre convexo*/

    while (true)
    {
        PuntoEnvol[i] = Punto0; /*Se agrega a la cadena los puntos que solamente forman parte de la cadena envolvente*/
        PuntoF = Puntos[0];     /*Se le asigna un punto al PuntoF para iniciar la siguiente interaccion*/

        for (j = 0; j < MAXPOINT; j++)
        {
            if ((PuntoF.x == Punto0.x && PuntoF.y == Punto0.y) || !(CCW(Puntos[j], PuntoEnvol[i], PuntoF)))
            /*Si el PuntoF - Punto final de la recta - y el Punto0 -Punto inicial de la recta- son iguales */
            /*O la funcion CCW retorna un valor de falso*/
            {
                setcolor(BLUE);
                /*Descomentar esto si se quiere apreciar mas a fondo el funcionamento ejecutando el programa
                setcolor(BLUE);
                line(Punto0.x,Punto0.y,PuntoF.x,PuntoF.y);*/
                /*Esta linea se pinta solo para que se logre apreciar lo que se hace en cada interaccion*/
                PuntoF = Puntos[j]; /*El punto final cambia al punto indicado en j*/
                delay(100);
            }
        }

        i++; /*Se incrementa i*/
        setcolor(WHITE);
        line(Punto0.x, Punto0.y, PuntoF.x, PuntoF.y);
        /*
            Ya una vez terminado la interaccion anterior se tiene en PuntoF el punto que se encuentra totalmente afuera de todos los puntos
            Y sabiendo eso se traza la linea para que de esa manera se logre cerrar la envolvente
        */
        Punto0 = PuntoF; /*El punto inicial cambia al punto final y al momento de volver a iniciar el bucle se agregara al arreglo PuntoEnvol*/

        if (PuntoF.x == PuntoEnvol[0].x && PuntoF.y == PuntoEnvol[0].y) /*Si el punto final, -PuntoF- es igual al Primer punto del arreglo PuntoEnvol*/
            break;                                                      /*Se detiene el bucle ya que la envolvente ya esta dada*/

        delay(200);
    }

    /*Aqui se logra trazar la envolvente paso por paso, sin embargo el poligono convexo (la envolvente) se puede volver a trazar con drawpoly y con la cadena PuntoEnvol
    en este punto del codigo*/

    setcolor(WHITE);
    outtextxy(50, 20, "Pulse cualquier boton para Salir");
    getch();
    closegraph();
}

bool CCW(Point a, Point b, Point c) /*Funcion para obtener la ubicacion de un punto respecto a un recta*/
{
    long int q = (long)(c.y - a.y) * (long)(b.x - a.x);
    long int w = (long)(b.y - a.y) * (long)(c.x - a.x);

    /*
    Para saber si un punto se encuentra al lado izquierdo de una recta o al lado derecho, existe una manera
    que es obtener el area del triangulo que se forma al obtener esos puntos, si el area es positiva ese punto
    se encuentra a la derecha, si el area es negativa ese punto e encuentra a la izquierda de ese segmento, y si el 
    area es 0, quiere decir que ese punto es colineal.
    
    area = |(long)(b.x-a.x)*(long)(c.y-a.y)| - |(long)(b.y-a.y)*(long)(c.x-a.x)| ;
                        q                                   w

    Es una formla del area que se obtiene a partir de unicamente sus puntos
    
    En este caso se utilizo de tal manera que solamente se compara las dos partes de esa formula, pero el resultado es el mismo
    */

    if (q >= w) /*Si el punto esta ubicado a la derecha o es colineal*/

        return true;

    return false; /*Si esta ubicado a la izquierda*/
}

void inicializar(void)
{
    int drive = DETECT, modo;
    initgraph(&drive, &modo, "c:\\tc20\\bin");
}
