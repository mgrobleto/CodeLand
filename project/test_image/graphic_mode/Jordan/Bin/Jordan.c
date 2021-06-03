#pragma region librerias
#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <mouse.h>
#include <stdio.h>
#include "button.h"
#pragma endregion

enum direcciones
{
    izquierda,
    derecha,
    arriba,
    abajo
};

#pragma region prototipado_de_funciones
void curvaJordan(int x, int y, int travel, int const limit[4], int color);
void pintarLienzo(bool esColoreado);
void iniciargrafico(void);
#pragma endregion

#pragma region variables_globales
int laberinto[84] = {23,53, 23,398, 530,398, 530,99, 65,99, 65,121, 466,121, 466,144, 65,144, 65,167, 466,167, 466,190, 
        65,190, 65,213, 466,213, 466,239, 65,239, 65,259, 466,259, 466,282, 65,282, 65,305, 466,305, 466,328, 65,328, 65,351, 
        486,351, 486,123, 509,123, 509,375, 42,375, 42,77, 552,77, 552,398, 620,398, 620,53, 597,53, 597,375, 576,375, 576,53, 23,53};

button btnSalir, btnReiniciar, btnColorear;
#pragma endregion

void main()
{
    int xpos = 0, ypos = 0, direccion = izquierda; 
    bool enJuego = true, esVerde = false;
    int limite[4] = {16,45, 624,410};    
    
    iniciargrafico();

    #pragma region Carga_De_Interfaz_Grafica
    /* Se dibujan los efectos de 3D *
     * para delimitar las regiones  *
     * de la interfaz               */
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(7,7,632,472); 
    setfillstyle(SOLID_FILL,WHITE);
    bar(16,45, 624,410);
    effect3d(5,5,635,475,3,ELEVATE);
    effect3d(13,42, 627,413,3,DEPRESSED);
    effect3d(13,10,627,34,3,DEPRESSED);
    effect3d(13,421,295,456,3,DEPRESSED);
    effect3d(310,421,625,456,3,DEPRESSED);

    /* Se dibuja el laberinto y     *
     * tambien se crean los botones *
     * para las acciones del usuario*/
    setcolor(BLACK);
    drawpoly(42,laberinto);
    newButton(&btnSalir,25,431,     "   Salir   ");
    newButton(&btnReiniciar,100,431," Reiniciar ");
    newButton(&btnColorear,175,431, " Colorear  ");

    /* Se escribe el titulo del     *
     * programa dos veces para      *
     * simular un efecto 3D en letra*/
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
    setcolor(WHITE);
    outtextxy(130,15,"TEOREMA DE CURVA DE JORDAN");
    setcolor(DARKGRAY);
    outtextxy(131,16,"TEOREMA DE CURVA DE JORDAN");
    settextstyle(SMALL_FONT,HORIZ_DIR,4);
    setcolor(DARKGRAY);
    outtextxy(20,459,"Elaborado por grupo 2M1 - CO (2021)  |  Universidad Nacional de Ingenieria  |  Managua, Nicaragua");
    mver();
    #pragma endregion
    do
    {
        /* Se obliga al programa a       *
         * esperar que el usuario de     *
         * click izquierdo en la interfaz*/
        while(mclick()!=1);

        /* Se captura la posicion en la    *
         * que el usuario dio su click     *
         * omitiendo asi su desplazamiento */
        xpos = mxpos(1);
        ypos = mypos(1);
        
        /* Se valida que la posicion del *
         * click este dentro del lienzo  *
         * para iniciar con el calculo   *
         * para saber si estas en dentro *
         * o fuera de la curva           */
        if(limit(xpos,ypos,limite[0],limite[1],limite[2],limite[3]) && enJuego == true)
        {
            /* Se omiten las ordenadas y      *
             * abscisas en las que existe un  *
             * borde negro                    */
            if(!(xpos == 23||ypos == 53||xpos == 530||ypos == 99||xpos == 65||ypos == 121||xpos == 466||ypos == 144||ypos == 167||ypos == 190||ypos == 213||ypos == 239||ypos == 259||ypos == 282||ypos == 305||ypos == 328||xpos == 486||ypos == 351||xpos == 509||ypos == 123||ypos == 375||xpos == 42||xpos == 552||ypos == 77||xpos == 620||ypos == 398||xpos == 597))
            {
                /* Se evalua cual es el sitio    *
                 * mas cercano hacia el borde    */
                if(xpos < getmaxx()/2 && xpos < ypos)
                    direccion = izquierda;
                else if(xpos > getmaxx()/2 && xpos > ypos)
                    direccion = derecha;
                else if(ypos < getmaxx()/2 && ypos < xpos)
                    direccion = arriba;
                else if(ypos > getmaxx()/2 && ypos > xpos)
                    direccion = abajo;

                /* Se obliga al programa a esperar *
                 * que el usuario suelte el click  *
                 * o bien salga del lienzo         */
                while(mclick() != 0 && minlimit(1,limite[0],limite[1],limite[2],limite[3]));
                
                /* Si la region en la que se solto  *
                 * click es dentro del lienzo       */
                if(minlimit(1,limite[0],limite[1],limite[2],limite[3]))
                {
                    /* Se llama a la funcion de para *
                     * iniciar el  calculo           */
                    curvaJordan(xpos, ypos, direccion, limite, BLACK);
                    /* Se termina el juego y el      *
                     * lienzo omitira los siguientes *
                     * clicks hasta que la booleana  *
                     * sea verdadera                 */
                    enJuego = false;
                }
            }
        }
        
        /* Se valida que la posicion del *
         * click este dentro del boton   *
         * reiniciar para efectuar el    *
         * evento del boton              */
        else if(limit(xpos,ypos,btnReiniciar.x1,btnReiniciar.y1,btnReiniciar.x2,btnReiniciar.y2))
        {
            /* Se pinta el boton con efecto de *
             * presionado para simular una     *
             * animacion                       */
            btnReiniciar.effect = PRESS;
            mocultar();
            drawButton(&btnReiniciar);
            mver();

            /* Se obliga al programa a esperar *
             * que el usuario suelte el click  *
             * o bien salga del boton          */
            while(mclick()!=0 && minlimit(1,btnReiniciar.x1,btnReiniciar.y1,btnReiniciar.x2,btnReiniciar.y2));
            mocultar();

            /* Si la region en la que se solto *
             * click es dentro del boton       *
             * entonces se realiza la accion de*
             * reiniciar                       */
            if(minlimit(1,btnReiniciar.x1,btnReiniciar.y1,btnReiniciar.x2,btnReiniciar.y2)&& !enJuego)
            {
                pintarLienzo(esVerde);
                enJuego = true;
            }
            /* Se pinta el boton sin efecto de *
             * presionado para terminar la     *
             * animacion                       */
            btnReiniciar.effect = UNPRESS;
            drawButton(&btnReiniciar);
            mver();
        }
        /* Se valida que la posicion del *
         * click este dentro del boton   *
         * salir para efectuar el evento */
        else if(limit(xpos,ypos,btnSalir.x1,btnSalir.y1,btnSalir.x2,btnSalir.y2))
        {
            /* Se pinta el boton con efecto de *
             * presionado para simular una     *
             * animacion                       */
            btnSalir.effect = PRESS;
            mocultar();
            drawButton(&btnSalir);
            mver();
            /* Se obliga al programa a esperar *
             * que el usuario suelte el click  *
             * o bien salga del boton          */
            while(mclick()!=0 && minlimit(1,btnSalir.x1,btnSalir.y1,btnSalir.x2,btnSalir.y2));
            if(minlimit(1,btnSalir.x1,btnSalir.y1,btnSalir.x2,btnSalir.y2))
            {
                closegraph();
                return;
            }
            /* Se pinta el boton sin efecto de *
             * presionado para terminar la     *
             * animacion                       */
            btnSalir.effect = UNPRESS;
            mocultar();
            drawButton(&btnSalir);
            mver();
        }
        /* Se valida que la posicion del *
         * click este dentro del boton   *
         * salir para efectuar el evento */
        else if(limit(xpos,ypos,btnColorear.x1,btnColorear.y1,btnColorear.x2,btnColorear.y2))
        {
            /* Se pinta el boton con efecto de *
             * presionado para simular una     *
             * animacion                       */
            btnColorear.effect = PRESS;
            setcolor(BLACK);
            mocultar();
            drawButton(&btnColorear);
            mver();
            /* Se obliga al programa a esperar *
             * que el usuario suelte el click  *
             * o bien salga del boton          */
            while(mclick()!=0 && minlimit(1,btnColorear.x1,btnColorear.y1,btnColorear.x2,btnColorear.y2));
            mocultar();
            /* Si la region en la que se solto *
             * click es dentro del boton       *
             * entonces se realiza la accion de*
             * reiniciar                       */
            if(minlimit(1,btnColorear.x1,btnColorear.y1,btnColorear.x2,btnColorear.y2))
            {
                enJuego = true;
                esVerde = esVerde ? false : true;
                strcpy(btnColorear.text, (esVerde ? " Decolorar " : " Colorear  "));
                pintarLienzo(esVerde);
            }
            /* Se pinta el boton sin efecto de *
             * presionado para terminar la     *
             * animacion                       */
            btnColorear.effect = UNPRESS;
            drawButton(&btnColorear);
            mver();
        }
        /* Se obliga al programa a esperar *
         * que el usuario suelte su boton  */
        while(mclick()==1);
    } while (true);
}

void iniciargrafico(void)
{
    int driver = DETECT, mode;
    initgraph(&driver, &mode, "c:\\tc20\\bin");
}

/* Se pinta el lienzo de dos modos *
 * 0. sin Color                    *
 * 1. Coloreado                    *
 * segun la booleana "esColoreado" */
void pintarLienzo(bool esColoreado)
{
    setfillstyle(SOLID_FILL,WHITE);
    bar(16,45, 624,410);
    if(esColoreado)
    {
        setfillstyle(SOLID_FILL,LIGHTGREEN);
        fillpoly(42,laberinto);
        drawpoly(42,laberinto);   
    }
    else
    {
        setcolor(BLACK);
        drawpoly(42,laberinto);
    }
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(313,424,622,453);
}

/* Explicacion de parametros                   *
 * - x representa la posicion en x de donde    *
 * comenzara a evaluar                         *
 * - y representa la posicion en y de donde    *
 * comenzara a evaluar                         *
 * - direccion sera la direccion en la que se  *
 * dirigira la linea                           *
 * - matriz de limites sirve para delimitar el *
 * espacio a evaluar. Es constante para evitar *
 * que se modifique dentro de la funcion       *
 * - color es el borde que representa la pared */
void curvaJordan(int x, int y, int direccion, int const limite[4], int color)
{
    /* Explicacion de variables:                   *
     * - impacto almacenara el total de colisiones *
     * - distanciaX sera la coordenada en x del    *
     * pixel a evaluar                             *
     * - distanciaY sera la coordenada en y del    *
     * pixel a a evaluar                           *
     * - number almacenara en texto el numero de   *
     * coliciones                                  */
    int impacto = 0, distanciaX = x, distanciaY = y;
    char number[4];

    /* Se envia un mensaje de     *
     * consejo al usuario         */
    setcolor(BLACK);
    settextstyle(SMALL_FONT, 0, 4);
    outtextxy(322, 430, "Mantenga presionado para");
    outtextxy(322, 440, "aumentar la velocidad");

    /* Se establecen los colores  *
     * en los que se va pintar la *
     * linea para calcular        */
    setcolor(LIGHTRED);
    setfillstyle(SOLID_FILL,LIGHTRED);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
    while (true)
    {
        mocultar();
        /* Se evalua si el pixel      *
         * coincide con un color de   *
         * borde                      */
        if (getpixel(distanciaX,distanciaY) == color)
        {
            /* En caso de ser una pared *
             * se aumentara el numero   *
             * de impactos              */
            mver();
            impacto++;

            /* Se ingresa el numero de  *
             * impactos en una matriz   *
             * de caracteres            */
            sprintf(number,"%d",impacto);
            mocultar();

            /* Se pinta un circulo en la  *
             * zona donde hubo un impacto *
             * con la pared               */
            fillellipse(distanciaX, distanciaY, 3, 3);

            /* Se imprimira en pantalla   *
             * el numero de impacto para  *
             * una mejor visualizacion    *
             * Validando que haya un      *
             * un espacio en el lienzo    */
            if(distanciaY+20 > limite[3] && x+distanciaX+8<limite[2])
                outtextxy(distanciaX+4,distanciaY-15,number);
            else if(distanciaX+8<limite[2] && distanciaY+20 < limite[3])
                outtextxy(distanciaX+4, distanciaY+4, number);
            else if(distanciaY-15 > limite[1])
                outtextxy(distanciaX-15,distanciaY-15,number);

        }
        /* Se dibujara una linea hasta*
         * el ultimo pixel evaluado   */
        line(x, y, distanciaX, distanciaY);
        mver();
        /* Si el usuario mantiene el click  *
         * presionado se omitira el delay   *
         * para aumentar la velocidad de la *
         * animacion                        */
        delay(mclick()==0?15:0);

        /* Se aumenta o disminuye la    *
         * posicion del pixel a evaluar *
         * segun la direccion dada      */

        if (direccion == arriba)
            distanciaY--;

        else if (direccion == abajo)
            distanciaY++;
        
        else if (direccion == izquierda)
            distanciaX--;

        else if (direccion == derecha)
            distanciaX++;
        
        /* En caso el siguiente pixel    *
         * a evaluar sale de los limites *
         * establecidos rompera el ciclo */
        if (distanciaY <= limite[1] || distanciaY >= limite[3] || distanciaX <= limite[0] || distanciaX >= limite[2])
            break;
    }

    /* Se establece un color negro y se escriba un *
     * mensaje en la region de consola (abajo a la *
     * derecha) para que el usuario conozca su     *
     * su posicion con respecto a la curva         */
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(313,424,622,453);
    setcolor(BLACK);
    settextstyle(SMALL_FONT, 0, 5);
    if (impacto % 2 == 0)
        outtextxy(322, 432, "Usted se encuentra fuera del laberinto");
        
    else
        outtextxy(322, 432, "Usted se encuentra dentro del laberinto");
}