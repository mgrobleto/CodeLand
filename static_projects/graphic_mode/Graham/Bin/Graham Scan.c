/*Librerias a utilizar*/
#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

/*Cabe destacar que este codigo se puede optimizar aun mas*/

#define MAXPOINT 50 /*Numeros de puntos que se mostraran en pantalla*/
                     /*Se puede cambiar la cantidad y aun asi funcionaria el algoritmo (Cabe destacar que en este caso a mayor puntos tardara mas el algoritmo)*/
                     /*A excepcion que se dieran numeros menores de 3*/

typedef struct
{
    int x;
    int y;
}Point;              /*Una estructura de tipo punto para un mayor entendimiento del codigo*/

void inicializar(void);             /*Funcion para inicializar el modo grafico*/
bool CCW(Point a, Point b, Point c);/*Funcion para saber si un punto va con las manesillas del reloj o encontra*/
                                    /*Tambien puede indicar si un punto esta a la derecha de una linea, colineal o la izquierda de esta*/

void main (void)
{
    Point Puntos[MAXPOINT],PuntoEnSup[MAXPOINT],PuntoEnInf[MAXPOINT],Punto0,PuntoAux; /*Declaracion de variables del tipo punto*/
    int i = 0, j = 0, pasada =0, Cant=0; /*Variables de interaccion*/
    char Men[50]; /*Posible mensaje que se guardara en esta variable*/

    inicializar();

    srand((unsigned int)time(NULL));/* Funcion para cambiar la funcion random en cada ejecucion de codigo*/

    for(i=0;i<MAXPOINT;i++) /*Establecimiento de puntos*/
    {
        /*Se indica la posicion de los puntos a traves de la funcion random, estos puntos tendran cierto limites en pantalla*/

        Puntos[i].x =100 +(rand() % 440) ;  
        Puntos[i].y =100 +(rand() % 280) ;  
    }

    /*Bucle para mostrar los puntos en pantalla y obtener el punto que se encuentra mas a la izquierda*/

    for(i=0;i<MAXPOINT;i++)
    {
        putpixel(Puntos[i].x,Puntos[i].y,WHITE);
    }

    /*Bucle para organizar los puntos de forma ascendente de izquierda a derecha usando el metodo de burbuja*/
    /*Cabe destacar que hay algoritmos mas eficientes que este*/

	for( pasada=1;pasada<MAXPOINT;pasada++)
		for( i =0; i<MAXPOINT-1;i++)
			if(Puntos[i].x>=Puntos[i+1].x)
			{
				PuntoAux = Puntos[i];
				Puntos[i] = Puntos[i+1];
				Puntos[i+1] = PuntoAux;
			}
    /*

    Este bucle es solamente para enumerar los puntos de izquierda a derecha

    for(i=0;i<MAXPOINT;i++)
    {
        sprintf(Men,"%d",i); /*Se guarda el mensaje en la cadena, que sera el valor de i
        outtextxy(Puntos[i].x,Puntos[i].y,Men); /* Se muestra en pantalla en las coordenadas de los puntos la enumeracion de cada punto
        delay(10);
    }
    
    */

   /*Este es una de las variaciones del algoritmo de Graham Scan, en esta se trabaja por partes, 
    Como se vio antes, los puntos se ordenaron de izquierda a derecha, y no conforme el angulo con respecto al punto
    */

   /*Esta primera parte se trabaja unicamente del lado superior de la envolvente convexa*/

    PuntoEnSup[0] = Puntos[0];  /*Se le asigna los dos puntos iniciales de la cadena*/
    PuntoEnSup[1] = Puntos[1];
    Cant = 2;                   /*Y se lleva el control de la cantidad de puntos existentes en esta cadena*/

    for(i = 2; i<MAXPOINT; i++)
    {
        PuntoEnSup[Cant]=Puntos[i]; /*Una vez en el bucle se agrega en la cadena el siguiente punto del total de puntos que se ordenaron respectivamente*/
        Cant++; /*se aumenta el valor del total de puntos de la parte de la envolvente convexa superior*/

        while( (Cant > 2) && !CCW(PuntoEnSup[Cant-1],PuntoEnSup[Cant-2],PuntoEnSup[Cant-3]))
         /*Entra en este bucle solamente si la envolvente convexa tiene mas de 2 puntos y el penultimo punto de los tres ultimos puntos de dicha cadena
            no esta ubicado a la parte derecha de la recta que forma el penultimo y ultimo punto
         */
        {
            /*Esto es unicamente para que se pinto de negro las lineas blancas que ya no son validas
            Nota: puede llegar cierto punto que llegue a borrar parte de la figura
            */
            setcolor(BLACK); /*Cambialo a azul para ver magia*/
            line(PuntoEnSup[Cant-3].x,PuntoEnSup[Cant-3].y,PuntoEnSup[Cant-2].x,PuntoEnSup[Cant-2].y);
            putpixel(PuntoEnSup[Cant-2].x,PuntoEnSup[Cant-2].y,WHITE);
            
            /*Si llega a entrar a este bucle quiere decir que va por un mal camino
            por ende se tendra que regresar y se eliminara el penultimo punto guardado en la caadena convexa
            y asi sucesivamente hasta que no se cumpla la condicion del bucle y comience a ir por donde tiene que ser
            */

            PuntoEnSup[Cant-2] = PuntoEnSup[Cant-1];
            Cant--;/*Se disminuye el total de puntos en el arreglo*/
            delay(50);
        }

        /*Aqui solamente se pinta la linea en blanco para que de poco a poco se vaya cerrando convexamente*/

        setcolor(WHITE);
        if(Cant > 2)
            line(PuntoEnSup[Cant-3].x,PuntoEnSup[Cant-3].y,PuntoEnSup[Cant-2].x,PuntoEnSup[Cant-2].y);
        
        delay(100);
    }

    /*Ya una vez terminado el bucle solo se traza la linea final*/

    line(PuntoEnSup[Cant-2].x,PuntoEnSup[Cant-2].y,PuntoEnSup[Cant-1].x,PuntoEnSup[Cant-1].y);


    /*Se hace lo mismo por esta vez con la parte inferior del cierre convexo*/

    /*La cadena de la parte inferior tendra los dos ultimos puntos del total de puntos que hay en el orden que se habia indicado antes*/
    PuntoEnInf[0] = Puntos[MAXPOINT-1];
    PuntoEnInf[1] = Puntos[MAXPOINT-2];
    Cant = 2;

    for(i = MAXPOINT-3; i>-1; i--)/*El bucle va en reversa, la variable i disminuye hasta llegar a 0*/
    {
        /*Aqui es exactamente igual que en el codigo anterior*/

        PuntoEnInf[Cant]=Puntos[i];
        Cant++;

        while( (Cant > 2) && !CCW(PuntoEnInf[Cant-1],PuntoEnInf[Cant-2],PuntoEnInf[Cant-3]))
        {
            setcolor(BLACK);/*Cambialo a azul para ver magia*/
            line(PuntoEnInf[Cant-3].x,PuntoEnInf[Cant-3].y,PuntoEnInf[Cant-2].x,PuntoEnInf[Cant-2].y);
            putpixel(PuntoEnInf[Cant-2].x,PuntoEnInf[Cant-2].y,WHITE);
            PuntoEnInf[Cant-2] = PuntoEnInf[Cant-1];
            Cant--;
            delay(50);
        }

        setcolor(WHITE);
        if(Cant > 2)
            line(PuntoEnInf[Cant-3].x,PuntoEnInf[Cant-3].y,PuntoEnInf[Cant-2].x,PuntoEnInf[Cant-2].y);
        
        delay(100);
    }

    line(PuntoEnInf[Cant-2].x,PuntoEnInf[Cant-2].y,PuntoEnInf[Cant-1].x,PuntoEnInf[Cant-1].y);    

    setcolor(WHITE);
    outtextxy(50,20,"Pulse cualquier boton para Salir");
    getch();
    closegraph();
}

bool CCW(Point a, Point b, Point c) /*Funcion para obtener la ubicacion de un punto respecto a un recta*/
{
    long int q = (long)(c.y-a.y)*(long)(b.x-a.x); 
    long int w = (long)(b.y-a.y)*(long)(c.x-a.x);
    
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

    if( q >= w ) /*Si el punto esta ubicado a la derecha o es colineal*/

        return false;
   
    return true;   /*Si esta ubicado a la izquierda*/
}

void inicializar(void)
{
	int drive=DETECT,modo;
	initgraph(&drive,&modo,"c:\\tc20\\bin");
}

