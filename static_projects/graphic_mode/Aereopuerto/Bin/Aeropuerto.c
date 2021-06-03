#include <stdio.h>
#include <graphics.h>
#include <mouse.h>
#include <conio.h>
#include <stdlib.h>
#include <VENTANAS.h>
#include <Button.h>
#include <GTools.h>

int main()
{
    struct time tiempo; /*estructura tiempo*/
    int tiempoAeropuerto = 0, hora = 0, seg = 0, minutos = 0;
    int vuelo = -1, xpos = 0, ypos = 0; /*Esta variable nos indicara en que ventana estamos*/
    int registroContador = 0, despejado = 0, paisDeLlegada = 0, ingresoDatos = 0;
    int destinos[5];
    int cantidad = 0, i = 0;
    button btnIngresoVuelo, btnDespeje, btnRadar, btnRegistro, btnSalir;
    /*-----------------modificar o poner un error en el c para la librerias-------------------------*/
    iniciarModoGrafico();
    entradaAeropuerto();
    settextstyle(8, 0, 4);
    Text3D(20, 425, 2, 0, 15, "Cargando...");
    gettime(&tiempo);
    tiempoAeropuerto = tiempo.ti_sec;

    delay(30000);
    cleardevice();
    panelDeControl();
    newButton(&btnIngresoVuelo, 58, 447, " Datos ");
    newButton(&btnDespeje, 192, 431, " Despeje ");
    newButton(&btnRadar, 380, 431, "  Radar  ");
    newButton(&btnRegistro, 530, 447, " Registro ");
    newButton(&btnSalir, 280, 465, "  Salir  ");
    mver();
    seg = tiempoAeropuerto;
    minutos = tiempoAeropuerto;
    do
    {
        gettime(&tiempo);
        tiempoAeropuerto = tiempo.ti_sec;
        if (minutos != tiempoAeropuerto)
            minutos = tiempoAeropuerto;

        if (tiempoAeropuerto == seg + 30)
        {
            if (seg + 30 == 60) /*cuando ya es un minuto*/
                seg = 0;
            else /*cuando ya es medio minuto*/
                seg = 30;

            if (hora == 24)
                hora = 0;

            hora++; /*incremento de hora*/
        }
        while (mclick() != 1)
            ;            /*Esperamos que haga un click*/
        xpos = mxpos(1); /*Capturamos su posicion evitando su desplazamiento*/
        ypos = mypos(1);

        /****-----------------Preguntamos si esta en el primer boton es decir en el [ingreso de datos]-----------------****/
        if (limit(xpos, ypos, btnIngresoVuelo.x1, btnIngresoVuelo.y1, btnIngresoVuelo.x2, btnIngresoVuelo.y2))
        {
            /*Hacemos el efecto que esta presionado*/
            btnIngresoVuelo.effect = PRESS;
            mocultar();
            drawButton(&btnIngresoVuelo);
            mver();

            /*Validar que el click se suelte o salga del boton para asi saber si se ejecuta o no la accion*/
            while (mclick() != 0 && minlimit(1, btnIngresoVuelo.x1, btnIngresoVuelo.y1, btnIngresoVuelo.x2, btnIngresoVuelo.y2))
                ;
            mocultar();

            /*Si la region en que lo solto es en las cordenadas del boton que ejecute la accion*/
            if (minlimit(1, btnIngresoVuelo.x1, btnIngresoVuelo.y1, btnIngresoVuelo.x2, btnIngresoVuelo.y2))
            {
                if (vuelo == -1 && ingresoDatos < 5) /*menos uno es para cancelar*/
                {
                    vuelo = ingresoVuelo();

                    if (vuelo >= 0 && vuelo <= 5)
                    {
                        despejado = 0;
                        ingresoDatos++;
                    }
                }
                mocultar();
                panelDeControl();
            }
            /*Se pinta el boton desprecionado*/
            btnIngresoVuelo.effect = UNPRESS;
            drawButton(&btnIngresoVuelo);
            drawButton(&btnDespeje);
            drawButton(&btnRadar);
            drawButton(&btnRegistro);
            drawButton(&btnSalir);
            mver();
        }
        /*****-------------------------Si presiona el boton de despeje---------------------------------------------------*****/
        else if (limit(xpos, ypos, btnDespeje.x1, btnDespeje.y1, btnDespeje.x2, btnDespeje.y2))
        {
            /*Hacemos el efecto que esta presionado*/
            btnDespeje.effect = PRESS;
            mocultar();
            drawButton(&btnDespeje);
            mver();

            /*Validar que el click se suelte o salga del boton para asi saber si se ejecuta o no la accion*/
            while (mclick() != 0 && minlimit(1, btnDespeje.x1, btnDespeje.y1, btnDespeje.x2, btnDespeje.y2))
                ;
            mocultar();

            /*Si la region en que lo solto es en las cordenadas del boton que ejecute la accion*/
            if (minlimit(1, btnDespeje.x1, btnDespeje.y1, btnDespeje.x2, btnDespeje.y2))
            {

                despeje(ingresoDatos, despejado);
                if (ingresoDatos != 0)
                {
                    despejado = 1;
                }
                mocultar();
                panelDeControl();
            }
            /*Se pinta el boton desprecionado*/
            btnDespeje.effect = UNPRESS;
            drawButton(&btnIngresoVuelo);
            drawButton(&btnDespeje);
            drawButton(&btnRadar);
            drawButton(&btnRegistro);
            drawButton(&btnSalir);
            mver();
        }
        /****--------------------------------------Si presionamos el boton de Radar-----------------------------****/
        else if (limit(xpos, ypos, btnRadar.x1, btnRadar.y1, btnRadar.x2, btnRadar.y2))
        {
            /*Hacemos el efecto que esta presionado*/
            btnRadar.effect = PRESS;
            mocultar();
            drawButton(&btnRadar);
            mver();

            /*Validar que el click se suelte o salga del boton para asi saber si se ejecuta o no la accion*/
            while (mclick() != 0 && minlimit(1, btnRadar.x1, btnRadar.y1, btnRadar.x2, btnRadar.y2))
                ;
            mocultar();

            /*Si la region en que lo solto es en las cordenadas del boton que ejecute la accion*/
            if (minlimit(1, btnRadar.x1, btnRadar.y1, btnRadar.x2, btnRadar.y2))
            {
                /*---------------------------------------------------*/
                if (vuelo != -1 && despejado == 1)
                {
                    paisDeLlegada = radar(dato[Nicaragua][0], dato[Nicaragua][1], dato[vuelo][0], dato[vuelo][1], vuelo);
                    settextjustify(0,2);
                    destinos[registroContador] = paisDeLlegada;
                    registroContador++;
                    vuelo = -1;
                    despejado = 1;
                }
                mocultar();
                panelDeControl();
            }
            /*Se pinta el boton desprecionado*/
            btnRadar.effect = UNPRESS;
            drawButton(&btnIngresoVuelo);
            drawButton(&btnDespeje);
            drawButton(&btnRadar);
            drawButton(&btnRegistro);
            drawButton(&btnSalir);
            mver();
        }
        /****----------------------------------Si se presiona el boton de registro-------------------------------****/
        else if (limit(xpos, ypos, btnRegistro.x1, btnRegistro.y1, btnRegistro.x2, btnRegistro.y2))
        {
            /*Hacemos el efecto que esta presionado*/
            btnRegistro.effect = PRESS;
            mocultar();
            drawButton(&btnRegistro);
            mver();

            /*Validar que el click se suelte o salga del boton para asi saber si se ejecuta o no la accion*/
            while (mclick() != 0 && minlimit(1, btnRegistro.x1, btnRegistro.y1, btnRegistro.x2, btnRegistro.y2))
                ;
            mocultar();

            /*Si la region en que lo solto es en las cordenadas del boton que ejecute la accion*/
            if (minlimit(1, btnRegistro.x1, btnRegistro.y1, btnRegistro.x2, btnRegistro.y2))
            {
                cantidad = informacion();
                cleardevice();
                for (i = 0; i < cantidad; i++)
                {
                    registro(i, destinos[i]);
                }
                getch();
                panelDeControl();
            }
            /*Se pinta el boton desprecionado*/
            btnRegistro.effect = UNPRESS;
            drawButton(&btnIngresoVuelo);
            drawButton(&btnDespeje);
            drawButton(&btnRadar);
            drawButton(&btnRegistro);
            drawButton(&btnSalir);
            mver();
        }
        /*Si presiona el boton salir del programa*/
        else if (limit(xpos, ypos, btnSalir.x1, btnSalir.y1, btnSalir.x2, btnSalir.y2))
        {
            /*Hacemos el efecto que esta presionado*/
            btnSalir.effect = PRESS;
            mocultar();
            drawButton(&btnSalir);
            mver();

            /*Validar que el click se suelte o salga del boton para asi saber si se ejecuta o no la accion*/
            while (mclick() != 0 && minlimit(1, btnSalir.x1, btnSalir.y1, btnSalir.x2, btnSalir.y2))
                ;
            mocultar();

            /*Si la region en que lo solto es en las cordenadas del boton que ejecute la accion*/
            if (minlimit(1, btnSalir.x1, btnSalir.y1, btnSalir.x2, btnSalir.y2))
            {
                closegraph();
                return 0;
            }
        }
        mver(); 

    } while (true);
}
